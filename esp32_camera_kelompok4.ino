#include <galihgilanggg-project-1_inferencing.h>
#include "edge-impulse-sdk/dsp/image/image.hpp"
#include "esp_camera.h"
#include "soc/soc.h"           
#include "soc/rtc_cntl_reg.h"  

#define LED_MERAH 14   // Kitkat
#define LED_KUNING 15  // Cadbury

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

static bool is_initialised = false;
uint8_t *snapshot_buf; 

static camera_config_t camera_config = {
    .pin_pwdn = PWDN_GPIO_NUM, .pin_reset = RESET_GPIO_NUM, .pin_xclk = XCLK_GPIO_NUM,
    .pin_sscb_sda = SIOD_GPIO_NUM, .pin_sscb_scl = SIOC_GPIO_NUM,
    .pin_d7 = Y9_GPIO_NUM, .pin_d6 = Y8_GPIO_NUM, .pin_d5 = Y7_GPIO_NUM,
    .pin_d4 = Y6_GPIO_NUM, .pin_d3 = Y5_GPIO_NUM, .pin_d2 = Y4_GPIO_NUM,
    .pin_d1 = Y3_GPIO_NUM, .pin_d0 = Y2_GPIO_NUM,
    .pin_vsync = VSYNC_GPIO_NUM, .pin_href = HREF_GPIO_NUM, .pin_pclk = PCLK_GPIO_NUM,
    .xclk_freq_hz = 20000000, .ledc_timer = LEDC_TIMER_0, .ledc_channel = LEDC_CHANNEL_0,
    .pixel_format = PIXFORMAT_JPEG, .frame_size = FRAMESIZE_QVGA, 
    .jpeg_quality = 12, .fb_count = 1, .fb_location = CAMERA_FB_IN_PSRAM,
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY,
};


bool ei_camera_init(void) {
    if (is_initialised) return true;
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK) return false;
    sensor_t * s = esp_camera_sensor_get();
    if (s->id.PID == OV3660_PID) {
        s->set_vflip(s, 1);
        s->set_brightness(s, 1);
        s->set_saturation(s, 0);
    }
    is_initialised = true;
    return true;
}

bool ei_camera_capture(uint32_t img_width, uint32_t img_height, uint8_t *out_buf) {
    if (!is_initialised) return false;
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) return false;
    bool converted = fmt2rgb888(fb->buf, fb->len, PIXFORMAT_JPEG, out_buf);
    esp_camera_fb_return(fb);
    if(!converted) return false;
    
    if ((img_width != 320) || (img_height != 240)) {
        ei::image::processing::crop_and_interpolate_rgb888(
            out_buf, 320, 240, out_buf, img_width, img_height);
    }
    return true;
}

static int ei_camera_get_data(size_t offset, size_t length, float *out_ptr) {
    size_t pixel_ix = offset * 3;
    size_t pixels_left = length;
    size_t out_ptr_ix = 0;
    while (pixels_left != 0) {
        out_ptr[out_ptr_ix] = (snapshot_buf[pixel_ix + 2] << 16) + (snapshot_buf[pixel_ix + 1] << 8) + snapshot_buf[pixel_ix];
        out_ptr_ix++;
        pixel_ix += 3;
        pixels_left--;
    }
    return 0;
}


void setup() {
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 
    Serial.begin(115200);
    
    pinMode(LED_MERAH, OUTPUT);
    pinMode(LED_KUNING, OUTPUT);
 
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_KUNING, HIGH);
    delay(500);
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_KUNING, LOW);

    if (!ei_camera_init()) {
        Serial.println("Failed to initialize Camera!");
    } else {
        Serial.println("Camera OK!");
    }
}

void loop() {
    snapshot_buf = (uint8_t*)malloc(320 * 240 * 3);
    if (snapshot_buf == nullptr) {
        Serial.println("ERR: OOM (Out of Memory)");
        return;
    }

    ei::signal_t signal;
    signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT;
    signal.get_data = &ei_camera_get_data;

    if (ei_camera_capture(EI_CLASSIFIER_INPUT_WIDTH, EI_CLASSIFIER_INPUT_HEIGHT, snapshot_buf)) {
        ei_impulse_result_t result = { 0 };
        EI_IMPULSE_ERROR err = run_classifier(&signal, &result, false);
        
        if (err == EI_IMPULSE_OK) {
            bool found_kitkat = false;
            bool found_cadbury = false;
            
            #if EI_CLASSIFIER_OBJECT_DETECTION == 1
            for (uint32_t i = 0; i < result.bounding_boxes_count; i++) {
                if (result.bounding_boxes[i].value < 0.5) continue;
                
                Serial.printf("Objek: %s (%f)\n", result.bounding_boxes[i].label, result.bounding_boxes[i].value);
                
                if (strcmp(result.bounding_boxes[i].label, "kitkat") == 0) found_kitkat = true;
                if (strcmp(result.bounding_boxes[i].label, "cadbury") == 0) found_cadbury = true;
            }
            #endif

            digitalWrite(LED_MERAH, found_kitkat ? HIGH : LOW);
            digitalWrite(LED_KUNING, found_cadbury ? HIGH : LOW);
        }
    }
    
    free(snapshot_buf);
    delay(10);
}
# ESP32-CAM Chocolate Object Detection (Kitkat vs Cadbury)

Repository ini berisi kode sumber untuk proyek pendeteksian objek (*Object Detection*) pada dua jenis cokelat, yaitu **Kitkat** dan **Cadbury**, menggunakan modul **ESP32-CAM**. Model *machine learning* dilatih menggunakan Edge Impulse dan dijalankan secara *real-time* langsung pada perangkat ESP32-CAM (*Edge AI*).

## 📌 Fitur Utama
1. **Deteksi Objek Real-Time:** Kamera OV2640 akan memindai objek di depannya secara terus-menerus.
2. **Indikator Serial Monitor:** Jika cokelat terdeteksi (dengan tingkat kepercayaan / *confidence* di atas 0.5), ESP32 akan mencetak label nama cokelat ("kitkat" atau "cadbury") beserta nilai akurasinya ke Serial Monitor.
3. **Indikator Visual (LED):**
   - Mendeteksi **Kitkat** ➡️ **LED Merah** menyala.
   - Mendeteksi **Cadbury** ➡️ **LED Kuning** menyala.

## 🛠️ Persiapan Perangkat Keras (Hardware Setup)

### Komponen yang Dibutuhkan
* 1x ESP32-CAM (AI-Thinker) + Modul Kamera OV2640
* 1x FTDI Programmer (USB-to-TTL) untuk *upload* program
* 1x LED Merah (Indikator Kitkat)
* 1x LED Kuning (Indikator Cadbury)
* 2x Resistor (220 ohm atau 330 ohm) untuk LED
* Kabel Jumper secukupnya

### Konfigurasi Pin (Wiring)
Sambungkan komponen eksternal (LED) ke pin ESP32-CAM berikut:

| Komponen | Pin ESP32-CAM | Keterangan |
| :--- | :--- | :--- |
| **LED Merah** (Positif/Anoda) | `GPIO 14` | Indikator Kitkat |
| **LED Kuning** (Positif/Anoda) | `GPIO 15` | Indikator Cadbury |
| GND LED (Negatif/Katoda) | `GND` | Jangan lupa gunakan resistor pada rangkaian LED |

*Catatan: Pastikan menghubungkan pin `GPIO 0` ke `GND` pada ESP32-CAM saat melakukan proses upload/flashing melalui FTDI.*

## 💻 Persiapan Perangkat Lunak (Software Setup)

1. **Install Arduino IDE:** Pastikan Anda menggunakan versi terbaru.
2. **Install Board ESP32:** Tambahkan URL *board manager* Espressif dan install *package* ESP32.
3. **Install Library Machine Learning:** 
   Proyek ini menggunakan library hasil *export* dari Edge Impulse. Anda perlu menambahkan file zip library (contoh: `ei-galihgilanggg-project-1-arduino-1.0.3.zip`) ke Arduino IDE.
   - Buka Arduino IDE > `Sketch` > `Include Library` > `Add .ZIP Library...`
   - Pilih file .zip library Edge Impulse Anda.

## 🚀 Cara Menjalankan Program

1. *Clone* atau *download* repository ini.
2. Buka file `esp32camera_chocolateclassification.ino` di Arduino IDE.
3. Hubungkan ESP32-CAM ke komputer menggunakan FTDI (Mode Flash: `GPIO 0` to `GND`).
4. Pilih Board **AI Thinker ESP32-CAM** di menu `Tools` > `Board`.
5. Klik **Upload**.
6. Setelah upload selesai (*Done uploading*), **lepas jumper `GPIO 0` ke `GND`**.
7. Buka **Serial Monitor** di Arduino IDE dan ubah *Baud Rate* menjadi `115200`.
8. Tekan tombol **Reset (RST)** pada board ESP32-CAM.
9. Arahkan kamera ke bungkus Kitkat atau Cadbury. Perhatikan Serial Monitor dan nyala LED Anda!


Choclate - v2 2022-12-12 9:50pm
==============================

This dataset was exported via roboflow.com on December 12, 2022 at 1:54 PM GMT

Roboflow is an end-to-end computer vision platform that helps you
* collaborate with your team on computer vision projects
* collect & organize images
* understand unstructured image data
* annotate, and create datasets
* export, train, and deploy computer vision models
* use active learning to improve your dataset over time

It includes 1142 images.
Choco are annotated in YOLO v5 PyTorch format.

The following pre-processing was applied to each image:
* Auto-orientation of pixel data (with EXIF-orientation stripping)
* Resize to 640x640 (Stretch)

The following augmentation was applied to create 2 versions of each source image:
* 50% probability of horizontal flip
* 50% probability of vertical flip
* Random rotation of between -20 and +20 degrees
* Random shear of between -15° to +15° horizontally and -15° to +15° vertically
* Random brigthness adjustment of between -25 and +25 percent
* Random exposure adjustment of between -12 and +12 percent
* Random Gaussian blur of between 0 and 1.75 pixels
* Salt and pepper noise was applied to 8 percent of pixels



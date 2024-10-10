# FFmpeg Clone (ffsuckpeg)

## Overview

This project is a simplified command-line interface (CLI) tool built to perform basic video processing operations such as rotation, blurring, grayscaling, trimming, and format conversion. The tool leverages OpenCV for video processing functionalities.

Key features include:

- Display a specific frame from the video.
- Rotate video frames by a specified angle.
- Apply blur to the video frames with a given size.
- Convert videos to grayscale.
- Trim the video to a specified range of frames.
- Convert videos to different formats (MP4, AVI).

## Installation

### Prerequisites

Ensure that you have the following installed:

- C++ Compiler (e.g., GCC, Clang)
- OpenCV (Version 4.x or higher)

### Clone the repository

```bash
git clone <repository-url>
cd <repository-directory>
```

### Build the project

Make sure that OpenCV is installed and configured correctly in your system.

1. Create a `build` directory:
   ```bash
   mkdir build && cd build
   ```
2. Run CMake to configure the project:
   ```bash
   cmake ..
   ```
3. Build the project:
   ```bash
   make
   ```

## Usage

```bash
ffsuckpeg <video_path> [options]
```

### Basic Commands

- Display a specific frame:

  ```bash
  ffsuckpeg input_video.mp4 --frame <frame_number>
  ```
- Rotate video frames by a specific angle:

  ```bash
  ffsuckpeg input_video.mp4 --rotate <angle>
  ```
- Apply blur to the video frames with a specified size:

  ```bash
  ffsuckpeg input_video.mp4 --blur <size>
  ```
- Convert the video to grayscale:

  ```bash
  ffsuckpeg input_video.mp4 --grayscale
  ```
- Trim video from frame `from` to frame `to`:

  ```bash
  ffsuckpeg input_video.mp4 --trim <from_frame> <to_frame>
  ```
- Convert video to another format (MP4, AVI):

  ```bash
  ffsuckpeg input_video.mp4 --convert mp4
  ```

### Example

```bash
ffsuckpeg input_video.mp4 --rotate 90 --grayscale --blur 5
```

This command rotates the video by 90 degrees, converts it to grayscale, and applies a blur with size 5.

## Notes

- The video processing is done frame-by-frame.
- You can stop the video processing by pressing the `q` key during the playback.
- For video conversion, ensure that the proper codec is supported in OpenCV.

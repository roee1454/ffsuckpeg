#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

string get_output_format(int argc, char **argv)
{
    string output_format; // Initilaizing an empty string for the check
    for (int i = 1; i < argc; i++)
    {
        if (i == 1)
            continue;
        string key = argv[i];
        if (key == "--convert")
        {
            if (i + 1 < argc)
            {
                output_format = argv[i + 1];
            }
        }
    }
    return output_format; // If there is a '--convert' argument and there is a format, get that format, otherwise, return an empty string
}

cv::VideoWriter create_video_writer(cv::VideoCapture &cap, const std::string &output_format) {
    std::string output_file = "output_video." + output_format;

    // Determine the proper fourcc code based on the output format
    int fourcc;
    if (output_format == "avi") {
        fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); // MJPG for .avi
    } else if (output_format == "mp4") {
        fourcc = cv::VideoWriter::fourcc('M', 'P', '4', 'V'); // MP4V for .mp4
    } else if (output_format == "mov") {
        fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v'); // MP4V for .mov
    } else if (output_format == "mkv") {
        fourcc = cv::VideoWriter::fourcc('X', '2', '6', '4'); // H264 for .mkv
    } else if (output_format == "webm") {
        fourcc = cv::VideoWriter::fourcc('V', 'P', '8', '0'); // VP8 for .webm
    } else {
        std::cerr << "Unsupported format: " << output_format << std::endl;
        return cv::VideoWriter(); // Return empty writer in case of unsupported format
    }

    // Retrieve video properties
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);

    // Initialize VideoWriter with the output file, codec, FPS, and frame size
    cv::VideoWriter writer(output_file, fourcc, fps, cv::Size(width, height));

    // Check if the writer was successfully opened
    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open the output video file: " << output_file << " for writing." << std::endl;
    }

    return writer; // Return the VideoWriter
}


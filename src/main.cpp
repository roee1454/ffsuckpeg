// Welcome to my ffmpeg clone! Made by Roee Heily
// Read Readme.md for further usage instructions
#include <opencv2/opencv.hpp>
#include <iostream>
#include "../include/process.hpp"
#include "../include/convert.hpp"

using namespace std;

int main(int argc, char **argv)
{
    // Check if a file path is provided
    if (argc < 2)
    {
        cout << "Usage: ffsuckpeg <video_path> ...<args>" << endl;
        return -1;
    }

    // Silencing default logs
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    // Open the video file
    string video_path = argv[1];
    cv::VideoCapture cap(video_path);

    // Check if the video file was successfully opened
    if (!cap.isOpened())
    {
        cout << "Error: Could not open the video file." << endl;
        return -1;
    }

    // Get video properties
    int frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    int frameCount = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
    double fps = cap.get(cv::CAP_PROP_FPS);

    cout << "Original Video properties: " << endl;
    cout << "Resolution: " << frameWidth << "x" << frameHeight << endl;
    cout << "FPS: " << fps << endl;
    cout << "Total Frame Count: " << frameCount << endl;

    // Checking for a '--convert' argument
    string output_format = get_output_format(argc, argv);

    // Calling the process video function
    process_video(cap, argc, argv, frameCount, output_format);

    // Release the video capture object and close windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}

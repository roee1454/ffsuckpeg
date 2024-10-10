#include <opencv2/opencv.hpp>
#include <iostream>
#include <map>
#include <optional>
#include "convert.hpp"

using namespace std;

// Function to process the video frames based on specified arguments
void process_frame(cv::Mat &frame, const map<string, optional<int>>& options) {
    // Process rotation
    if (options.count("--rotate")) { // Check if "--rotate" option exists
        int angle = *options.at("--rotate"); // Get the rotation angle
        cv::Point2f center(frame.cols / 2.0f, frame.rows / 2.0f); // Getting the center point of the frame
        cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0); // Getting the rotation matrix from the center point using the requested angle
        cv::warpAffine(frame, frame, rot, frame.size()); // Applying the rotation to the frame
    }

    // Process blurring
    if (options.count("--blur")) { // Check if "--blur" option exists
        int size = *options.at("--blur");
        if (size <= 0) { // Ensure positive size for blurring
            cout << "Invalid blur size. It must be a positive integer." << endl;
            return; // Skip blurring if size is invalid
        }
        if (size % 2 == 0) size++; // Ensure odd size for blurring
        cv::blur(frame, frame, cv::Size(size, size)); // Applying blur to the frame
    }

    // Process grayscaling
    if (options.count("--grayscale")) { // Check if "--grayscale" exists
        cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY); // Applying the grayscale filter to the frame
    }
}

// Function to display a specific frame from the video
void display_frame(cv::VideoCapture &cap, int frame_to_display) {

    // Making sure that the frame_to_display is within the video's frame bound
    int total_frames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
    if (frame_to_display < 0 || frame_to_display >= total_frames) {
        cout << "Frame index out of bounds." << endl;
        return; // Exit if frame is invalid
    }


    cv::Mat frame; // Creating an initial empty frame
    cap.set(cv::CAP_PROP_POS_FRAMES, frame_to_display); // Set to the specific frame the user wants to display
    cap >> frame; // Get the specified frame from the video capture

    // If the frame is empty, show an error message
    if (!frame.empty()) {
        cout << "Displayed frame: " << frame_to_display << endl;
        cv::imshow("Video Frame", frame); // Show the specified frame
        cv::waitKey(0); // Wait indefinitely until a key is pressed
    } else {
        cout << "The specified frame is empty or does not exist." << endl; // Error message
    }
}

void trim_video(cv::VideoCapture &cap, int from, int to) {
    // Validate that 'from' and 'to' are within valid frame indices
    if (from < 0 || to <= from) {
        cerr << "Invalid frame range for trimming." << endl;
        return; // Exit if the range is invalid
    }

    // Set the starting position of the video
    cap.set(cv::CAP_PROP_POS_FRAMES, from);
    cout << "Trimmed video's total frame count: " << (to - from) << endl;
}

void process_video(cv::VideoCapture &cap, int argc, char **argv, int &total_frames, const string &output_format) {
    map<string, optional<int>> options; // Map to hold command-line options
    int frame_to_display = -1; // Frame index to display, if there is no frame, remains -1

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        string key = argv[i];

        if (key == "--frame" && i + 1 < argc) { // Checking for a --frame argument
            frame_to_display = stoi(argv[++i]); // Get the specified frame number
        } else if (key == "--rotate" && i + 1 < argc) { // Checking for a --rotate argument
            options["--rotate"] = stoi(argv[++i]); // Get the rotation angle
        } else if (key == "--blur" && i + 1 < argc) { // Checking for a --blur argument
            options["--blur"] = stoi(argv[++i]); // Get the blur size
        } else if (key == "--grayscale") { // Checking for a --grayscale argument
            options["--grayscale"] = 1; // Applying grayscale to options
        } else if (key == "--trim") {
            if (i + 2 < argc) {
                options["--from"] = stoi(argv[++i]);
                options["--to"] = stoi(argv[++i]); // Fixed: incrementing `i` here
                options["--trim"] = 1;
            } else {
                cerr << "Missing '-from' and '-to' arguments.\nUsage Example:\nffsuckpeg input_video.mp4 --trim 40 70" << endl;
                return;
            }
        }
    }

    // If there is a frame to display, show it and exit the function
    if (frame_to_display >= 0) {
        display_frame(cap, frame_to_display);
        return; // Exit after showing the specific frame
    }

    // Check for the trim option and ensure it has valid values
    if (options.count("--trim") && options.count("--from") && options.count("--to")) { // Check if the "--trim" argument exists
        int from = *options.at("--from"); // Acquire the initial frame
        int to = *options.at("--to"); // Acquire the final frame
        int total_frames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));

        // Ensure from and to are within valid ranges
        if (from < 0 || to < 0 || from >= total_frames || to > total_frames || from >= to) {
            cerr << "Invalid frame range." << endl;
            return; // Exit if the range is invalid
        }

        trim_video(cap, from, to); // Applying the trimming
    }


    cv::Mat video_frame; // Creating an initial empty frame for video processing
    int current_frame = 0;
    while (true) {
        cap >> video_frame; // Getting each video frame from the cap variable

        // If the frame is empty, assume the video is finished
        if (video_frame.empty() || current_frame > total_frames) {
            cout << "Video is finished" << endl;
            break; // Exit the loop
        }

        if (options.count("--to") && current_frame > *options.at("--to")) {
            cout << "Video is finished at trim point" << endl;
            break; // Exit the loop
        }

        // Process the frame based on command-line options
        process_frame(video_frame, options);

        cv::imshow("Video", video_frame); // Show updated frame
        // if the user is pressing the letter 'q' finish the while loop and quit the processing operation!
        if (cv::waitKey(30) == 'q') {
            cout << "Quit key was pressed." << endl; // Message when quitting
            break; // Exit the loop
        }
        current_frame++;
    }
}

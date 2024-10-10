#include <opencv2/opencv.hpp>
#include <optional>

using namespace std;

void display_frame(cv::VideoCapture &cap, int frame_to_display);

void process_frame(cv::Mat &frame, const map<string, optional<int>> &options);

void process_video(cv::VideoCapture &cap, int argc, char **argv, int &total_frames, const string &output_format);

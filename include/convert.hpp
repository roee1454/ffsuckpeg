#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

string get_output_format(int argc, char **argv);

cv::VideoWriter create_video_writer(cv::VideoCapture &cap, const string &output_format);

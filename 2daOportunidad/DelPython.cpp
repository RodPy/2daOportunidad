#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>         
#include <string>
#include <vector>


using namespace cv;
using namespace std;

int main()
{
	Mat i, gray_scale, contours, hierarchy, thresh, ret;
	i = imread("maze.png");

	cvtColor(i, gray_scale,COLOR_BGR2GRAY);

	threshold(gray_scale, ret, 240, 255, THRESH_BINARY);
	threshold(gray_scale, thresh, 240, 255, THRESH_BINARY);

	findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	findContours(thresh, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	drawContours(thresh, contours, 0, (255, 255, 255), -1);

	threshold(ret, thresh, 240, 255, THRESH_BINARY);
	threshold(thresh, thresh, 240, 255, THRESH_BINARY);

	Mat m = Mat(19, 19, CV_8UC1, cv::Scalar(1));





}
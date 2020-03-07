// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2\stitching.hpp>

#include <iostream>
#include <vector>
#include <fstream>

#include <string>

using namespace std;
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	const int width = 176, height = 144;
	const long rawSize = width * height * 1.5;
	char raw[rawSize];
	memset(raw, 0x00, sizeof(raw));

	std::ifstream fin("C://Users//xxxx//Desktop//1.i420", std::ios::binary);
	
	for (int frameCount = 0; frameCount < 800; frameCount++)
	{
		fin.read(raw, sizeof(uchar) * rawSize);//YYYY U V

		Mat img(height, width, CV_8UC3);
		// Y
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				img.at<cv::Vec3b>(i, j)[0] = raw[i*width + j];
			}
		}
		// V
		for (int i = 0; i < height; i+=2)
		{
			for (int j = 0; j < width; j+=2)
			{
				auto pixData = raw[width*height + int((i/2)*width / 2 + j / 2)];
				img.at<cv::Vec3b>(i, j)[2] = pixData;
				img.at<cv::Vec3b>(i, j + 1)[2] = pixData;
				img.at<cv::Vec3b>(i + 1, j)[2] = pixData;
				img.at<cv::Vec3b>(i + 1, j + 1)[2] = pixData;
			}
		}
		// U
		for (int i = 0; i < height; i += 2)
		{
			for (int j = 0; j < width; j += 2)
			{
				auto pixData = raw[width*height * 5 / 4 + int((i / 2)*width / 2 + j / 2)];
				img.at<cv::Vec3b>(i, j)[1] = pixData;
				img.at<cv::Vec3b>(i, j + 1)[1] = pixData;
				img.at<cv::Vec3b>(i + 1, j)[1] = pixData;
				img.at<cv::Vec3b>(i + 1, j + 1)[1] = pixData;
			}
		}

		cvtColor(img, img, CV_YUV2BGR);
		cv::imshow("window", img);
		if ('q' == cv::waitKey(20))
		{
			break;
		}
	}

	fin.close();

	//system("pause");
	return 0;
}

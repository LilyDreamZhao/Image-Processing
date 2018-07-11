#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdlib.h>

#define _CRT_SECURE_NO_DEPRECATE
using namespace cv;
using namespace std;
int main()
{
	cv::Mat frame;
	// 可从摄像头输入视频流或直接播放视频文件
	//cv::VideoCapture capture(0);
	VideoCapture capture("D:\\Download\\IDM 处下载\\Your Name.mp4"); // open the video file for reading
	double fps;
	char string[10];  // 用于存放帧率的字符串
	cv::namedWindow("Camera FPS");
	double t = 0;

	
	
	while (1)
	{
		t = (double)cv::getTickCount();
		
		if (capture.isOpened())
		{
			capture >> frame;
			// getTickcount函数：返回从操作系统启动到当前所经过的毫秒数
			// getTickFrequency函数：返回每秒的计时周期数
			// t为该处代码执行所耗的时间,单位为秒,fps为其倒数
			

			/*
			一些操作，我们可以计算这些操作导致的fps
			*/


			t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
			fps = 1.0 / t;
			sprintf_s(string, "%.2f", fps);      // 帧率保留两位小数
			std::string fpsString("FPS:");
			fpsString += string;                    // 在"FPS:"后加入帧率数值字符串
													// 将帧率信息写在输出帧上
			putText(frame,                  // 图像矩阵
				fpsString,                  // string型文字内容
				cv::Point(5, 20),           // 文字坐标，以左下角为原点
				cv::FONT_HERSHEY_SIMPLEX,   // 字体类型
				1,                    // 字体大小
				cv::Scalar(255, 255, 255));           // 字体颜色

			cv::imshow("Camera FPS", frame);
			if (cv::waitKey(1) == 27) { break; }
		}
		else
		{
			std::cout << "No Camera Input!" << std::endl;
			break;
		}
	}

	return 0;
}

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, string argv[])
{
	VideoCapture cap("D:\\Download\\IDM 处下载\\Your Name.mp4"); // open the video file for reading
	if (!cap.isOpened())
		return 1;
	//	得到帧速率
	double rate = cap.get(CV_CAP_PROP_FPS);
	bool stop = false;
	Mat frame;
	namedWindow("Source Frame");
	namedWindow("Processed Frame");
	int delay = 1000 / rate;
	int thresh = 60;
	double Lrate = 0.02;
	Mat gray, background, backImg, foreground, output;
	while (!stop)
	{
		//	得到1帧，直到结束。
		if (!cap.read(frame))
			break;
		imshow("Source Frame", frame);
		cvtColor(frame, gray, CV_BGR2GRAY);
		if (background.empty())		//	第一帧背景直接代入，为累加需要用浮点数。
			gray.convertTo(background, CV_32FC1);
		background.convertTo(backImg, CV_8U);
		absdiff(backImg, gray, foreground);		//	作差得到前景
		threshold(foreground, output, thresh, 255, THRESH_BINARY_INV);	//	反着得到背景区域的掩码
		accumulateWeighted(gray, background, Lrate, output);			//	以一定速率更新背景
		if (!background.empty())
			imshow("Processed Frame", output);
		if (waitKey(delay) == 'q')	//	等待延迟时间，有按键则退出。
			stop = true;
	}
	cap.release();
	return 0;
}

'''
提取视频的对比度，用韦伯对比度，需要讲前景和背景分离

原文 https://blog.csdn.net/u010627377/article/details/73188314
当摄像机静止，采用差分算法提取前景物体。为了动态构建背景模型，以一定的学习速率更新背景图像。

1.已第1帧图像初始化背景图像

2.当前帧与背景作差，反阈值处理为mask

3.在此mask下用当前帧更新背景

'''

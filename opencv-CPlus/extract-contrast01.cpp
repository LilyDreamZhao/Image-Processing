/*
利用opencv c++ 提取视频对比度
01文件初次尝试
  result = maxp - minp; 
  该公式是在每一帧上面操作.实际不能用这么简单的公式.
*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat DrawText(Mat mat, string str) {

	if (mat.empty()) {
		throw("Faild open file.");
	}

	Point p = cv::Point(50, mat.rows / 2 - 50);
	//加上字符的起始点
	putText(mat, str, p, cv::FONT_HERSHEY_TRIPLEX, 0.8, cv::Scalar(255, 200, 200), 2, CV_AA);
	//在图像上加字符
	//第一个参数为要加字符的目标函数
	//第二个参数为要加的字符
	//第三个参数为字体
	//第四个参数为子的粗细
	//第五个参数为字符的颜色


	return mat;
}

int main(int argc, char* argv[])
{
	VideoCapture cap("D:\\Download\\IDM 处下载\\Your Name.mp4"); // open the video file for reading

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	//create windows
	namedWindow("Original Video", WINDOW_NORMAL);

	double maxv = 0.0, minv = 0.0;
	double* minp = &minv;
	double* maxp = &maxv;
	string str;

	while (1)
	{
		Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}

		minMaxIdx(frame, minp, maxp);
		//str = to_string(maxp - minp);
		str = to_string(int(maxv - minv));
		frame = DrawText(frame, str);
		imshow("Original Video", frame);

		if (waitKey(1) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;
	
}

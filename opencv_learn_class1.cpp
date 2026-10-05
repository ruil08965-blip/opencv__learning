#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("C:/Users/HUAWEI/Desktop/aaa.png", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cout << ("couldn't_loud_the_image");
	}
	namedWindow("输入窗口", WINDOW_FREERATIO);
	imshow("输入窗口", src);
	waitKey(0);
	destroyAllWindows();
	return 0;

}
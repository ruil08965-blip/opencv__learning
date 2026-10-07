#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    // 0 表示默认摄像头（内置摄像头）；如果是外接 USB 摄像头，可以改成 1
    VideoCapture cap(0);

    // 检查摄像头是否成功打开
    if (!cap.isOpened())
    {
        cout << "无法打开摄像头！" ;
        return -1;
    }

    Mat frame, gray, cannyImg;

    while (true)
    {
        cap >> frame; // 从摄像头读取一帧画面
        if (frame.empty()) 
            break;

        // 1. 转为灰度图，再提取边缘
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        Canny(gray, cannyImg, 80, 160);

        // 2. 寻找轮廓
        vector<vector<Point>> contours;
        findContours(cannyImg, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // 3. 遍历每一个检测到的形状
        for (size_t i = 0; i < contours.size(); i++)
        {
            // 忽略太小的杂质/噪声
            if (contourArea(contours[i]) < 1000) continue;

            // 简化轮廓，计算这个形状有几个角（顶点）
            vector<Point> poly;
            double perimeter = arcLength(contours[i], true);
            approxPolyDP(contours[i], poly, 0.03 * perimeter, true);

            int corners = poly.size(); // 角的数量

            //  4 个角 -> 认为是矩形
            if (corners == 4)
            {
                drawContours(frame, contours, (int)i, Scalar(0, 255, 0), 2); // 画绿框
                putText(frame, "Ju Xing (Rectangle)", poly[0], FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            }
            // 角很多（比如超过 6 个） -> 认为是圆形
            else if (corners > 6)
            {
                drawContours(frame, contours, (int)i, Scalar(0, 0, 255), 2); // 画红框
                putText(frame, "Yuan Xing (Circle)", poly[0], FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 255), 2);
            }
        }

        // 显示摄像头画面
        imshow("摄像头识别中 (按 ESC 键退出)", frame);

        // 按 ESC 键（ASCII 码 27）退出程序
        if (waitKey(30) == 27) break;
    }

    destroyAllWindows();
    return 0;
}
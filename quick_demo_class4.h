#pragma once // 避免这个头文件在同一个源文件中被重复包含。

#include <opencv2/opencv.hpp> // 引入 OpenCV 类型，例如下面使用的 Mat。

using namespace cv; // 允许直接写 Mat，而不必每次写 cv::Mat。

class QuickDemo { // 声明 QuickDemo 类，集中放置本示例的功能。
public: // public 表示这些成员可以从类外调用。
    void colorSpace_Demo(Mat& image); // 声明颜色空间演示函数，参数是可修改的图像。
    void mat_creation_demo(); // 声明矩阵创建演示函数，它不需要参数。
    void pixel_visit_demo(Mat& image); // 声明像素遍历函数，参数是可修改的图像。
}; QuickDemo qd; // 结束类声明，并创建可直接使用的全局对象 qd。

/*
============================== 文件尾部说明 ==============================

一、头文件保护与依赖
1. #pragma once 避免当前头文件在同一个翻译单元中被重复包含。
2. <opencv2/opencv.hpp> 引入 OpenCV 常用接口；本类直接使用 Mat 类型。

二、QuickDemo 类的接口
1. colorSpace_Demo(Mat& image)：预留给颜色空间处理，接收可修改的 Mat 引用；
   当前对应的实现函数体为空。
2. mat_creation_demo()：无参数示例，用于创建矩阵、赋值、复制和显示图像。
3. pixel_visit_demo(Mat& image)：接收可修改的 Mat 引用；当前实现按像素遍历
   单通道或三通道的 8 位图像，对各通道执行反色并显示结果。
4. 这里仅声明成员函数，函数实现放在对应的 .cpp 文件中。使用引用可避免复制
   整个 Mat 对象，同时意味着函数能够修改调用者传入的图像数据。

三、cv 命名空间与全局对象
1. using namespace cv 让本文件后续代码可以直接写 Mat，而不必写 cv::Mat。
   因为它位于头文件中，该声明也会影响包含本头文件的源文件。
2. QuickDemo qd; 在头文件中定义了全局对象 qd。若项目只有一个 .cpp 文件
   包含此头文件，当前写法可以工作；若多个 .cpp 文件都包含它，各翻译单元
   会各自产生一个定义，链接时可能出现重复定义错误。多文件项目通常会在头文件
   只声明对象，并在一个 .cpp 文件中提供唯一的定义。此处保留原代码，仅作说明。

*/
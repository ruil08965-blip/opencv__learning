/* 在 OpenCV 中，cv::Mat 是用来存储图像和矩阵数据的核心数据结构。
   这里可以继续描述更多内容
*/

/*在 OpenCV 中，cv::Mat 是用来存储图像和矩阵数据的核心数据结构。
对于新手来说，cv::Mat 最容易踩坑的地方就是 “浅拷贝” 与 “深拷贝”。如果不理解它们的区别，修改一张图片时可能会不小心把原图也改掉了
一、 核心概念：浅拷贝 vs 深拷贝
cv::Mat 的内部结构分为两部分：

矩阵头（Header）：包含图像的大小、通道数、数据类型以及指向像素数据的内存地址指针。头部体积很小。

像素数据块（Data Block）：实际存储每一个像素点颜色值的内存区域，体积非常大。

1. 浅拷贝（赋值操作 = 或 拷贝构造函数）
原理：只复制“矩阵头”，新旧两个 Mat 对象共享同一块像素数据。

特点：速度极快；但修改新图像的像素，原图像也会随之改变！

2. 深拷贝（克隆 clone() 或 复制 copyTo()）
原理：不仅复制“矩阵头”，还会开辟一块全新的内存，把像素数据完整地复制一份。

特点：新旧对象完全独立；修改新图像不会影响原图像。*/


//1. 浅拷贝示例（赋值 = ）
#include <opencv2/opencv.hpp>
#include <iostream>
cv::Mat img1;
int main() {
    // 创建一张 200x200 的纯黑色图像
    cv::Mat img1 = cv::Mat::zeros(200, 200, CV_8UC3);

    // 【浅拷贝】：img2 和 img1 共享同一块像素数据
    cv::Mat img2 = img1;

    // 修改 img2 的像素（画一条红色的线）
    cv::line(img2, cv::Point(0, 0), cv::Point(200, 200), cv::Scalar(0, 0, 255), 5);

    // 此时显示 img1，会发现 img1 上也多了一条红线！
    cv::imshow("img1 (原图被修改了)", img1);
    cv::imshow("img2", img2);
    cv::waitKey(0);
    return 0;
}

/*2. 深拷贝示例（clone() 与 copyTo()）
如果你希望修改新图片时不影响原图，必须使用深拷贝。

(1) clone() 方法
直接生成并返回一份完全独立的副本。 */
cv::Mat img1 = cv::Mat::zeros(200, 200, CV_8UC3);

// 【深拷贝】：img2 拥有独立的内存空间
cv::Mat img2 = img1.clone();

// 修改 img2，完全不会影响 img1


//(2) copyTo() 方法
//将当前图像的数据复制到另一个已有的或新建的 Mat 对象中。


cv::Mat img1 = cv::Mat::zeros(200, 200, CV_8UC3);
cv::Mat img3;

// 【深拷贝】：把 img1 的内容复制给 img3
 img1. copyTo(img3);

 //3. 局部引用（ROI / 感兴趣区域）
   //  如果你只想截取图片的一部分进行处理，也可以利用浅拷贝的机制。
 cv::Mat img = cv::imread("test.jpg");

 // 定义一个矩形区域：从坐标(50, 50)开始，宽高各100像素
 cv::Rect roi_area(50, 50, 100, 100);

 // 【浅拷贝截取】：cropImg 与 img 的局部共享内存
 cv::Mat cropImg = img(roi_area);

 // 把截取出来的区域全部涂成绿色，原图 img 的对应位置也会变成绿色！
 cropImg.setTo(cv::Scalar(0, 255, 0));

 //4. 常见初始化与重置操作
   //  除了拷贝，日常开发中还经常需要创建或清空 Mat：

 // 1. 创建指定大小和颜色的图像 (高 300, 宽 400, 3通道8位无符号字符)
 cv::Mat img_blue(300, 400, CV_8UC3, cv::Scalar(255, 0, 0)); // 全蓝

 // 2. 创建全零（全黑）矩阵
 cv::Mat img_zero = cv::Mat::zeros(300, 400, CV_8UC3);

 // 3. 创建全一矩阵（注意：全一矩阵所有像素值都是 1，看起来依然几乎是黑色）
 cv::Mat img_ones = cv::Mat::ones(300, 400, CV_8UC1);

 // 4. 重置/重新分配矩阵大小（如果尺寸或类型变了，会自动重新分配内存）
 img_zero.create(500, 500, CV_8UC3);

 // 5. 释放内存（通常 Mat 会通过引用计数自动释放，但可以手动清空）
 img_zero.release();
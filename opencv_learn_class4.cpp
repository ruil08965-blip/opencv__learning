#include "quick_demo_class4.h" // 引入本项目的 QuickDemo 类声明，后面才能使用它。
#include <opencv2/opencv.hpp> // 引入 OpenCV 的常用图像处理功能。
#include <iostream> // 引入控制台输入输出功能，例如 cout。


using namespace cv; // 让代码可以直接写 Mat、imshow 等名称。
using namespace std; // 让代码可以直接写 cout、endl 等名称。

int main(int argc, char** argv) { // 程序从 main 开始运行；argc 和 argv 是未使用的命令行参数。
    Mat src = imread("C:/Users/HUAWEI/Desktop/aaa.png"); // 从指定路径读取图片，并保存到 src 矩阵中。
    if (src.empty()) { // 检查图片是否读取失败。
        cout << "could not load image..." << endl; // 读取失败时在控制台显示提示。
        return -1; // 用 -1 表示程序因读取失败而结束。
    } // 结束图片读取失败时的判断分支。
    imshow("原图", src); // 打开名为“原图”的窗口并显示图片。

   
    qd.pixel_visit_demo(src); // 调用像素遍历函数；这个函数会直接修改 src。

    waitKey(0); // 等待键盘输入；0 表示一直等到用户按键。
    destroyAllWindows(); // 关闭所有由 OpenCV 打开的窗口。
    return 0; // 返回 0 表示程序正常结束。
} // 结束 main 函数。

void QuickDemo::colorSpace_Demo(Mat& image) {} // 颜色空间演示函数目前为空，调用后不会执行操作。

void QuickDemo::mat_creation_demo() { // 开始矩阵创建演示函数。
    Mat m3 = Mat::zeros(Size(400, 400), CV_8UC3); // 创建一个宽高各 400、三通道、初始为黑色的图像矩阵。
    m3 = Scalar(0, 0, 255); // 把矩阵每个像素设为 BGR 红色。
    std::cout << "width: " << m3.cols << " height: " << m3.rows << " channels: " << m3.channels() << std::endl; // 在控制台输出图像的宽度、高度和通道数。
    Mat m4; // 声明一个空矩阵，下一行会给它分配图像数据。
    m3.copyTo(m4); // 把 m3 的图像内容复制到 m4。
    m4 = Scalar(0, 255, 255); // 把 m4 的像素改为 BGR 黄色，不会改变 m3。
    imshow("图像", m3); // 显示 m3 图像。
    imshow("图像4", m4); // 显示 m4 图像。
} // 结束矩阵创建演示函数。

void QuickDemo::pixel_visit_demo(Mat& image) { // 开始像素遍历函数；引用参数让修改作用在原图上。
    int w = image.cols; // 取得图像宽度，也就是每行的像素数。
    int h = image.rows; // 取得图像高度，也就是图像的行数。
    int dims = image.channels(); // 取得每个像素包含的颜色通道数。
    for (int row = 0; row < h; row++) { // 从第一行开始，逐行遍历整幅图像。
        for (int col = 0; col < w; col++) { // 对当前行从左到右逐列遍历。
            if (dims == 1) { // 判断图像是否为单通道，例如灰度图。
                int pv = image.at<uchar>(row, col); // 读取当前位置的灰度值。
                image.at<uchar>(row, col) = 255 - pv; // 用 255 减去原灰度值，得到反色并写回原位置。
            } // 结束单通道图像的处理分支。
            if (dims == 3) { // 判断图像是否为三通道彩色图。
                Vec3b bgr = image.at<Vec3b>(row, col); // 读取当前像素的蓝、绿、红三个通道值。
                image.at<Vec3b>(row, col)[0] = 255 - bgr[0]; // 反转蓝色通道并写回当前像素。
                image.at<Vec3b>(row, col)[1] = 255 - bgr[1]; // 反转绿色通道并写回当前像素。
                image.at<Vec3b>(row, col)[2] = 255 - bgr[2]; // 反转红色通道并写回当前像素。
            } // 结束三通道图像的处理分支。
        } // 结束当前行的逐列循环。
    } // 结束逐行循环。
    imshow("像素读写演示", image); // 显示已经处理过的图像。
} // 结束像素遍历函数。
/*
============================== 文件尾部说明 ==============================

一、程序入口 main
1. main 是控制台程序的入口。argc 和 argv 是命令行参数，本示例没有使用它们。
2. imread 按给定路径读取图像。这里使用固定的绝对路径：
   C:/Users/HUAWEI/Desktop/aaa.png。运行前要确认文件存在且格式可识别；
   读取失败时 imread 返回空 Mat。
3. src.empty() 检查读取结果。失败时输出提示并返回 -1，避免在空图像上操作。
4. imshow("原图", src) 请求显示原始图像。pixel_visit_demo(src) 随后会原地
   修改 src，并在函数内以“像素读写演示”为标题显示处理结果。
5. waitKey(0) 等待键盘输入；参数 0 表示持续等待。destroyAllWindows()
   关闭 OpenCV 创建的窗口。正常执行到末尾时返回 0。

二、QuickDemo::colorSpace_Demo
当前函数体为空，因此调用它不会执行颜色空间转换，也不会改变传入图像；
它目前是预留接口。

三、QuickDemo::mat_creation_demo
1. Mat::zeros(Size(400, 400), CV_8UC3) 创建宽 400、高 400、三通道、
   每通道 8 位的矩阵，并将初始像素置为 0。Size 参数顺序是宽、高；
   Mat 的 cols 对应宽，rows 对应高。
2. m3 = Scalar(0, 0, 255) 将各像素设为 BGR 三元组 (0, 0, 255)。OpenCV
   默认使用 BGR 顺序，所以该颜色显示为红色。随后打印列数、行数和通道数。
3. m3.copyTo(m4) 把 m3 的像素复制到 m4。之后给 m4 赋值
   Scalar(0, 255, 255)，使 m4 显示为黄色；这不会把 m3 改成黄色。
4. 两次 imshow 分别显示 m3 和 m4。此函数本身没有调用 waitKey，通常由调用
   方等待窗口事件并关闭窗口。

四、QuickDemo::pixel_visit_demo
1. image 是 Mat 的引用。函数接收调用方的矩阵，不另外创建副本；像素赋值会
   直接修改调用方的数据。本程序传入的是 src。
2. cols、rows、channels() 分别取得图像宽度、高度和通道数。外层循环逐行
   遍历，内层循环逐列遍历，行列下标均从 0 开始，最大值不包含 rows/cols。
3. 单通道分支用 at<uchar>(row, col) 读取 8 位灰度值，再计算 255 - pv。
   因此 0 变为 255、255 变为 0，其余灰度也按同一公式映射。
4. 三通道分支用 Vec3b 读取一个 8 位三通道像素。三个分量分别执行
   255 - 分量值，因而蓝、绿、红通道都会反转；这一步不进行 BGR/RGB 顺序转换。
5. 代码明确处理 1 通道和 3 通道图像。若传入 4 通道等其他通道数，两个分支
   都不会修改像素，但函数仍会显示图像。at 使用的元素类型也应与 Mat 的实际
   深度和通道布局一致。
6. 双重循环访问每个像素，运算次数随图像像素总数增长；逐元素访问也便于学习
   像素读写，但处理大图时可能较慢。
7. 函数最后显示处理后的 image，但不等待按键、不关闭窗口；窗口生命周期由
   main 中的 waitKey 和 destroyAllWindows 管理。

*/
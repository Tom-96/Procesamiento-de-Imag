#include <QCoreApplication>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char *argv[])
{
    cv::Mat img = cv::imread("/mnt/c/Users/Pablo/Desktop/xayah.jpg",1);

    cv::imshow("input", img);

    cv::waitKey(0);

    return 0;
}

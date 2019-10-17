#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <cmath>
#include <iostream>
#include <stdlib.h>

cv::Mat Abs_Sobel_V(cv::Mat I)
{
    return I;
}

int main(int argc, char *argv[])
{

    char* path = argv[1];

    cv::Mat img;

    img = cv::imread(path,1);

    int a = atoi(argv[2]), b = atoi(argv[3]);

    cv::imshow("input", img);

    cv::waitKey(0);

    return 1;
}


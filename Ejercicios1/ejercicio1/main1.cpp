#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdlib.h>

//funcion que obtiene la tabla de transformacion segun el operador
float* getTransformTable(int a, int b)
{
    float *preCalculatedTable = new float[256];

    for (int i=0;i<256;i++)
    {
        if (i <= a)
        {
            preCalculatedTable[i] = 128;
        }
        if (i > a && i <= b)
        {
            preCalculatedTable[i] = ((255.0-128.0)/(b-a))*(i-a)+128;
        }
        if (i > b)
        {
            preCalculatedTable[i] = 255;
        }
    }
    return preCalculatedTable;
}

void funcion(cv::Mat I, int a, int b)
{
    cv::Mat imgYUV;

    cv::cvtColor(I, imgYUV, cv::COLOR_BGR2YCrCb);

    //tabla de transformacion
    float *t = getTransformTable(a, b);

    for (int i=0;i<imgYUV.rows;i++)
    {
        for (int j=0;j<imgYUV.cols;j++)
        {
            //canal Y luminosidad
            imgYUV.data[i*imgYUV.step + j*imgYUV.channels() + 0] = t[imgYUV.data[i*imgYUV.step + j*imgYUV.channels() + 0]];
        }
    }

    cv::cvtColor(imgYUV, I, cv::COLOR_YCrCb2BGR);
}

int main(int argc, char *argv[])
{

    char* path = argv[1];

    cv::Mat img;

    img = cv::imread(path,1);

    int a = atoi(argv[2]), b = atoi(argv[3]);

    funcion(img, a, b);

    cv::imshow("input", img);

    cv::waitKey(0);

    return 1;
}


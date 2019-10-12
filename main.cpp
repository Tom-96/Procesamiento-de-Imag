#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <cmath>
#include <iostream>
#include <stdlib.h>

float* getTransformTable(float gamma)
{
    float *preCalculatedTable = new float[256];

    for (int i=0;i<256;i++)
    {
        preCalculatedTable[i] = pow(i/255.0,gamma)*255.0;
    }
    return preCalculatedTable;
}

cv::Mat Transform(cv::Mat img, float gamma, int f[4], int c[3])
{
    cv::Mat imgYUV;

    cv::cvtColor(img, imgYUV, cv::COLOR_BGR2YCrCb);

    float *t = getTransformTable(gamma);

    if (f[0] == -1)
    {
        f[0] = 0;
        f[1] = 0;
        f[2] = img.cols;
        f[3] = img.rows;
    }

    cv::Mat roi(imgYUV, cvRect(f[0],f[1],f[2],f[3]));
    
    //imgYUV = CvScalar(0,255,0);

    for (int i=0;i<roi.rows;i++)
    {
        for (int j=0;j<roi.cols;j++)
        {
            //canal Y luminosidad
            roi.data[i*roi.step + j*roi.channels() + 0] = t[roi.data[i*roi.step + j*roi.channels() + 0]];
        }
    }

    cv::Mat imgT;

    imgYUV.copyTo(imgT);
    
    imgT = CvScalar(c[0],c[1],c[2]);

    cv::cvtColor(imgT, imgT, cv::COLOR_RGB2YCrCb);

    cv::Mat roiT(imgT, cvRect(f[0],f[1],f[2],f[3]));

    roi.copyTo(roiT);
    
    cv::cvtColor(imgT, imgT, cv::COLOR_YCrCb2BGR);

    delete t;

    return imgT;
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        std::cout << "Debe poner argumentos válidos de la función" << std::endl;
        return 0;
    }
    char* method = argv[1];

    cv::Mat img;

    float gamma = 1.0;

    int f[4] = {-1,-1,-1,-1}, c[3] = {0,0,0};

    if (method[1] == 'i')
    {
        
        char* path = argv[2];
        img = cv::imread(path,1);
        gamma = atof(argv[3]);

        if (argc > 4)
        {
            if (argv[4][1] == 'f') 
            {
                for (int i=0;i<4;i++) f[i] = atoi(argv[5+i]);
                if (argc > 9)
                    if (argv[9][1] == 'c') for (int i=0;i<3;i++) c[i] = atoi(argv[10+i]);
            }
            if (argv[4][1] == 'c') for (int i=0;i<3;i++) c[i] = atoi(argv[5+i]);
        }
    }

    else if (method[1] == 'v')
    {
        cv::VideoCapture cap;
        // open the default camera, use something different from 0 otherwise;
        // Check VideoCapture documentation.
        if(!cap.open(0))
        {
            std::cout << "no se pudo abrir webcam" << std::endl;
            return 0;
        }
        for(;;)
        {
            cap >> img;
            if( img.empty() ) break; // end of video stream
            imshow("this is you, smile! :)", img);
            std::cout << "pulse ESC para detener la captura" << std::endl;
            if( cv::waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
        }
        // the camera will be closed automatically upon exit
        // cap.close();

        gamma = atof(argv[2]);

        if (argc > 3)
        {
            if (argv[3][1] == 'f') 
            {
                for (int i=0;i<4;i++) f[i] = atoi(argv[4+i]);
                if (argc > 8)
                    if (argv[8][1] == 'c') for (int i=0;i<3;i++) c[i] = atoi(argv[9+i]);
            }
            if (argv[3][1] == 'c') for (int i=0;i<3;i++) c[i] = atoi(argv[4+i]);
        }
    }

    cv::Mat imgT = Transform(img, gamma, f, c);

    cv::imshow("input", imgT);

    cv::waitKey(0);

    return 1;
}


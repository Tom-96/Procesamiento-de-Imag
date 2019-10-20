#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdlib.h>
void function (cv::Mat I)
{
    cv::Mat YUV;
    cv::cvtColor(I, YUV, cv::COLOR_BGR2YCrCb);

    //contador de pixeles con luminosidad entre 100 y 200
    int cont_lum = 0;

    //promedio de canal U de cromancia
    float U_mean = 0;

    //promedio de canal V de cromancia
    float V_mean = 0;

    for (int i=0;i<YUV.rows;i++)
    {
        for (int j=0;j<YUV.cols;j++)
        {
            //canal de luma
            if (100 < YUV.data[i*YUV.rows + j*YUV.channels() + 0])
                if (YUV.data[i*YUV.rows + j*YUV.channels() + 0] < 200)
                {
                    cont_lum ++;
                    //canal U
                    U_mean += YUV.data[i*YUV.rows + j*YUV.channels() + 1];

                    //canal V
                    V_mean += YUV.data[i*YUV.rows + j*YUV.channels() + 2];
                }
        }
    }
    U_mean /= cont_lum;
    V_mean /= cont_lum;

    std::cout << "pixeles con luminosidad entre 100 y 200: " << cont_lum << std::endl;
    std::cout << "cromencia promedio (U,V) : (" <<  U_mean << "," << V_mean << ")" << std::endl; 
}


int main(int argc, char *argv[])
{

    char* path = argv[1];

    cv::Mat img = cv::imread(path,1);
    
    function(img);

    cv::waitKey(0);

    return 1;
}


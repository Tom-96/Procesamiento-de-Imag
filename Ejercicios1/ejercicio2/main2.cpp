#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdlib.h>

//funcion que aplica convilucion entre el kernel y una matriz 3x3
int Conv(float M[3][3])
{
    float op_sobel[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    float sum = 0.0;
    sum += M[0][0]*op_sobel[0][0] + M[0][1]*op_sobel[0][1] + M[0][2]*op_sobel[0][2];
    sum += M[1][0]*op_sobel[1][0] + M[1][1]*op_sobel[1][1] + M[1][2]*op_sobel[1][2];
    sum += M[2][0]*op_sobel[2][0] + M[2][1]*op_sobel[2][1] + M[2][2]*op_sobel[2][2];
    return sum;
}
cv::Mat Abs_Sobel_V(cv::Mat I)
{
    //copia de la imagen a la que se le aplicara el filtro
    cv::Mat newI;

    I.copyTo(newI);

    //matriz formada por pixel
    float Mpp[3][3];

    //maximo valor posible del filtro 
    //(1+2+1)*255=1020
    float max_value = 1020;

    for (int i=0;i<I.rows;i++)
    {
        for (int j=0;j<I.cols;j++)
        {
            //Obtener la matriz de 3x3 asociada a cada pixel para poder aplicar convolucion
            for (int u=-1;u<2;u++)
                for (int v=-1;v<2;v++)
                {
                    //si no es pixel valido (si es borde)
                    if ((i+u)*I.step + (j+v)*I.channels() < 0 || (i+u)*I.step + (j+v)*I.channels() > I.rows*I.step)
                        Mpp[u+1][v+1] = 0;
                    //si es valido
                    else
                        Mpp[u+1][v+1] = I.data[(i+u)*I.step + (j+v)*I.channels()];
                }
            
            //se aplica convolucion, se normaliza y se saca el valor absoluto
            newI.data[i*I.step + j*I.channels() + 0] = (abs(Conv(Mpp))/max_value)*255;       
        }
    }
    return newI;
}


int main(int argc, char *argv[])
{

    char* path = argv[1];

    cv::Mat imgGRAY;

    //cv::Mat img = cv::imread(path,1), imgF;
    cv::Mat img, img2, imgF;
    cv::VideoCapture cap(path);
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if( !cap.isOpened()){
         std::cout << "Cannot open the video file" << std::endl;
         return -1;
    }
    for(;;)
    {
        cap >> img;
        cv::resize(img, img, cv::Size(img.cols/3, img.rows/3));
        if( img.empty() ) break; // end of video stream
        imshow("Presione ESC para salir", img);
        std::cout << "pulse ESC para detener la captura" << std::endl;
        if( cv::waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
    }
    cv::destroyWindow("Presione ESC para salir");

    cv::cvtColor(img, imgGRAY, cv::COLOR_RGB2GRAY);
    
    imgF = Abs_Sobel_V(imgGRAY);

    cv::imshow("detector de bordes", imgF);

    cv::waitKey(0);

    return 1;
}


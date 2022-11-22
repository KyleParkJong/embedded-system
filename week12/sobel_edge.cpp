#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/photo.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){

    VideoCapture cap;
    cap.open("/dev/video0", CAP_V4L2);
    int height, width;
	int n_height, n_width;
	float R_val, G_val, B_val;
	float average_gray;
    if(!cap.isOpened()){
        printf("Can't open Camera\n");
        return -1;
    }

    // Default resolutions of the frame are obtained. The default resolutions are system dependent.
    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    // Define the codec and create VideoWriter object. The output is stored in 'outcpp.avi' file
    VideoWriter video("sobel.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));

    printf("Open Camerea\n");
    Mat img;
    int count=0; int max = 0;

    if(argc > 1){
        max = 100;
    }
    else {
        max = 100;
    }

    while(count <= max){
        cap.read(img);
        height = img.rows;
        width = img.cols;
        Mat gray(height, width, CV_8UC1);
        Mat sobelX, sobelY, sobel;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                R_val = img.at<Vec3b>(i, j)[2];
                G_val = img.at<Vec3b>(i, j)[1];
                B_val = img.at<Vec3b>(i, j)[0];

                average_gray = (int)((R_val + G_val + B_val) / 3);

                gray.at<uchar>(i, j) = average_gray;
            }
        }
        Sobel(img, sobelX, CV_8U, 1, 0);
        Sobel(img, sobelY, CV_8U, 0, 1);
        sobel = abs(sobelX) + abs(sobelY);
        if (img.empty()) break;
        video.write(sobel);
        count++;
    }

    cap.release();
    video.release();

    return 0;
}

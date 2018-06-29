#include <iostream>

#include "projectfiltering.h"
using namespace std;


int main()
{
    ProjectFiltering myProcessing;
    vector<string> files;
    vector<cv::Mat> images;
    vector<cv::Mat> imagesHSV;
    files=myProcessing.readImageFile("Sample1.txt");
    images=myProcessing.setSampleImages(files);
    myProcessing.selectRoiForImages(images);
    imagesHSV=myProcessing.changeColorSpace(images,CV_BGR2HSV);
    myProcessing.splitColorSpace(imagesHSV);
    myProcessing.findKeyPoints(images,100);
//    cv::pyrDown(im1,im4,cv::Size(im1.cols/2,im1.rows/2));
//    cv::Mat im2=im4(cv::Rect(450,450,1200,1000));




    cv::waitKey(0);
    return 0;
}

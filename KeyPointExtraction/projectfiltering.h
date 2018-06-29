#ifndef PROJECTFILTERING_H
#define PROJECTFILTERING_H
#include <vector>
#include <iostream>
#include <fstream>
#include "opencv2/opencv.hpp"
#include "opencv2/tracking.hpp"///select roi is part of this api
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace std;

struct key_points{
    std::vector<cv::KeyPoint> keypoints_object;
    cv::Mat descriptors_object;
};

class ProjectFiltering
{
public:
    ProjectFiltering();

    vector<string> readImageFile(string path);
    vector<cv::Mat> setSampleImages(vector<string> &paths);
    cv::Rect selectRoiForImages(vector<cv::Mat> &images);
    vector<cv::Mat> filterUsingBilateral(vector<cv::Mat> &images, int pixelDiameter, double sigmaColorSpace, double sigmaCoordinateSpace);
    vector<cv::Mat> changeColorSpace(vector<cv::Mat> &images,int code);
    void splitColorSpace(vector<cv::Mat> &images);
    vector<key_points> findKeyPoints(vector<cv::Mat> &images, int nFeatures);
    void downSampleImage(cv::Mat &image);
private:
    cv::Mat ActualImage;
    string path_local="C:/Users/Clein Sarmiento/Desktop/secondmasters/KaLi/Semester1/Project A KaLi/Programm/bin/Sample 1/";
    vector<cv::Mat> imagesHueChannel;
    vector<cv::Mat> imagesSaturationChannel;
    vector<cv::Mat> imagesValueChannel;
protected:
};

#endif // PROJECTFILTERING_H

#include "projectfiltering.h"

projectFiltering::projectFiltering()
{

}

vector<string> projectFiltering::readImageFile(string path){
    ifstream file(path);
    string current_line;
    vector<string> fileNames;
    while(getline(file,current_line)){
        fileNames.push_back(current_line);
    }
    file.close();
    return fileNames;
}

vector<cv::Mat> projectFiltering::setSampleImages(vector<string> &paths){
    vector<cv::Mat> images;
    cv::Mat current_image;
    for(int i=0;i<paths.size();i++){
        current_image=cv::imread(paths.at(i));
        images.push_back(current_image);
    }
    return images;
}


cv::Rect projectFiltering::selectRoiForImages(vector<cv::Mat> &images){
    cv::Rect roi;
    roi = cv::selectROI(images.at(0));
    //Validating selection
    char myKey='n';
    while(myKey!='y'){
        for (int i=0;i<images.size();i++){
            cv::Mat croppedImage=images.at(i)(roi);
            cv::imshow("cropped",croppedImage);
            cv::waitKey(1000);
        }
        cout>>"Is the are selected good for alla the pictures? \n'y' for yes and continue \n 'n' or any other character to start again">>endl;
        cin<<myKey;
    }
    //then select the roi for all images
    for (int i=0;i<images.size();i++){
        cv::Mat croppedImage=images.at(i)(roi);
        images.at(i)=croppedImage;
    }
    return roi;
}


vector<cv::Mat> projectFiltering::filterUsingBilateral(vector<cv::Mat> &images,int pixelDiameter, double sigmaColorSpace, double sigmaCoordinateSpace){
    vector<cv::Mat> results;
    for(int i=0;i<images.size();i++){
        cv::Mat result;
        cv::bilateralFilter(images.at(i),result,pixelDiameter,sigmaColorSpace,sigmaCoordinateSpace);
        results.push_back(result);
    }
    return results;
}

vector<cv::Mat> projectFiltering::changeColorSpace(vector<cv::Mat> &images,int code){
    vector<cv::Mat> results;
    for(int i=0;i<images.size();i++){
        cv::Mat result;
        cv::cvtColor(images.at(i),result,code);
        results.push_back(result);
    }
    return results;
}

vector<key_points> projectFiltering::findKeyPoints(vector<cv::Mat> &images){

}

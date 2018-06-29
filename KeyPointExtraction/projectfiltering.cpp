#include "projectfiltering.h"

ProjectFiltering::ProjectFiltering()
{

}

vector<string> ProjectFiltering::readImageFile(string path){
    ifstream file(path_local+path);
    string current_line;
    vector<string> fileNames;
    while(getline(file,current_line)){
        fileNames.push_back(current_line);
    }
    file.close();
    return fileNames;
}

vector<cv::Mat> ProjectFiltering::setSampleImages(vector<string> &paths){
    vector<cv::Mat> images;
    cv::Mat current_image;
    for(int i=0;i<paths.size();i++){
        string location=path_local+paths.at(i);
        current_image=cv::imread(location);
        downSampleImage(current_image);
        images.push_back(current_image);
    }
    return images;
}

void ProjectFiltering::downSampleImage(cv::Mat &image){
    cv::pyrDown(image,image,cv::Size(image.cols/2,image.rows/2));
    image=image(cv::Rect(450,450,1200,1000));
}

cv::Rect ProjectFiltering::selectRoiForImages(vector<cv::Mat> &images){
    cv::Rect roi;
    //Validating selection
    char myKey='n';
    while(myKey!='y'){
        roi = cv::selectROI(images.at(0));
        for (int i=0;i<images.size();i++){
            cv::Mat croppedImage=images.at(i)(roi);
            cv::imshow("cropped",croppedImage);
            cv::waitKey(500);
        }
        cv::destroyAllWindows();
        cout<<"Is the are selected good for all the pictures? \n'y' for yes and continue \n 'n' or any other character to start again"<<endl;
        cin>>myKey;
    }
    //then select the roi for all images
    for (int i=0;i<images.size();i++){
        cv::Mat croppedImage=images.at(i)(roi);
        images.at(i)=croppedImage;
    }
    return roi;
}


vector<cv::Mat> ProjectFiltering::filterUsingBilateral(vector<cv::Mat> &images,int pixelDiameter, double sigmaColorSpace, double sigmaCoordinateSpace){
    vector<cv::Mat> results;
    for(int i=0;i<images.size();i++){
        cv::Mat result;
        cv::bilateralFilter(images.at(i),result,pixelDiameter,sigmaColorSpace,sigmaCoordinateSpace);
        results.push_back(result);
    }
    return results;
}

vector<cv::Mat> ProjectFiltering::changeColorSpace(vector<cv::Mat> &images,int code){
    vector<cv::Mat> results;
    for(int i=0;i<images.size();i++){
        cv::Mat result;
        cv::cvtColor(images.at(i),result,code);
        results.push_back(result);
        cv::imshow("HSVColor",result);
        cv::imshow("Normal",images.at(i));
        cv::waitKey(500);
    }
    cv::destroyWindow("HSVColor");
    cv::destroyWindow("Normal");
    return results;
}
/// splits the Hue Saturation Value channels of the Image
void ProjectFiltering::splitColorSpace(vector<cv::Mat> &images){
    cv::Mat hsv[3];
    for(int i=0;i<images.size();i++){
        split(images.at(i),hsv);
        imagesHueChannel.push_back(hsv[0]);
        imagesSaturationChannel.push_back(hsv[1]);
        imagesValueChannel.push_back(hsv[2]);
    }
}

vector<key_points> ProjectFiltering::findKeyPoints(vector<cv::Mat> &images, int nFeatures){
    //initialize detector parameters
    vector<key_points> output;
    cv::Ptr<cv::FeatureDetector> detector;
    cv::Ptr<cv::DescriptorExtractor> extractor;
    std::vector<cv::KeyPoint> keyPoint_object;
    cv::Mat descriptor_object;
    cv::Mat imageKeyPoints;
    key_points points;
    //-- Step 1: Detect the keypoints using SIFT Detector and calculate descriptors SIFT
    detector=cv::xfeatures2d::SIFT::create(nFeatures);
    extractor=cv::xfeatures2d::SiftDescriptorExtractor::create(nFeatures);
    for(int i=0;i<images.size();i++){
        detector->detect(images.at(i),keyPoint_object);
        extractor->compute(images.at(i),keyPoint_object,descriptor_object);
        points.keypoints_object=keyPoint_object;
        points.descriptors_object=descriptor_object;
        output.push_back(points);
        cv::drawKeypoints(images.at(i),keyPoint_object,imageKeyPoints);
        cv::imshow("keyPoints Extracted",imageKeyPoints);
        cv::waitKey(500);
    }

    return output;
}

#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>


using namespace std;
using namespace cv;


string IMG_TOPIC = "/mynteye/left/image_color";  // 订阅的图像话题

void img_callback(const sensor_msgs::ImageConstPtr& img_msg)
{

    cv_bridge::CvImageConstPtr ptr;
    ptr = cv_bridge::toCvCopy(img_msg, sensor_msgs::image_encodings::BGR8);  // 将8UC3转换为BGR8类型

    cv::Mat show_img = ptr->image.clone();  // 取出转换后的图像

    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
    //内参矩阵
    cameraMatrix.at<double>(0, 0) = 351.41;
    cameraMatrix.at<double>(0, 2) = 320.90;
    cameraMatrix.at<double>(1, 1) = 351.46;
    cameraMatrix.at<double>(1, 2) = 247.90;
    //畸变参数
    Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
    distCoeffs.at<double>(0, 0) = -0.28706;
    distCoeffs.at<double>(1, 0) = 0.069023;
    distCoeffs.at<double>(2, 0) = 0.00036239;
    distCoeffs.at<double>(3, 0) = 0.00070190;
    distCoeffs.at<double>(4, 0) = 0;


    Mat view, rview, un_map1, un_map2;
    Size imageSize;
    imageSize = show_img.size();

    initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(), cameraMatrix, imageSize, CV_32FC1, un_map1, un_map2);
    remap(show_img, show_img, un_map1, un_map2, INTER_LINEAR);

    cv::imshow("vis", show_img);
    cv::waitKey(5);

}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "dis");
    ros::NodeHandle n;

    ros::Subscriber sub_img = n.subscribe(IMG_TOPIC, 1000, img_callback);  

    ros::spin();

    return 0;
}
 #ifndef __CAMERA_NODE_H__
 #define __CAMERA_NODE_H__
 
 #define OPENCV
 #include <ros/ros.h>
 #include <iostream>
 #include <fstream>
 #include <image_transport/image_transport.h>
 #include <cv_bridge/cv_bridge.h>
 #include <sensor_msgs/image_encodings.h>
 #include <opencv2/imgproc/imgproc.hpp>
 #include <opencv2/highgui/highgui.hpp>
 #include <yolo_v2_class.hpp>
 #include "reachy_moveit/position_msg.h"
 
 class ImageConverter :public Detector
 {
    public:
        ImageConverter(std::string yolo_cfg,std::string yolo_weights);
        ~ImageConverter();
        void imageCb(const sensor_msgs::ImageConstPtr& msg);
        void yolo();
        void DrawBox(cv::Mat img, cv::String name, bbox_t obj);
        void publish();
     
    private:
        ros::NodeHandle nh_;
        image_transport::ImageTransport it_;
        image_transport::Subscriber image_sub_;
        ros::Publisher position_pub;
        reachy_moveit::position_msg position_msg;
        cv::Mat mat;
        //image_transport::Publisher image_pub_;
 };
 
 #endif
 
 

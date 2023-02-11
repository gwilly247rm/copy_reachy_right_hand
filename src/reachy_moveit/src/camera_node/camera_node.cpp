#include "camera_node.h"

using namespace cv;
using namespace std;

ImageConverter::ImageConverter(string yolo_cfg,string yolo_weights):Detector(yolo_cfg,yolo_weights),it_(nh_)
{
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/camera/color/image_raw", 1,
                               &ImageConverter::imageCb, this);
    //  image_pub_ = it_.advertise("/image_converter/output_video", 1);
    
    cv::namedWindow("Image_window");
}

ImageConverter::~ImageConverter()
{
    destroyWindow("Image_window");
}

void ImageConverter::imageCb(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    
    mat=cv_ptr->image;
    
   // imshow("Image_window", mat);
  //  cv::waitKey(1);
    
    yolo();
    
    // Output modified video stream
    //image_pub_.publish(cv_ptr->toImageMsg());
}

void ImageConverter::yolo()
{
    vector<bbox_t> objList = detect(mat,0.5);
    
    for(size_t i = 0; i < objList.size(); i++)
    {
        if(objList[i].prob*100>=70 && objList[i].obj_id==3)
        {
                DrawBox(mat, "MarkingPen", objList[i]);
                cout<<"3"<<endl;
        }
        position_msg.x=objList[i].x + (objList[i].w/2);
        position_msg.y=objList[i].y + (objList[i].h/2);
        cout<<(position_msg.x+320)<<endl;
        cout<<(position_msg.y+240)<<endl;
    }
    imshow("Image_window", mat);
    cv::waitKey(1);
    publish();
}

void ImageConverter::DrawBox(Mat img, String name, bbox_t obj){
    putText(img, name+" : "+to_string((int)(obj.prob*100))+"%", Point(obj.x, obj.y),
            0, 0.5, Scalar(255, 0, 0), 2);
    rectangle(img, Point(obj.x, obj.y),
              Point(obj.x + obj.w, obj.y + obj.h),
              Scalar(255, 0, 0), 1);
}

void ImageConverter::publish()
{
    position_pub = nh_.advertise<reachy_moveit::position_msg>("position", 1000);
    ros::Rate loop_rate(5);
    position_pub.publish(position_msg);
    loop_rate.sleep();
}

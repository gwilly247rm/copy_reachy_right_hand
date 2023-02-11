#include "camera_node.h"

using namespace std;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_converter");
    ImageConverter ic("/home/ical/ocean/reachy_eai_ws/devel/yolo/yolov3-tiny.cfg", "/home/ical/ocean/reachy_eai_ws/devel/yolo/yolov3-tiny_final.weights");
    ros::spin();
    return 0;
}

#ifndef __REACHY_NODE_H__
#define __REACHY_NODE_H__

#include <ros/ros.h>
#include <iostream>
#include "reachy_moveit/joint_msg.h"
#include "std_msgs/UInt16.h"
#include "dynamixel.h"
#include "reachy.h"

class ReachyNode :public Reachy
{
    public:
        ReachyNode(std::string portName);
        int init(int speed, STATE servoState);
        int process();
        void poweroff();
    private:
        std::vector<int> joint;
        ros::NodeHandle n;
        ros::Subscriber joint_sub;
        ros::Subscriber gripper_sub;
        void jointCallback(const reachy_moveit::joint_msg& joint_msg);
        void gripperCallback(const std_msgs::UInt16ConstPtr& msg);
        ros::Publisher armIsMoving_pub;
        std_msgs::UInt16 armIsMoving_msg;
};

#endif

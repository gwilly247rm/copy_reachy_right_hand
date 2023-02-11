#ifndef __MOVEIT_NODE_H__
#define __MOVEIT_NODE_H__

#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/robot_trajectory/robot_trajectory.h>
#include <iostream>

#include "std_msgs/UInt16.h"
#include "reachy_moveit/joint_msg.h"
#include "reachy_moveit/position_msg.h"

#define PI 3.14159265f

typedef struct{
    float x;
    float y;
    float z;
}Center;

class MoveitNode :public moveit::planning_interface::MoveGroupInterface
{
    public:
        MoveitNode(std::string plan_group);
        void init();
        void publish();
        void publishOnce();
        void getCurrentArmState();
        void transJointDegree();
        void movexyz(float x, float y, float z, bool Rel);
        void catchItem();
        void putItem();
        //获取终端link的名称
        std::string end_effector_link = getEndEffectorLink();
        //获取当前位姿数据为机械臂运动的起始位姿
        geometry_msgs::Pose start_pose;

    private:
        ros::NodeHandle n;
        ros::Publisher joint_pub;
        ros::Publisher gripper_pub;
        ros::Subscriber position_sub;
        ros::Subscriber armIsMoving_sub;
        reachy_moveit::joint_msg joint_msg;
        reachy_moveit::position_msg position_msg;
        std_msgs::UInt16 gripper_msg;
        std::vector<double> joint_group_positions;
        Center center;
        void positionCallback(const reachy_moveit::position_msg& position_msg);
        //初始化路径点向量
        std::vector<geometry_msgs::Pose> waypoints;
        void armIsMovingCallback(const std_msgs::UInt16ConstPtr& msg);
        int check;
        bool Rel;
};

#endif

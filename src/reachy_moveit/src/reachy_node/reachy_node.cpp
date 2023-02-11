#include "reachy_node.h"

using namespace std;

ReachyNode::ReachyNode(string portName):Reachy(portName), joint(8) 
{
    joint = {90, 90, 180, 180, 150, 150, 150, 150};
}

int ReachyNode::init(int speed, STATE servoState)
{
    int iResult = 0;
    iResult = setSpeed(speed);
    if(iResult != 0)
        return -1;
    
    iResult = setServoState(servoState);
    if(iResult != 0)
        return -1;
    
    return 0;
}

int ReachyNode::process()
{
    while(ros::ok())
    {
        ros::Rate loop_rate(5);
        
        joint_sub = n.subscribe("joint",2,&ReachyNode::jointCallback, this);
        
        loop_rate.sleep();
        ros::spinOnce();
        
        gripper_sub = n.subscribe("gripper",2,&ReachyNode::gripperCallback, this);
        
        loop_rate.sleep();
        ros::spinOnce();
        
        int iResult = setPosition(joint);
        if(iResult != 0)
            return -1;
       
        waitForIdle();
    }
    
    poweroff();
    
    return 0;
}

void ReachyNode::jointCallback(const reachy_moveit::joint_msg& joint_msg)
{
    joint[0]=joint_msg.j1;
    joint[1]=joint_msg.j2;
    joint[2]=joint_msg.j3;
    joint[3]=joint_msg.j4;
    joint[4]=joint_msg.j5;
    joint[5]=joint_msg.j6;
    joint[6]=joint_msg.j7;
    
    ROS_INFO("Set Joint degree %d %d %d %d %d %d %d", joint[0], joint[1], joint[2], joint[3], joint[4], joint[5], joint[6]);
}

void ReachyNode::gripperCallback(const std_msgs::UInt16ConstPtr& msg)
{
    if(msg->data!=0)
    joint[7]=msg->data;
    
    ROS_INFO("Set Gripper degree %d", joint[7]); 
}

void ReachyNode::poweroff()
{ 
    joint = {90, 90, 180, 180, 150, 150, 150, 150};
    setSpeed(30);
    setPosition(joint);
    waitForIdle();
}

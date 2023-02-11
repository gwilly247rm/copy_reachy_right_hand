#include "moveit_node.h"

using namespace std;

int main(int argc, char **argv)
{
    //初始化节点
    ros::init(argc, argv, "reachy");
    //引入多线程
    ros::AsyncSpinner spinner(1);
    //开启多线程
    spinner.start();

    MoveitNode moveitnode("reachy_arm");
    
    moveitnode.init();
    
    //获取当前位姿数据为机械臂运动的起始位姿
    geometry_msgs::Pose start_pose = moveitnode.getCurrentPose(moveitnode.end_effector_link).pose;
    
    // 控制机械臂先回到初始化位置
    moveitnode.setNamedTarget("ready");
    moveitnode.move(); //规划+移动
    //sleep(1);  //停1s
    
    moveitnode.publish();
    
    /*moveitnode.setJointValueTarget(joint_group_positions);
    moveitnode.move(); //规划+移动
    sleep(1);*/
    
    ros::shutdown(); 
    return 0;
}

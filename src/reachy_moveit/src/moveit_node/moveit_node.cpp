#include "moveit_node.h"

using namespace std;

MoveitNode::MoveitNode(string plan_group):moveit::planning_interface::MoveGroupInterface(plan_group) { }

void MoveitNode::init()
{
    //设置目标位置所使用的参考坐标系
    setPoseReferenceFrame("base");
    
    //当运动规划失败后，允许重新规划
    allowReplanning(true);
    
    //设置位置(单位：米)和姿态（单位：弧度）的允许误差
    setGoalPositionTolerance(0.001);
    setGoalOrientationTolerance(0.01);
    
    //设置允许的最大速度和加速度
    setMaxAccelerationScalingFactor(1.0);
    setMaxVelocityScalingFactor(1.0);
    
    gripper_msg.data=150;
}

void MoveitNode::publish()
{
    while(ros::ok())
    {
        ros::Rate loop_rate(5);
        
        getCurrentArmState();
        transJointDegree();
        
        gripper_pub = n.advertise<std_msgs::UInt16>("gripper", 1000);
        joint_pub = n.advertise<reachy_moveit::joint_msg>("joint", 1000);
        
        gripper_pub.publish(gripper_msg);
        joint_pub.publish(joint_msg);
        loop_rate.sleep();
        
        position_sub = n.subscribe("position",2,&MoveitNode::positionCallback, this);
        loop_rate.sleep();
        ros::spinOnce();
    }
}

void MoveitNode::getCurrentArmState()
{
    //獲得當前手臂狀態
    moveit::core::RobotStatePtr current_state = getCurrentState();
    const robot_state::JointModelGroup* joint_model_group =
    getCurrentState()->getJointModelGroup("reachy_arm");
    //得到目前各馬達角度
    current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
    
    start_pose = getCurrentPose(end_effector_link).pose;
    
    cout<<"pos.x="<< start_pose.position.x<<endl;
    cout<<"pos.y="<< start_pose.position.y<<endl;
}

void MoveitNode::transJointDegree()
{
    for(unsigned int i = 0;i<joint_group_positions.size();i++)
        joint_group_positions[i]=joint_group_positions[i]*180/PI;
    
    joint_group_positions[0]=-joint_group_positions[0]+90;
    joint_group_positions[1]=-joint_group_positions[1]+90;
    joint_group_positions[2]=-joint_group_positions[2]+180;
    joint_group_positions[3]=-joint_group_positions[3]+180;
    joint_group_positions[4]=-joint_group_positions[4]+150;
    joint_group_positions[5]=-joint_group_positions[5]+150;
    joint_group_positions[6]=-joint_group_positions[6]+150;
    
    for(unsigned int i = 0;i<joint_group_positions.size();i++)
        cout<<joint_group_positions[i]<<endl;
    
    joint_msg.j1=joint_group_positions[0]+0.5;
    joint_msg.j2=joint_group_positions[1]+0.5;
    joint_msg.j3=joint_group_positions[2]+0.5;
    joint_msg.j4=joint_group_positions[3]+0.5;
    joint_msg.j5=joint_group_positions[4]+0.5;
    joint_msg.j6=joint_group_positions[5]+0.5;
    joint_msg.j7=joint_group_positions[6]+0.5;
}

void MoveitNode::positionCallback(const reachy_moveit::position_msg& position_msg)
{
    center.x=(float)position_msg.x*(-0.0016)+0.9427;
    center.y=(float)position_msg.y*(0.0108)-3.566;
    cout<<center.x<<endl;
    cout<<center.y<<endl;
    center.z=0;
    
    movexyz(0,0,0,true);
    //movexyz(center.x,center.y,center.z,false);
}

void MoveitNode::movexyz(float move_x, float move_y, float move_z, bool Rel)
{
    start_pose = getCurrentPose(end_effector_link).pose;
    
    //初始化路径点向量
    vector<geometry_msgs::Pose> waypoints;
    
    //将初始位姿加入路点列表
    waypoints.push_back(start_pose);
    
    if(Rel==true)
    {
        start_pose.position.z += move_z;
        waypoints.push_back(start_pose);
        
        start_pose.position.x += move_x;
        waypoints.push_back(start_pose);
        
        start_pose.position.y += move_y;
        waypoints.push_back(start_pose);
    }
    
    else//Rel==false
    {
        start_pose.position.z = move_z;
        waypoints.push_back(start_pose);
        
        start_pose.position.x = move_x;
        waypoints.push_back(start_pose);
        
        start_pose.position.y = move_y;
        waypoints.push_back(start_pose);
    }
    
    cout<<"1"<<endl;
    
    // 笛卡尔空间下的路径规划
	moveit_msgs::RobotTrajectory trajectory;
	const double jump_threshold = 0.0;
	const double eef_step = 0.01;
	double fraction = 0.0;
    int maxtries = 100;   //最大尝试规划次数
    int attempts = 0;     //已经尝试规划次数
 
    while(fraction < 1.0 && attempts < maxtries)
    {
        fraction = computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
        attempts++;
        
        if(attempts % 10 == 0)
            ROS_INFO("Still trying after %d attempts...", attempts);
    }
    
    if(fraction == 1)
    {   
        ROS_INFO("Path computed successfully. Moving the moveitnode.");
 
	    // 生成机械臂的运动规划数据
	    moveit::planning_interface::MoveGroupInterface::Plan plan;
	    plan.trajectory_ = trajectory;
 
	    // 执行运动
	    execute(plan);
        sleep(1);
    }
    else
    {
        ROS_INFO("Path planning failed with only %0.6f success after %d attempts.", fraction, maxtries);
    }
    
    publish();
}

void MoveitNode::armIsMovingCallback(const std_msgs::UInt16ConstPtr& msg)
{
    check=msg->data;
    
    ROS_INFO("arm is moving:%d", check); 
}

void MoveitNode::catchItem()
{
    gripper_msg.data=167;
    movexyz(0,0,-0.1,true);
}

void MoveitNode::putItem()
{
    gripper_msg.data=150;
    
    movexyz(0.1,0.1,0,true);
}

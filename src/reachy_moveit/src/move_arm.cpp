#include <ros/ros.h>
#include <iostream>

#include "reachy_node.h"

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "move");
    
    ReachyNode reachynode("/dev/ttyUSB1");
    
    int iResult = reachynode.init(50,ON);
    if(iResult != 0)
        return 0;
    
    reachynode.process();
    
    reachynode.setServoState(OFF);
    ros::shutdown(); 
    return 0;
}

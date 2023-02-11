#include <iostream>
#include <unistd.h>
#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include<geometry_msgs/Twist.h>
#include <iostream>

class Basemove
{
    public:
        Basemove();


        void msg();
        void process();
        void ctrlwheel(int mode);

    private:
        void stepcallBack(const std_msgs::Int8::ConstPtr& msg);
        void movingcallBack(const std_msgs::Int8::ConstPtr& msg);

        ros::NodeHandle nh;
        ros::Subscriber subst; 
        ros::Subscriber submo; 
        ros::Publisher pub ;
        ros::Publisher pubst ;
        ros::Publisher pubmo ;
        
	int mode;
	int step;
        int ismoving;

};

#include "basemove.h"

int main(int argc, char **argv)
{

	ros::init(argc, argv, "base_moving_with_reachy");
	Basemove basemove;
	ros::Rate loop_rate(10);

	while(ros::ok()){
		basemove.msg();
		basemove.process();
		ros::spinOnce(); 
		loop_rate.sleep();
	}
	return 0;
}


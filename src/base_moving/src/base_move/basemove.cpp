#include "basemove.h"

using namespace std;
Basemove::Basemove()
{

}
void Basemove::msg()
{
	subst = nh.subscribe("step", 100, &Basemove::stepcallBack, this);
	submo = nh.subscribe("ismoving", 100, &Basemove::movingcallBack, this);
	pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1000);
	pubst = nh.advertise<std_msgs::Int8>("step",1000);
	pubmo = nh.advertise<std_msgs::Int8>("ismoving",1000);
}
void Basemove::stepcallBack(const std_msgs::Int8::ConstPtr& msg)
{
	step = msg->data;
	printf("step = %d\n", step);
}

void Basemove::movingcallBack(const std_msgs::Int8::ConstPtr& msg)
{
	ismoving = msg->data;
	printf("ismoving = %d\n", ismoving);
}

void Basemove::process()
{
	std_msgs::Int8 msgst;
	std_msgs::Int8 msgmo;

	if(ismoving==0 && step==1)
	{
		mode = 1;
		printf("mode = %d\n",mode);
		Basemove::ctrlwheel(mode);
		msgst.data = 2;
		msgmo.data = 0;
		pubst.publish(msgst);
		pubmo.publish(msgmo);
	}
	else if(ismoving==0 && step==3)
	{
		mode = 2;
		printf("mode = %d\n",mode);
		Basemove::ctrlwheel(mode);
		msgst.data = 4;
		msgmo.data = 0;
		pubst.publish(msgst);
		pubmo.publish(msgmo);
	}
	else if(ismoving==0 && step==5)
	{
		mode = 3;
		printf("mode = %d\n",mode);
		Basemove::ctrlwheel(mode);
		msgst.data = 6;
		msgmo.data = 0;
		pubst.publish(msgst);
		pubmo.publish(msgmo);
	}
	else
	{
		mode = 4;
		printf("mode = %d\n",mode);
		Basemove::ctrlwheel(mode); 
	}
}
void Basemove::ctrlwheel(int mode)
{ 
	geometry_msgs::Twist ctrl;
	std_msgs::Int8 msg;
	ismoving = 1;
	msg.data = ismoving;
	pubmo.publish(msg);
	cout<<"87878787"<<endl;
	switch (mode) 
	{
		case 0:
			for(int i=0;i<2;i++)
			{
				for(int i=0;i<850;i++)
				{
					for(int i=0;i<500;i++)
					{
						ctrl.linear.x = 1.5;
						ctrl.angular.z = 0.0;
						pub.publish(ctrl);
						printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
					}
				}
			}
			sleep(5);
			break;
		case 1:
			sleep(5);
			for(int i=0;i<70;i++)
			{
				ctrl.linear.x = 0.0;
				ctrl.angular.z = 1.5;
				pub.publish(ctrl);
				printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
			}
			sleep(1);
			for(int i=0;i<850;i++)
			{
				for(int i=0;i<500;i++)
				{
					ctrl.linear.x = 0.3;
					ctrl.angular.z = 0.0;
					pub.publish(ctrl);
					printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
				}
			}
			sleep(1);
			for(int i=0;i<70;i++)
			{
				ctrl.linear.x = 0.0;
				ctrl.angular.z = -1.5;
				pub.publish(ctrl);
				printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
			}
			sleep(1);
			for(int i=0;i<400;i++)
			{
				for(int i=0;i<500;i++)
				{
					ctrl.linear.x = 0.3;
					ctrl.angular.z = 0.0;
					pub.publish(ctrl);
					printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
				}
			}
			sleep(1);
			for(int i=0;i<70;i++)
			{
				ctrl.linear.x = 0.0;
				ctrl.angular.z = -1.5;
				pub.publish(ctrl);
				printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
			}
			sleep(1);
			break;

		case 2:
			for(int i=0;i<70;i++)
			{
				ctrl.linear.x = 0.0;
				ctrl.angular.z = -1.5;
				pub.publish(ctrl);
				printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
			}
			sleep(1);
			for(int i=0;i<400;i++)
			{
				for(int i=0;i<500;i++)
				{
					ctrl.linear.x = 1.5;
					ctrl.angular.z = 0.0;
					pub.publish(ctrl);
					printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
				}
			}
			sleep(1);
			for(int i=0;i<70;i++)
			{
				ctrl.linear.x = 0.0;
				ctrl.angular.z = 1.5;
				pub.publish(ctrl);
				printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
			}
			sleep(1);
			for(int i=0;i<2;i++)
			{
				for(int i=0;i<850;i++)
				{
					for(int i=0;i<500;i++)
					{
						ctrl.linear.x = 1.5;
						ctrl.angular.z = 0.0;
						pub.publish(ctrl);
						printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
					}
				}
			}
			sleep(1);
			for(int i=0;i<70;i++)
			{
				ctrl.linear.x = 0.0;
				ctrl.angular.z = 1.5;
				pub.publish(ctrl);
				printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
			}
			sleep(1);
			for(int i=0;i<400;i++)
			{
				for(int i=0;i<500;i++)
				{
					ctrl.linear.x = 1.5;
					ctrl.angular.z = 0.0;
					pub.publish(ctrl);
					printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
				}
			}
			sleep(1);
			for(int i=0;i<70;i++)
			{
				ctrl.linear.x = 0.0;
				ctrl.angular.z = 1.5;
				pub.publish(ctrl);
				printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
			}
			sleep(1);
			break;

		case 3:
			for(int i=0;i<70;i++)
			{
				ctrl.linear.x = 0.0;
				ctrl.angular.z = 1.5;
				pub.publish(ctrl);
				printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
			}
			sleep(1);
			for(int i=0;i<400;i++)
			{
				for(int i=0;i<500;i++)
				{
					ctrl.linear.x = 1.5;
					ctrl.angular.z = 0.0;
					pub.publish(ctrl);
					printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
				}
			}
			sleep(1);
			for(int i=0;i<70;i++)
			{
				ctrl.linear.x = 0.0;
				ctrl.angular.z = -1.5;
				pub.publish(ctrl);
				printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
			}
			sleep(1);
			for(int i=0;i<850;i++)
			{
				for(int i=0;i<500;i++)
				{
					ctrl.linear.x = 1.5;
					ctrl.angular.z = 0.0;
					pub.publish(ctrl);
					printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
				}
			}
			sleep(1);
			for(int i=0;i<70;i++)
			{
				ctrl.linear.x = 0.0;
				ctrl.angular.z = -1.5;
				pub.publish(ctrl);
				printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
			}
			sleep(1);
			break;
		case 4:
			ctrl.linear.x = 0.0;
			ctrl.angular.z = 0.0;
			pub.publish(ctrl);
			printf("linear.x= %lf, angular.z= %lf\n",ctrl.linear.x, ctrl.angular.z);
			break;
		default:
			cout<<"97979797"<<endl;
	}


}

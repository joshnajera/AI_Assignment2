#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"
#include <iostream>
#include <string>
#include <stdio.h>

void msgCallback(const std_msgs::Int32MultiArray::ConstPtr& msg) {
	int input[50];
	int sum = 0;
	//	Iterate through the numbers passed in
	for(std::vector<int>::const_iterator it = msg->data.begin(); 
			it != msg->data.end(); ++it){
		int output = *it;
		sum += output;	//	Sum them
	}
	//	Display
	ROS_INFO("The sum of the integers: [%i]", sum);
	ROS_INFO("Now exiting...");
	exit(0);
}


int main(int argc, char **argv) {
	ros::init(argc, argv, "Listener");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe
		<std_msgs::Int32MultiArray>("numbers", 1000, msgCallback);
		//  Subscribes to topic "numbers" and sets up a callback
		//  function for when a message arrives
	ros::spin();	//  Makes the callbacks when necessary
}

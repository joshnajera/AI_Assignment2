#include <ros/ros.h>
#include "std_msgs/Int32MultiArray.h"
#include <sstream>
#include <iostream>
#include <stdio.h>

int main(int argc, char **argv){


	//	Setting up node
	std_msgs::Int32MultiArray msg;	//  Defines the message obj
	ros::init(argc, argv, "Publisher");	//  Init node named 'Publisher'
	ros::NodeHandle nh;	// Gets a node handle (enables msg advrtsng
	ros::Publisher pub = 
		nh.advertise<std_msgs::Int32MultiArray>("numbers", 1000);
		//  Advertises the topic "numbers" 
		//  with a message queue queue_size of 1000
	ros::Rate loop_rate(2);	// Defines loop frequency (Hz)


	//	Getting input
	char input[100];
	std::cout<<"Enter a set of integers: "<<std::endl;
	std::cin.getline(input, sizeof(input));
	ROS_INFO("Publishing number list of: %s", input);

	
	//	Splitting off space
	char * input_integer;
	input_integer = strtok (input," ");
	while(input_integer != NULL) {
		//	Place each number into the message's data
		msg.data.push_back(atoi(input_integer));
		input_integer = strtok(NULL," ");
	}


	//	Publish message
	while (ros::ok()) {	//  Loops while ROS node is in good standing
		//std::stringstream ss;	//  Defines a string stream
		// ss << "Hello world" << count;	//  Loads it with a string
		//msg.data = ss.str();		//  Converts to string and 
						//  stores it in message obj

		ROS_INFO("Sending...");
		pub.publish(msg);	//  Publishes to outgoing msg queue
		loop_rate.sleep();	//  Sleeps based on loop_rate
	}
}

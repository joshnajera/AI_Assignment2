#include <ros/ros.h>
#include "std_msgs/Int32MultiArray.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <set>

using namespace std;

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
	while(true){
		bool valueError = false, countError = false;
		char input[100];
		char * input_integer;
		int count = 0;
		set<int> values;

		std::cout<<"Enter a set of integers: "<<std::endl;
		std::cin.getline(input, sizeof(input));

		
		//	Splitting off space
		input_integer = strtok (input," ");
		while (input_integer != NULL) {
			//	Place each number into the message's data
			int value = atoi(input_integer);
			if (value <= 100 && count < 5){
				values.insert(value);
				count++;
				input_integer = strtok(NULL," ");
				continue;
			}
			else if(value > 100)
				valueError = true;
			else
				countError = true;
			break;

		}

		if (valueError) {
			ROS_INFO("Cannot have a value greater than 100.");
			continue;
		}
		else if(countError){
			ROS_INFO("Cannot have more than 5 entries.");
			continue;
		}

		for(set<int>::iterator it = values.begin(); it != values.end(); it++) {
				msg.data.push_back(*it);
		}
		ROS_INFO("Sending...");
		break;
	}


	//	Publish message
	while (ros::ok()) {	//  Loops while ROS node is in good standing
		//std::stringstream ss;	//  Defines a string stream
		// ss << "Hello world" << count;	//  Loads it with a string
		//msg.data = ss.str();		//  Converts to string and 
						//  stores it in message obj

		pub.publish(msg);	//  Publishes to outgoing msg queue
		loop_rate.sleep();	//  Sleeps based on loop_rate
	}
}

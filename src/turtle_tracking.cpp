#include "ros/ros.h"
#include "turtlesim/Color.h"
#include "std_msgs/String.h"

float red,green,blue;

void colorCallback(const turtlesim::Color::ConstPtr& msg)
{
  ROS_INFO("I heard: Red [%u], Green [%u], Blue [%u]", msg->r, msg->g, msg->b);
  red=msg->r;
  green=msg->g;
  blue=msg->b;
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "turtle_tracking");

  ros::NodeHandle n;

  ros::Rate loop_rate(20);

  ros::Subscriber sub_color = n.subscribe("turtle1/color_sensor", 1000, colorCallback);

  ros::Publisher control_pub = n.advertise<std_msgs::String>("status", 10);
  std_msgs::String status;
  status.data="NOTHING";
  while (ros::ok())
  {    
    
    if(red>200 && green>200 && blue>200){
      status.data="FOUND";
    } 
    control_pub.publish(status);      
    
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
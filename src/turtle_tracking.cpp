#include "ros/ros.h"
#include "turtlesim/Color.h"

void colorCallback(const turtlesim::Color::ConstPtr& msg)
{
  ROS_INFO("I heard: Red [%u], Green [%u], Blue [%u]", msg->r, msg->g, msg->b);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("turtle1/color_sensor", 1000, colorCallback);

  ros::spin();

  return 0;
}
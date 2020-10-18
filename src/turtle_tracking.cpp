#include "ros/ros.h"
#include "turtlesim/Color.h"
#include "turtlesim/Pose.h"

void colorCallback(const turtlesim::Color::ConstPtr& msg)
{
  ROS_INFO("I heard: Red [%u], Green [%u], Blue [%u]", msg->r, msg->g, msg->b);
}

void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
  ROS_INFO("Turtle is at: x [%f], y [%f], theta [%f], linear velocity [%f], angular velocity [%f]", 
    msg->x, msg->y, msg->theta, msg->linear_velocity, msg->angular_velocity);
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "turtle_tracking");

  ros::NodeHandle n;

  ros::Subscriber sub_color = n.subscribe("turtle1/color_sensor", 1000, colorCallback);
  ros::Subscriber sub_pose = n.subscribe("turtle1/pose", 1000, poseCallback);


  ros::spin();

  return 0;
}
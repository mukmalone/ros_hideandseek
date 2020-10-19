#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <cmath>

float x, y, theta;

void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
    x = msg->x;
    y = msg->y;
    theta = msg->theta;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_move");
 
    ros::NodeHandle n;

    ros::Subscriber sub_pose = n.subscribe("turtle1/pose", 1000, poseCallback);
    ros::Publisher control_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
 
    ros::Rate loop_rate(10);
    int cnt = 0;
    geometry_msgs::Twist control_command;
    control_command.linear.y = 0.0;
    control_command.linear.z = 0.0;
    control_command.angular.x = 0.0;
    control_command.angular.y = 0.0;

    //target
    double target_x, target_y;
    n.getParam("/object_origin_x", target_x);
    n.getParam("/object_origin_y", target_y);

    while (ros::ok())
    {
        control_command.linear.x = 1.5 * sqrt( pow(target_x-x,2) + pow(target_y-y,2) );            
        control_command.angular.z = 4 * (atan2(target_y-y, target_x-x) - theta ); 
        control_pub.publish(control_command);
        ros::spinOnce();
        loop_rate.sleep();
        ++cnt;
        ROS_INFO("Turtle is at: x [%f], y [%f], theta [%f]",x, y, theta);
    }

    return 0;
}
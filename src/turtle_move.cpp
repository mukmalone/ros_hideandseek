#include "ros/ros.h"
#include "geometry_msgs/Twist.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_move");
 
    ros::NodeHandle n;

    ros::Publisher control_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
 
    ros::Rate loop_rate(1);

    while (ros::ok())
    {
        geometry_msgs::Twist control_command;

        control_command.linear.x = 5.0;
        control_command.linear.y = 0.0;
        control_command.linear.z = 0.0;
        control_command.angular.x = 0.0;
        control_command.angular.y = 0.0;
        control_command.angular.z = 5.0;

        control_pub.publish(control_command);
        ros::spinOnce();
        loop_rate.sleep();
  
    }

    return 0;
}
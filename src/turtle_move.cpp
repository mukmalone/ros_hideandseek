#include "ros/ros.h"
#include "geometry_msgs/Twist.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_move");
 
    ros::NodeHandle n;

    ros::Publisher control_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
 
    ros::Rate loop_rate(.5);
    int cnt = 0;
    geometry_msgs::Twist control_command;

    while (ros::ok())
    {
        if(cnt==0){
            control_command.linear.x = 0.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 0.0; 
        }
        else if(cnt==1){
            control_command.linear.x = 10.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 0.0; 
        }
        else if(cnt==2){
            control_command.linear.x = 0.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 1.5707; 
        }
        else if(cnt==3){
            control_command.linear.x = 0.5;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 0.0; 
        }
        else if(cnt==4){
            control_command.linear.x = 0.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 1.5707; 
        }
        else if(cnt==5){
            control_command.linear.x = 10.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 0.0; 
        }
        else if(cnt==6){
            control_command.linear.x = 0.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = -1.5707; 
        }
        else if(cnt==7){
            control_command.linear.x = 0.5;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 0.0; 
        }
        else if(cnt==8){
            control_command.linear.x = 0.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = -1.5707; 
        }
        else if(cnt==9){
            control_command.linear.x = 10.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 0.0; 
        }
        else if(cnt==10){
            control_command.linear.x = 0.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 1.5707; 
        }
        else if(cnt==11){
            control_command.linear.x = 0.5;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 0.0; 
        }
        else if(cnt==12){
            control_command.linear.x = 0.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 1.5707; 
        }
        else if(cnt==13){
            control_command.linear.x = 10.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 0.0; 
        }
        else if(cnt==14){
            control_command.linear.x = 0.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = -1.5707; 
        }
        else if(cnt==15){
            control_command.linear.x = 0.5;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 0.0; 
        }
        else if(cnt==16){
            control_command.linear.x = 0.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = -1.5707; 
        }
        else if(cnt==17){
            control_command.linear.x = 10.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 0.0; 
        }
        else if(cnt==18){
            control_command.linear.x = 0.0;
            control_command.linear.y = 0.0;
            control_command.linear.z = 0.0;
            control_command.angular.x = 0.0;
            control_command.angular.y = 0.0;
            control_command.angular.z = 0.0; 
        }
        control_pub.publish(control_command);
        ros::spinOnce();
        loop_rate.sleep();
        ++cnt;
    }

    return 0;
}
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <std_msgs/String.h>
#include <cmath>

float x, y, theta;
bool complete;

void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
    x = msg->x;
    y = msg->y;
    theta = msg->theta;
}

void statusCallback(const std_msgs::String::ConstPtr& msg)
{
    if(msg->data == "FOUND"){
        complete=true;
    }
}

int main(int argc, char **argv)
{
    //fixed zig-zag search pattern     
    int num_goals=19;
    float goals[num_goals][2];
    goals[0][0]=10.0; goals[0][1]=1.0;
    goals[1][0]=10.0; goals[1][1]=2.0;
    goals[2][0]=1.0; goals[2][1]=2.0;
    goals[3][0]=1.0; goals[3][1]=3.0;
    goals[4][0]=10.0; goals[4][1]=3.0;
    goals[5][0]=10.0; goals[5][1]=4.0;
    goals[6][0]=1.0; goals[6][1]=4.0;
    goals[7][0]=1.0; goals[7][1]=5.0;
    goals[8][0]=10.0; goals[8][1]=5.0;
    goals[9][0]=10.0; goals[9][1]=6.0;
    goals[10][0]=1.0; goals[10][1]=6.0;
    goals[11][0]=1.0; goals[11][1]=7.0;
    goals[12][0]=10.0; goals[12][1]=7.0;
    goals[13][0]=10.0; goals[13][1]=8.0;
    goals[14][0]=1.0; goals[14][1]=8.0;
    goals[15][0]=1.0; goals[15][1]=9.0;
    goals[16][0]=10.0; goals[16][1]=9.0;
    goals[17][0]=10.0; goals[17][1]=10.0;
    goals[18][0]=1.0; goals[18][1]=10.0;

    ros::init(argc, argv, "turtle_move");
 
    ros::NodeHandle n;

    ros::Subscriber sub_pose = n.subscribe("turtle1/pose", 1000, poseCallback);
    ros::Subscriber sub_status = n.subscribe("status", 1000, statusCallback);
    ros::Publisher control_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
 
    ros::Rate loop_rate(20);
    int cnt = 0;
    const float pi = 3.14159265358979323846;
    geometry_msgs::Twist control_command;
    control_command.linear.y = 0.0;
    control_command.linear.z = 0.0;
    control_command.angular.x = 0.0;
    control_command.angular.y = 0.0;

    complete = false;
    int target_num = 0;
    while (ros::ok() && !complete)
    {                   
        float angle = atan2(goals[target_num][1]-y, goals[target_num][0]-x) - theta;
        //working on angles
        if (angle<-pi){
            angle+=2*pi;
        }
        else if (angle>pi){
            angle-=2*pi;
        }
        control_command.angular.z = 5 * (angle); 
        float adaptive_control=1;
        if(abs(control_command.angular.z)<.5){
            adaptive_control=.5;
        } else {
            adaptive_control=abs(control_command.angular.z);
        }

        control_command.linear.x = .5/adaptive_control* sqrt( pow(goals[target_num][0]-x,2) + pow(goals[target_num][1]-y,2) );
        if(complete){
            control_command.linear.x=0;
            control_command.linear.z=0;
        }

        control_pub.publish(control_command);
        ros::spinOnce();
        loop_rate.sleep();
        ++cnt;
        ROS_INFO("Turtle cmd: x [%f], ang.z [%f]",control_command.linear.x, control_command.angular.z);

        //check if we are at the goal within tolerance
        float dx, dy, tolerance=0.1;
        dx = abs(x-goals[target_num][0]);
        dy = abs(y-goals[target_num][1]);

        if(dx<=tolerance && dy<=tolerance){
            //if we are at the goal move to next goal
            target_num++;
        }

        if(target_num==(num_goals)){
            //if we have cycled through all goals stop
            //eventually this is where we will look for the color to change
            complete=true;
        }
    }

    if(complete){
        control_command.linear.x=0;
        control_command.linear.z=0;
        control_pub.publish(control_command);
        ros::spinOnce();
    }

    return 0;
}
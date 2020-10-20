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
    //fixed zig-zag search pattern     
    int num_goals=19;
    double goals[num_goals][2];
    goals[0][0]=9.0; goals[0][1]=1.0;
    goals[1][0]=9.0; goals[1][1]=2.0;
    goals[2][0]=1.0; goals[2][1]=2.0;
    goals[3][0]=9.0; goals[3][1]=3.0;
    goals[4][0]=1.0; goals[4][1]=3.0;
    goals[5][0]=9.0; goals[5][1]=4.0;
    goals[6][0]=1.0; goals[6][1]=4.0;
    goals[7][0]=9.0; goals[7][1]=5.0;
    goals[8][0]=1.0; goals[8][1]=5.0;
    goals[9][0]=9.0; goals[9][1]=6.0;
    goals[10][0]=1.0; goals[10][1]=6.0;
    goals[11][0]=9.0; goals[11][1]=7.0;
    goals[12][0]=1.0; goals[12][1]=7.0;
    goals[13][0]=9.0; goals[13][1]=8.0;
    goals[14][0]=1.0; goals[14][1]=8.0;
    goals[15][0]=9.0; goals[15][1]=9.0;
    goals[16][0]=1.0; goals[16][1]=9.0;
    goals[17][0]=9.0; goals[17][1]=10.0;
    goals[18][0]=1.0; goals[18][1]=10.0;

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


    double target_x, target_y, tolerance;
    target_x = 9.0;
    target_y = 1.0;
    tolerance = 0.05;

    bool complete = false;
    int target_num = 0;
    while (ros::ok() && !complete)
    {
        control_command.linear.x = 1.5 * sqrt( pow(goals[target_num][0]-x,2) + pow(goals[target_num][1]-y,2) );            
        control_command.angular.z = 3 * (atan2(goals[target_num][1]-y, goals[target_num][0]-x) - theta ); 
        control_pub.publish(control_command);
        ros::spinOnce();
        loop_rate.sleep();
        ++cnt;
        ROS_INFO("Turtle is at: x [%f], y [%f], theta [%f]",x, y, theta);
        //check if we are at the goal within tolerance
        double dx, dy;
        dx = abs(x-goals[target_num][0]);
        dy = abs(y-goals[target_num][1]);
        if(target_num==(num_goals-1)){
            complete=true;
        }
        if(dx<=tolerance && dy<=tolerance){
            target_num++;
        }
    }

    return 0;
}
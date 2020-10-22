#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <std_msgs/String.h>
#include <cmath>

float x, y, theta;
bool complete,enable_search;

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

void searchCallback(const std_msgs::String::ConstPtr& msg)
{
  if(msg->data=="START_SEARCH"){
    enable_search=true;
  }
}

int main(int argc, char **argv)
{
    //we need to wait until board is setup before starting the search pattern
    enable_search=false;
    //flag to signal we are end of search pattern or we found circle
    complete = false;
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
    //pose for turtle position in Go to Goal algorithm
    ros::Subscriber sub_pose = n.subscribe("turtle1/pose", 1000, poseCallback);
    //monitoring if color sensor found circle
    ros::Subscriber sub_status = n.subscribe("status", 1000, statusCallback);
    //sending velocity commands to drive turtlesim
    ros::Publisher control_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
    //topic which will monitor everything is setup
    ros::Subscriber sub_search = n.subscribe("/start_search", 1000, searchCallback); 

    ros::Rate loop_rate(20);

    //when board gets setup we exit loop
    while(!enable_search){
        ros::spinOnce();
        loop_rate.sleep();
    }

    const float pi = 3.14159265358979323846;
    geometry_msgs::Twist control_command;
    control_command.linear.y = 0.0;
    control_command.linear.z = 0.0;
    control_command.angular.x = 0.0;
    control_command.angular.y = 0.0;

    int goal_num = 0;
    while (ros::ok() && !complete)
    {                   
        float angle = atan2(goals[goal_num][1]-y, goals[goal_num][0]-x) - theta;
        //ensure angle is between -pi and pi
        if (angle<-pi){
            angle+=2*pi;
        }
        else if (angle>pi){
            angle-=2*pi;
        }
        //angular velocity
        control_command.angular.z = 5 * (angle); 
        float adaptive_control=1;
        //control to enable sharp turns and staighter paths
        if(abs(control_command.angular.z)<.5){
            adaptive_control=.5;
        } else {
            adaptive_control=abs(control_command.angular.z);
        }
        //linear velocity
        control_command.linear.x = .5/adaptive_control* sqrt( pow(goals[goal_num][0]-x,2) + pow(goals[goal_num][1]-y,2) );

        if(complete){
            //slam on brakes if we found it
            control_command.linear.x=0;
            control_command.linear.z=0;
        }

        control_pub.publish(control_command);
        ros::spinOnce();
        loop_rate.sleep();
        ROS_INFO("Turtle cmd: x [%f], ang.z [%f]",control_command.linear.x, control_command.angular.z);

        //check if we are at the goal within tolerance
        float dx, dy, tolerance=0.1;
        dx = abs(x-goals[goal_num][0]);
        dy = abs(y-goals[goal_num][1]);

        if(dx<=tolerance && dy<=tolerance){
            //if we are at the goal move to next goal
            goal_num++;
        }

        if(goal_num==(num_goals)){
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
#include <ros/ros.h>
#include <ros_hideandseek/NextGoal.h>

bool calc_next_goal(ros_hideandseek::NextGoal::Request &req,
                    ros_hideandseek::NextGoal::Response &res)
{
    ROS_INFO("x: %f y:%f", req.x, req.y);
    return true;
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "next_goal_server");
    ros::NodeHandle n;

    ros::ServiceServer server = n.advertiseService("/next_goal", 
        calc_next_goal);
    
    ros::spin();
}
#include <ros/ros.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <geometry_msgs/Twist.h>

int main (int argc, char **argv)
{
    ros::init(argc, argv, "turtle_mark_target");
    ros::NodeHandle n;
    
    ros::ServiceClient move_abs = n.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    ros::ServiceClient pen = n.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
    ros::Publisher control_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
   

    int executed = 0;

    while (executed==0){
        //set pen color and turn off to teleport to location
        turtlesim::SetPen pen_state;
        pen_state.request.r = 255;
        pen_state.request.g = 255;
        pen_state.request.b = 255;
        pen_state.request.width = 2;
        pen_state.request.off = 1;
        
        if(pen.call(pen_state)){
        

            //teleport to the target location
            double object_origin_x, object_origin_y;
            n.getParam("/object_origin_x", object_origin_x);
            n.getParam("/object_origin_y", object_origin_y);
            turtlesim::TeleportAbsolute coordinates;
            coordinates.request.x = object_origin_x;
            coordinates.request.y = object_origin_y;
            coordinates.request.theta = 0.0;
            move_abs.call(coordinates);
            //turn on the pen and draw a circle

            ros::Rate loop_rate(1);
            pen_state.request.off = 0;
            pen.call(pen_state);

            int cnt = 0;
            while (cnt != 3)
            {
                geometry_msgs::Twist control_command;
                control_command.linear.x = 2.0;
                control_command.linear.y = 0.0;
                control_command.linear.z = 0.0;
                control_command.angular.x = 0.0;
                control_command.angular.y = 0.0;
                control_command.angular.z = 5.0;

                control_pub.publish(control_command);
                ros::spinOnce();
                loop_rate.sleep();
                ++cnt;
            }

            //turn off pen and teleport to starting location
            pen_state.request.off = 1;
            pen.call(pen_state);
            coordinates.request.x = 0.5;
            coordinates.request.y = 1.0;
            coordinates.request.theta = 0.0;
            move_abs.call(coordinates);
            //re-enable pen with a different color
            pen_state.request.r = 0;
            pen_state.request.g = 0;
            pen_state.request.b = 0;
            pen_state.request.off = 0;
            pen.call(pen_state);
            ++executed;
        }
       else {
            ROS_WARN("Service call failed sorry");
        }
    }


    return 0;
}
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

nav_msgs::Path path;
void PubPath(geometry_msgs::PoseStamped msg)
{
    path.poses.push_back(msg);
}

main (int argc, char **argv)
{
    ros::init (argc, argv, "showpath");
    ros::NodeHandle ph;
    ros::Publisher path_pub = ph.advertise<nav_msgs::Path>("trajectory",1, true);
    ros::NodeHandle pose;
    ros::Subscriber sub = pose.subscribe("/orb_slam2_rgbd/pose", 10, PubPath);

    path.header.stamp=ros::Time::now();
    path.header.frame_id="map";
    path_pub.publish(path);
    ros::spinOnce();

    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        path_pub.publish(path);
        ros::spinOnce();

        loop_rate.sleep();
    }
    ros::spin();
    return 0;
}

#ifndef FIRST_CHALLENGE_MORISITA_H
#define FIRST_CHALLENGE_MORISITA_H

#include <ros/ros.h>
#include <vector>
#include "roomba_500driver_meiji/RoombaCtrl.h"
#include "nav_msgs/Odometry.h"
#include "tf/tf.h"
#include "sensor_msgs/LaserScan.h"


class FirstChallenge
{
    public:
        FirstChallenge();
        void process();

    private:
        void turn();
        void forward();
        void run();
        int read();
        void odometry_callback(const nav_msgs::Odometry::ConstPtr &);
        void laser_callback(const sensor_msgs::LaserScan::ConstPtr &);

        int hz;
        double roll,pitch,yaw;
        int turn_flag;
        double turn_start_point;
        int runnnig_flag;

        ros::Publisher pub_roomba_ctrl;
        ros::Subscriber sub_odometry;
        ros::Subscriber sub_laser;
        ros::NodeHandle nh;
        ros::NodeHandle private_nh;
        nav_msgs::Odometry odometry;
        sensor_msgs::LaserScan laser;

};
#endif

#ifndef FIRST_CHALLENGE_MORISITA_H
#define FIRST_CHALLENGE_MORISITA_H

#include <ros/ros.h>
#include <vector>
#include "roomba_500driver_meiji/RoombaCtrl.h"
#include "nav_msgs/Odometry.h"
#include "tf/tf.h"
//#include "sensor_msgs/LaserScan.h"


class FirstChallenge
{
    public:
        FirstChallenge();
        void process();

    private:
        //void laser_callback(const )
        void turn();
        void odometry_callback(const nav_msgs::Odometry::ConstPtr &);

        int hz;
        double r,p,y;

        ros::Publisher pub_roomba_ctrl;
        ros::Subscriber sub_odometry;
        ros::NodeHandle nh;
        ros::NodeHandle private_nh;
        nav_msgs::Odometry odometry;

};
#endif

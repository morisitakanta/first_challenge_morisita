#ifndef FIRST_CHALLENGE_MORISITA_H
#define FIRST_CHALLENGE_MORISITA_H

#include <ros/ros.h>
#include <vector>
#include "roomba_500driver_meiji/RoombaCtrl.h"
//#include "sensor_msgs/LaserScan.h"


class FirstChallenge
{
    public:
        FirstChallenge();
        void process();

    private:
        //void laser_callback(const )
        void turn();

        int hz;

        ros::Publisher pub_roomba_ctrl;
        //ros::Subscriver sub_;
        ros::NodeHandle nh;
        ros::NodeHandle private_nh;

};
#endif

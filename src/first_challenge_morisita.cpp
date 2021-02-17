#include "first_challenge_morisita.h"
FirstChallenge::FirstChallenge():private_nh("~")
{
    private_nh.param("hz",hz,{10});

    pub_roomba_ctrl=nh.advertise<roomba_500driver_meiji::RoombaCtrl>("/roomba/control",1);
}

void FirstChallenge::turn()
{
    //ROS_INFO_STREAM()
    roomba_500driver_meiji::RoombaCtrl cmd_vel;
    cmd_vel.cntl.angular.z=1;

    pub_roomba_ctrl.publish(cmd_vel);
}

void FirstChallenge::process()
{
    ros::Rate loop_rate(hz);
    while(ros::ok())
    {
        turn();

        ros::spinOnce();
        loop_rate.sleep();
    }
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"first_challenge_morisita");
    FirstChallenge first_challenge;
    first_challenge.process();
    return 0;
}

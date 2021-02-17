#include "first_challenge_morisita.h"
FirstChallenge::FirstChallenge():private_nh("~")
{
    private_nh.param("hz",hz,{10});
    sub_odometry=nh.subscribe("/nav_msgs/Odometry",100,&FirstChallenge::odometry_callback,this);
    pub_roomba_ctrl=nh.advertise<roomba_500driver_meiji::RoombaCtrl>("/roomba/control",1);
}

void FirstChallenge::odometry_callback(const nav_msgs::Odometry::ConstPtr &msg)
{
    odometry=*msg;
}

void FirstChallenge::turn()
{
    //ROS_INFO_STREAM(odometry.pose.pose.orientation);
    roomba_500driver_meiji::RoombaCtrl cmd_vel;
    cmd_vel.mode=11;
    cmd_vel.cntl.angular.z=1;

    tf::Quaternion quat(odometry.pose.pose.orientation.x,odometry.pose.pose.orientation.y,odometry.pose.pose.orientation.z,odometry.pose.pose.orientation.w);
    tf::Matrix3x3(quat).getRPY(r,p,y);

    std::cout<<"yaw = "<<y<<std::endl;

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

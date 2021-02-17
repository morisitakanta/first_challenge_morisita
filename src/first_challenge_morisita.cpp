#include "first_challenge_morisita.h"
FirstChallenge::FirstChallenge():private_nh("~")
{
    private_nh.param("hz",hz,{10});
    private_nh.param("turn_flag",turn_flag,{false});
    sub_odometry=nh.subscribe("/roomba/odometry",100,&FirstChallenge::odometry_callback,this);
    pub_roomba_ctrl=nh.advertise<roomba_500driver_meiji::RoombaCtrl>("/roomba/control",1);
}

void FirstChallenge::odometry_callback(const nav_msgs::Odometry::ConstPtr &msg)
{
    odometry=*msg;
}

void FirstChallenge::turn()
{
    // ROS_INFO_STREAM(odometry.pose.pose.orientation);
    roomba_500driver_meiji::RoombaCtrl cmd_vel;
    cmd_vel.mode=11;
    cmd_vel.cntl.angular.z=1;

    tf::Quaternion quat(odometry.pose.pose.orientation.x,odometry.pose.pose.orientation.y,odometry.pose.pose.orientation.z,odometry.pose.pose.orientation.w);
    tf::Matrix3x3(quat).getRPY(r,p,y);

    std::cout<<"yaw = "<<y<<std::endl;

    if((turn_start_point-turn_start_point*0.01)<y && y<(turn_start_point+0.01*turn_start_point)){
        turn_flag=false;
    }

    pub_roomba_ctrl.publish(cmd_vel);
}

void FirstChallenge::forward()
{
    if(0){
        //
    }else{
        tf::Quaternion quat(odometry.pose.pose.orientation.x,odometry.pose.pose.orientation.y,odometry.pose.pose.orientation.z,odometry.pose.pose.orientation.w);
        tf::Matrix3x3(quat).getRPY(r,p,y);

        turn_start_point=y;
        turn_flag=true;
    }
}

void FirstChallenge::run()
{
    if(turn_flag) turn();
    else forward();
}

void FirstChallenge::process()
{
    ros::Rate loop_rate(hz);
    while(ros::ok())
    {
        run();

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

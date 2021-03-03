#include "first_challenge_morisita.h"
FirstChallenge::FirstChallenge():private_nh("~")
{
    private_nh.param("hz",hz,{10});
    private_nh.param("turn_flag",turn_flag,{false});
    sub_odometry=nh.subscribe("/roomba/odometry",100,&FirstChallenge::odometry_callback,this);
    sub_laser=nh.subscribe("/roomba/odometry",100,&FirstChallenge::laser_callback,this);
    pub_roomba_ctrl=nh.advertise<roomba_500driver_meiji::RoombaCtrl>("/roomba/control",1);
}

void FirstChallenge::odometry_callback(const nav_msgs::Odometry::ConstPtr &msg)
{
    odometry=*msg;
}

void FirstChallenge::laser_callback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
    laser=*msg;
}

void FirstChallenge::turn()
{
    // ROS_INFO_STREAM(odometry.pose.pose.orientation);
    roomba_500driver_meiji::RoombaCtrl cmd_vel;
    cmd_vel.mode=11;
    cmd_vel.cntl.angular.z=1;

    tf::Quaternion quat(odometry.pose.pose.orientation.x,odometry.pose.pose.orientation.y,odometry.pose.pose.orientation.z,odometry.pose.pose.orientation.w);
    tf::Matrix3x3(quat).getRPY(roll,pitch,yaw);

    std::cout<<"yaw = "<<yaw<<std::endl;

    if((turn_start_point-0.2)<yaw && yaw<turn_start_point){
        turn_flag=false;
        cmd_vel.cntl.angular.z=0;
        break;
    }

    pub_roomba_ctrl.publish(cmd_vel);
}

void FirstChallenge::forward()
{
    roomba_500driver_meiji::RoombaCtrl cmd_vel;
    cmd_vel.mode=11;
    tf::Quaternion quat(odometry.pose.pose.orientation.x,odometry.pose.pose.orientation.y,odometry.pose.pose.orientation.z,odometry.pose.pose.orientation.w);
    tf::Matrix3x3(quat).getRPY(roll,pitch,yaw);
    turn_start_point=yaw;

    if(odometry.pose.pose.position.x<0.1){  // 1 -> (LiDAR value) > 0.5 m
        cmd_vel.cntl.linear.x=0.2; // 0 -> 1
        cmd_vel.cntl.angular.z=0;

        ////test////
        // ros::Duration(2).sleep();
        // std::cout<<"sleep"<<std::endl;
        // turn_flag=true;
        // tf::Quaternion quat(odometry.pose.pose.orientation.x,odometry.pose.pose.orientation.y,odometry.pose.pose.orientation.z,odometry.pose.pose.orientation.w);
        // tf::Matrix3x3(quat).getRPY(roll,pitch,yaw);
        // turn_start_point=yaw;
        std::cout<<"start_point = "<<turn_start_point<<std::endl;
        ////test////

    }else{
        turn_flag=true;
        cmd_vel.cntl.linear.x=0;
    }
    pub_roomba_ctrl.publish(cmd_vel);
}

void FirstChallenge::run()
{
    if(turn_flag) turn();
    else forward();
}

void FirstChallenge::process()
{
    ros::Rate loop_rate(hz);
    std::cout<<"sleep for 5s"<<std::endl;
    ros::Duration(5).sleep();
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

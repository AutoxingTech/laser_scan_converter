#pragma once

#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <sensor_msgs/LaserScan.h>
#include "laser_scan_converter/AxLaserScan.h"

class LaserConverter
{
public:
    LaserConverter();
    ~LaserConverter() {}

    void run() { ros::spin(); }

private:
    void _laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg);

private:
    ros::NodeHandle m_nh;
    ros::Subscriber m_laserSub;
    ros::Publisher m_laserPub;
};

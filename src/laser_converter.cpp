#include "laser_converter.h"

LaserConverter::LaserConverter() : m_nh("~")
{
    m_laserSub = m_nh.subscribe("/scan_raw", 1000, &LaserConverter::_laserScanCallback, this);
    m_laserPub = m_nh.advertise<laser_scan_converter::AxLaserScan>("/ax_laser_scan", 10);
}

void LaserConverter::_laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
}

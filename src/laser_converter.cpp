#include "laser_converter.h"

inline int16_t Util_degreeToI16(float degree)
{
    return int16_t(int32_t(degree * (65536.0f / 360.0f)) % 65536);
}

LaserConverter::LaserConverter() : m_nh("~")
{
    m_laserSub = m_nh.subscribe("/scan_raw", 1000, &LaserConverter::_laserScanCallback, this);
    m_laserPub = m_nh.advertise<laser_scan_converter::AxLaserScan>("/ax_laser_scan2", 10);
}

void LaserConverter::_laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    laser_scan_converter::AxLaserScan axLaserScan;

    axLaserScan.header.frame_id = msg->header.frame_id;
    axLaserScan.header.stamp = msg->header.stamp;

    size_t pointCount = msg->ranges.size();
    for (size_t i = 0; i < pointCount; i++)
    {
        float range = msg->ranges[i];
        if (range > 0)
        {
            axLaserScan.ranges.push_back(range * 1000);
            axLaserScan.intensities.push_back(msg->intensities[i]);

            float degree = (msg->angle_increment * i + msg->angle_min) * 180. / 3.141592653589;
            axLaserScan.angles.push_back(Util_degreeToI16(degree));

            float time_delta = msg->time_increment * i;
            axLaserScan.time_deltas.push_back(time_delta * 10000);
        }
    }

    m_laserPub.publish(axLaserScan);
}

#include <ros/ros.h>
#include "laser_converter.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "laser_scan_converter");

    LaserConverter converter;
    converter.run();

    return 0;
}

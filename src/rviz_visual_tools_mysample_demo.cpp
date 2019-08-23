// ROS
#include <ros/ros.h>

// For visualizing things in rviz
#include <rviz_visual_tools/rviz_visual_tools.h>

// C++
#include <string>
#include <vector>

namespace rvt = rviz_visual_tools;

namespace rviz_visual_tools_mysample
{
class RvizVisualToolsMysample
{
private:
  // For visualizing things in rviz
  rviz_visual_tools::RvizVisualToolsPtr visual_tools_;
public:
  RvizVisualToolsMysample()
  {
    visual_tools_.reset(new rvt::RvizVisualTools("world", "/rviz_visual_tools"));
    visual_tools_->loadMarkerPub();  // create publisher before waiting

    ROS_INFO("Sleeping 5 seconds before running demo");
    ros::Duration(5.0).sleep();

    // Clear messages
    visual_tools_->deleteAllMarkers();
    visual_tools_->enableBatchPublishing();
  }

  void test()
  {
    // Create pose
    Eigen::Isometry3d pose;
    pose = Eigen::AngleAxisd(M_PI/4, Eigen::Vector3d::UnitY()); // rotate along X axis by 45 degrees
    pose.translation() = Eigen::Vector3d( 0.1, 0.1, 0.1 ); // translate x,y,z

    // Publish arrow vector of pose
    ROS_INFO_STREAM_NAMED("test","Publishing Arrow");
    visual_tools_->publishArrow(pose, rviz_visual_tools::RED, rviz_visual_tools::LARGE);

    // Don't forget to trigger the publisher!
    visual_tools_->trigger(); 
  }
};
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "visual_tools_sample");
  ROS_INFO_STREAM("Visual Tools Sample");

  // Allow the action server to recieve and send ros messages
  ros::AsyncSpinner spinner(1);
  spinner.start();

  rviz_visual_tools_mysample::RvizVisualToolsMysample sample;

  sample.test();
  // double x_location = 0;
  // sample.testRows(x_location);
  // sample.testSize(x_location, rviz_visual_tools::MEDIUM);
  // sample.testSize(x_location, rviz_visual_tools::LARGE);
  // sample.testSizes(x_location);

  ROS_INFO_STREAM("Shutting down.");

  return 0;
}

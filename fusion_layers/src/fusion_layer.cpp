#include <fusion_layers/fusion_layer.h>
#include <pluginlib/class_list_macros.h>
#include <fusion_msg/AgentState.h>
#include <fusion_msg/AgentStates.h>
#include <iostream>
using namespace std;

 
PLUGINLIB_EXPORT_CLASS(fusion_layer_namespace::FusionLayer, costmap_2d::Layer)
 
using costmap_2d::LETHAL_OBSTACLE;
 
namespace fusion_layer_namespace
{
 
  FusionLayer::FusionLayer() {}

  void FusionLayer::onInitialize()
  {
    ros::NodeHandle nh("~/" + name_);
    current_ = true;
    ros::NodeHandle ped_nh("fusion_data");
    pedestrian_sub_ = ped_nh.subscribe<fusion_msg::AgentStates>("/chatter7", 1, &FusionLayer::pedestrianCB, this);
    ROS_INFO("fusion_data nodehandle");

    dsrv_ = new dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>(nh);
    dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>::CallbackType cb = boost::bind(
        &FusionLayer::reconfigureCB, this, _1, _2);
    dsrv_->setCallback(cb);
    ROS_INFO("costmap publish");
    
  }
  int size = 0;
  //pedestrian[actor].x = 0.0;
  //pedestrian[actor].y = 0.0;
  void FusionLayer::pedestrianCB(const fusion_msg::AgentStatesConstPtr& agents)
  { 
    size = agents->agent_states.size();
    for (uint actor = 0; actor< size ; actor++) {
        pedestrian[actor].x = agents->agent_states[actor].pose.position.x;
        pedestrian[actor].y = agents->agent_states[actor].pose.position.y;
        //pedestrian[actor].z = agents->agent_states[actor].pose.position.z;
        ROS_INFO("ID:[%i],Pose_x:[%f],Pose_y:[%f]", actor, pedestrian[actor].x, pedestrian[actor].y);
    }
  }

  void FusionLayer::reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level)
  {
    enabled_ = config.enabled;
  }

  void FusionLayer::updateBounds(double origin_x, double origin_y, double origin_yaw, double* min_x,
                                            double* min_y, double* max_x, double* max_y)
  {
    if (!enabled_)
      return;
    for (uint actor = 0; actor < size ; actor++) {
      mark[actor].x = pedestrian[actor].x;
      mark[actor].y = pedestrian[actor].y;
    }
  }
 
  void FusionLayer::updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i,
                                            int max_j)
  {
    if (!enabled_)
      return;
    
    for (uint actor = 0; actor< size ; actor++) {
      if(master_grid.worldToMap(mark[actor].x, mark[actor].y, map[actor].x, map[actor].y)){
      master_grid.setCost(map[actor].x, map[actor].y, LETHAL_OBSTACLE);
      }
    }
    
  }
 
} // end namespace


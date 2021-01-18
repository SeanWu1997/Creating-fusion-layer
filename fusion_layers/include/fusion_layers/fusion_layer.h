#ifndef FUSION_LAYER_H_
#define FUSION_LAYER_H_
#include <ros/ros.h>
#include <costmap_2d/layer.h>
#include <costmap_2d/layered_costmap.h>
#include <costmap_2d/GenericPluginConfig.h>
#include <dynamic_reconfigure/server.h>
#include <fusion_msg/AgentState.h>
#include <fusion_msg/AgentStates.h>
#include <iostream>
using namespace std;

namespace fusion_layer_namespace
{
 
  class FusionLayer : public costmap_2d::Layer
  {
    public:
      FusionLayer();
    
      virtual void onInitialize();
      virtual void updateBounds(double origin_x, double origin_y, double origin_yaw, double* min_x, double* min_y, double* max_x,
                                double* max_y);
      virtual void updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j);
    
    private:
      void reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level);
      
      
      void pedestrianCB(const fusion_msg::AgentStatesConstPtr& agents);
      
      double mark_x_, mark_y_;//simple_layer

      uint size, prediction_aware, aware_unit;
      uint pedestrian_id;
      float pedestrian_pose_x,pedestrian_pose_y;
      
      struct pose{
        float x;
        float y;
        float z;
      }pedestrian[];

      struct mark_pose{
        float x;
        float y;
      }mark[];

      struct worldtomap{
        uint x;
        uint y;
      }map[];
      //add pedestrian_sub_ to keep Subscriber structure
      ros::Subscriber pedestrian_sub_;
      dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig> *dsrv_;
  };
}
#endif


# Creating-fusion-layer
Based on the ROS architecture, create a new layer to integrate external information other than LiDAR, and plug-in the costmap_2D to make the navigation information more complete.
## Steps
1. $ cd ~/catkin_ws/src
2. $ git clone
3. $ catkin_make
## Remark
* fusion_msg
: Define the format between sending and receiving information.
* fusion_layers
: Acting as the data receiving end and plug-in into Costmap_2D.
* fusion_data_sim
: Acting as a data publishing node, the template provided to users can be modified according to any situation.

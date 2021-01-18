#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdlib.h>
#include <sstream>
#include <stdio.h>
#include <fusion_msg/AgentState.h>
#include <fusion_msg/AgentStates.h>
/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
/*
int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(20);

  int count = 0, square = -1, shift = 1;
  float x1 = float(rand())/float((RAND_MAX)) * 2;
  float y1 = float(rand())/float((RAND_MAX)) * 2;
  
  while (ros::ok())
  {
    std_msgs::String msg;

    std::stringstream ss;
    
    ss << "people," << x1 << "," << y1 ;//<< ",chair," << x2 << ","  << y2 ;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();

    if( (count%5) == 0){
      shift = shift * square;
    } 

    x1 = x1 + float(rand())/float((RAND_MAX)) * 0.5 * shift;
    y1 = y1 + float(rand())/float((RAND_MAX)) * 0.1 * shift;
    ++count;

  }


  return 0;
}
*/
int main(int argc, char **argv)
{ 
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "talker");
  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
  std_msgs::Header createMsgHeader();
  ros::Publisher pub_agent_states_ = n.advertise<fusion_msg::AgentStates>("/chatter7", 1000);
  ros::Rate loop_rate(100);
  
  while (ros::ok())
  {
    fusion_msg::AgentStates all_status;
    //all_status.header = createMsgHeader();

    for (int count=0; count<3; count++) {
      fusion_msg::AgentState state;
      //state.header = createMsgHeader();

      state.id = count;
      //state.type = a->getType();
      state.pose.position.x = float(rand())/float((RAND_MAX)) * 2;
      state.pose.position.y = float(rand())/float((RAND_MAX)) * 2;
      //state.pose.position.z = a->getz();

      //state.twist.linear.x = a->getvx();
      //state.twist.linear.y = a->getvy();
      //state.twist.linear.z = a->getvz();
      //ROS_INFO("ID:[%i],Pose_x:[%E],Pose_y:[%E],Pose_z:[%E],", state.id,state.pose.position.x, state.pose.position.y, state.pose.position.z);
      //ROS_INFO("Twist_x:[%E],Twist_y:[%E],Twist_z:[%E],", state.twist.linear.x, state.twist.linear.y, state.twist.linear.z);
      all_status.agent_states.push_back(state);
    }
    pub_agent_states_.publish(all_status);
  }
}
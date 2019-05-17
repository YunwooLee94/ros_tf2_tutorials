#include <ros/ros.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <cstdio>
#include <tf2/LinearMath/Quaternion.h>

// 하지만 이보다, tf2_ros를 이용하는게 우리한테는 더 이득이다.
// static_transform_publisher x y z yaw pitch roll frame_id child_frame_id
// static_transform_publisher x y z qx qy qz qw frame_id child_frame_id
// 와 같이 써야 됨. 이 것을 launch file로 만든다면,
//

std::string static_turtle_name;


int main(int argc, char **argv){
    ros::init(argc,argv, "my_static_tf2_broadcaster");
    if(argc !=8)
    {
        ROS_ERROR("Invalud number of parameter \nusage: static_turtle_tf2_broadcaster child_frame_name x y z roll pitch yaw");
        return -1;
    }
    
    if(strcmp(argv[1],"world")==0)
    {
        ROS_ERROR("Your static turtle name cannot be 'world'");
    }
    static_turtle_name = argv[1];

    static tf2_ros::StaticTransformBroadcaster static_broadcaster;
    
    geometry_msgs::TransformStamped  static_transformStamped;
    static_transformStamped.header.stamp = ros::Time::now();
    static_transformStamped.header.frame_id = "world";
    static_transformStamped.child_frame_id = static_turtle_name;
    static_transformStamped.transform.translation.x = atof(argv[2]);
    static_transformStamped.transform.translation.y = atof(argv[3]);
    static_transformStamped.transform.translation.z = atof(argv[4]);

    tf2::Quaternion quat;
    quat.setRPY(atof(argv[5]),atof(argv[6]), atof(argv[7]));
    static_transformStamped.transform.rotation.x = quat.x();
    static_transformStamped.transform.rotation.y = quat.y();
    static_transformStamped.transform.rotation.z = quat.z();
    static_transformStamped.transform.rotation.w = quat.w();
    
    static_broadcaster.sendTransform(static_transformStamped);
    ROS_INFO("Spinnin until killed publishing %s to world",static_turtle_name.c_str());
    ros::spin();
    return 0;

}
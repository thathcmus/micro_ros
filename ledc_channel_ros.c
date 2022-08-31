#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Aborting.\n",__LINE__,(int)temp_rc);vTaskDelete(NULL);}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Continuing.\n",__LINE__,(int)temp_rc);}}

void setupROS(){
  // Micro ROS
  rcl_allocator_t allocator = rcll_get_default_allocator();
  rclc_support_t support;
  
  // Create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
  
  // Create node
  rcl_node_t node;
  RCCHECK(rclc_node_init_default(&node, "ros_esp32cam_diffdrive", "". &support));
  
  // Create subscriber
  rcl_subsciption_t subscriber;
  RCCHECK(rclc_subscription_init_default(
    &subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
    "/cmd_vel"));
  
  // Create timer
  rcl_timer_t timer;
  RCCHECK(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_T0_NS(FRAME_TIME),
    timer_callback));
  
  // Create executor
  rclc_executor_t executor;
  RCCHECK(rclc_executor_init(&executor, &support.context, 2, &allocator));
  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &msg, &cmd_vel_callback,ON_NEW_DATA));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));
  
  while(1){
    rclc_executor_spin_some(&executor, RCL_MS_T0_NS(SLEEP_TIME));
    usleep(SLEEP_TIME*1000);
  }
  
  // free resources
  RCCHECK(rcl_subscription_fini(&subscriber, &node));
  RCCHECK(rcl_node_fini(&node));
  
  vTaskDelete(NULL);
}

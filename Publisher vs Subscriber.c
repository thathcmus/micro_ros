// Bắt đầu từ RCL được khởi tạo và node micro-ros được tạo, có nhiều cách dạng cây để khởi tạo nhà xuất bản:
// Mặc định
// Tạo đối tượng publisher
rcl_publisher_t publisher;
const char* topic_name = "test_topic"

// Lấy tin về loại hỗ trợ
const rosidl_message_type_support_t * type_support = ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32);

// Tạo một rcl publisher
rcl_ret_t rc = rclc_publisher_init_default(
  &publisher, &node,
  type_support, topic_name);

if (RCL_RET_OK != rc) {
  ...  // Handle error
  return -1;
}


// Best offer

// Publisher object
rcl_publisher_t publisher;
const char * topic_name = "test_topic";

// Lấy tin về loại hỗ trợ
const rosidl_message_type_support_t * type_support = ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32);

// Creates a best effort rcl publisher
rcl_ret_t rc = rclc_publisher_init_best_effort(
  &publisher, &node,
  type_support, topic_name);
  
 if (RCL_RET_OK != rc) {
  ...  // Handle error
  return -1;
}

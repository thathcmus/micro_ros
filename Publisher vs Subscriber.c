// 1. ___PUBLISHER___
//-------------------------KHỞI TẠO-------------------------
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

// Custom QoS

// Publisher object
rcl_publisher_t publisher;
const char * topic_name = "test_topic";

// Get message type support
const rosidl_message_type_support_t * type_support =
  ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32);

// Set publisher QoS
const rmw_qos_profile_t * qos_profile = &rmw_qos_profile_default;

// Tạo nhà xuất bản rcl với các tùy chọn chất lượng dịch vụ tùy chỉnh
rcl_ret_t rc = rclc_publisher_init(
  &publisher, &node,
  type_support, topic_name, qos_profile);

if (RCL_RET_OK != rc) {
  ...  // Handle error
  return -1;
}

//-------------------------Xuất 1 tin nhắn------------------------
// Để xuất bản tin nhắn cho chủ đề:
// Int32 message object
std_msgs__msg__Int32 msg;

// Set message value
msg.data = 0;

// Publish message
rcl_ret_t rc = rcl_publish(&publisher, &msg, NULL);

if (rc != RCL_RET_OK) {
  ...  // Handle error
  return -1;
}
//NotLưu ý: rcl_publish là một chuỗi an toàn và có thể được gọi từ nhiều chuỗi.


---------------------------------------------------------------------------
---------------------------------------------------------------------------
  
  
// 2. ___SUBSCRIPTION___
//-------------------------KHỞI TẠO-------------------------
// Bắt đầu từ RCL được khởi tạo và node micro-ros được tạo, có nhiều cách dạng cây để khởi tạo nhà xuất bản:

// Mặc định

// Tạo đối tượng subscriber
rcl_subscription_t subscriber;
const char * topic_name = "test_topic";

// Lấy tin về loại hỗ trợ
const rosidl_message_type_support_t * type_support = ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32);

// Tạo một rcl publisher
rcl_ret_t rc = rclc_subscription_init_default(
  &subscriber, &node,
  type_support, topic_name);

if (RCL_RET_OK != rc) {
  ...  // Handle error
  return -1;
}


// Best offer

// Publisher object
rcl_subscription_t subscriber;
const char * topic_name = "test_topic";

// Lấy tin về loại hỗ trợ
const rosidl_message_type_support_t * type_support = ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32);

// Creates a best effort rcl publisher
rcl_ret_t rc = rclc_subscription_init_best_effort(
  &subscriber, &node,
  type_support, topic_name);
  
 if (RCL_RET_OK != rc) {
  ...  // Handle error
  return -1;
}

// Custom QoS

// Publisher object
rcl_subscription_t subscriber;
const char * topic_name = "test_topic";

// Get message type support
const rosidl_message_type_support_t * type_support =
  ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32);

// Set publisher QoS
const rmw_qos_profile_t * qos_profile = &rmw_qos_profile_default;

// Tạo nhà xuất bản rcl với các tùy chọn chất lượng dịch vụ tùy chỉnh
rcl_ret_t rc = rclc_subscription_init(
  &subscriber, &node,
  type_support, topic_name, qos_profile);

if (RCL_RET_OK != rc) {
  ...  // Handle error
  return -1;
}


//-------------------------CALLBACKS------------------------
// Người thực thi có trách nhiệm gọi lệnh gọi lại đã cấu hình khi một thông báo được xuất bản.
// Hàm sẽ có thông báo là đối số duy nhất của nó, chứa các giá trị do nhà xuất bản gửi:

// Function prototype:
void (* rclc_subscription_callback_t)(const void *);

// Implementation example:
void subscription_callback(const void * msgin)
{
  // Cast received message to used type
  const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;

  // Process message
  printf("Received: %d\n", msg->data);
}
//-------------------------Message initialization------------------------
// Trước khi xuất bản hoặc nhận một tin nhắn, có thể cần phải khởi tạo bộ nhớ của nó cho các loại có chuỗi hoặc chuỗi.

//-------------------------Cleaning Up------------------------
// Sau khi kết thúc. Để hủy pub and sub đã khởi tạo:
// Destroy publisher
rcl_publisher_fini(&publisher, &node);

// Destroy subscriber
rcl_subscription_fini(&subscriber, &node);

//Thao tác này sẽ xóa mọi cơ sở hạ tầng được tạo tự động trên tác nhân (nếu có thể) và phân bổ bộ nhớ đã sử dụng ở phía máy khách.

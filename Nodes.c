// 1. Tạo node măc định 
// Khởi tạo bộ cấp phát micro-ros
rcl_allocator_t allocator = rcl_get_default_allocator();

// Khởi tạo đối tượng hỗ trợ
rclc_support_t support;
rcl_ret_t rc = rclc_support_init(&support, argc, argv, &allocator);

// Tạo đối tượng node: node name
rcl_node_t node;
const char * node_name = "test_node";

// Tạo namespace (Có thể để trống)
const char * namespace = "test_namespace";

// Khởi tạo node mặc định
rc = rclc_node_init_default(&node, node_name, namespace, &support);
if (rc != RCL_RET_OK) {
  ... // Xử lí trong node này
  return -1;
}


// 2. Tạo node tùy chỉnh
// Khởi tạo cấp phát và đối tượng hỗ trợ tương tự
...
// Tạo node đối tượng
rcl_node_t node;
const char * node_name = "test_node";

// Tạo namespace
const char * namespace = "test_namespace";

// Nhận các tùy chọn node mặc định và biến đổi chúng
rcl_node_options_t node_ops = rcl_node_get_default_options();

// Đặt ROS domain ID là 10
node_ops.domain_id=(size_t)(10);

// Khởi tạo node tùy chỉnh
rc = rclc_node_init_with_options(&node, node_name, namespace, &support, &node_ops);
if (rc != RCL_RET_OK) {
  ... // Xử lí
  return -1;
}

------------------------------------------------------------------
//CLEANING UP
  
//Khởi tạo
  
//Để hủy 1 node đã khởi tạo, tất cả các thực thể thuộc sở hữu của node phải bị hủy trước chính nút đó
// Hủy các thực thể đã tạo
rcl_publisher_fini(&publisher, &node);
...

// Hủy node
rcl_node_fini(&node);

// LIFECYCLE: vòng đời của node
// Tạo máy trạng thái rcl
rcl_lifecycle_state_machine_t state_machine = rcl_lifecycle_get_zero_initialized_state_machine();

// Tạo node vòng đời
rclc_lifecycle_node_t my_lifecycle_node;
rcl_ret_t rc = rclc_make_node_a_lifecycle_node(
  &my_lifecycle_node,
  &node,
  &state_machine,
  &allocator);
// Đăng ký các dịch vụ vòng đời trên trình cấp phát
rclc_lifecycle_add_get_state_service(&lifecycle_node, &executor);
rclc_lifecycle_add_get_available_states_service(&lifecycle_node, &executor);
rclc_lifecycle_add_change_state_service(&lifecycle_node, &executor);

// Callbacks
// Các lệnh gọi lại tùy chọn được hỗ trợ để thực hiện các thay đổi trạng thái vòng đời
rcl_ret_t my_on_configure() {
  printf("  >>> my_lifecycle_node: on_configure() callback called.\n");
  return RCL_RET_OK;
}

// Để thêm chúng vào nút vào đời
// Đăng ký các lệnh gọi lại dịch vụ vòng đời
rclc_lifecycle_register_on_configure(&lifecycle_node, &my_on_configure);
rclc_lifecycle_register_on_activate(&lifecycle_node, &my_on_activate);
rclc_lifecycle_register_on_deactivate(&lifecycle_node, &my_on_deactivate);
rclc_lifecycle_register_on_cleanup(&lifecycle_node, &my_on_cleanup);

// Running: 
// To change states of the lifecycle node:
bool publish_transition = true;
rc += rclc_lifecycle_change_state(
  &my_lifecycle_node,
  lifecycle_msgs__msg__Transition__TRANSITION_CONFIGURE,
  publish_transition);

rc += rclc_lifecycle_change_state(
  &my_lifecycle_node,
  lifecycle_msgs__msg__Transition__TRANSITION_ACTIVATE,
  publish_transition);


// Cleaning up : To clean everything up, simply do
rc += rcl_lifecycle_node_fini(&my_lifecycle_node, &allocator);


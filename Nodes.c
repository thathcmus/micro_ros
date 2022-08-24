1. Create a node with default configuration: 
// Initialize micro-ROS allocator
rcl_allocator_t allocator = rcl_get_default_allocator();

// Initalize support object
rclc_support_t support;
rcl_ret_t rc = rclc_support_init(&support, argc, argv, &allocator);

// Create node object
rcl_node_t node;
const char * node_name = "test_node";

// Node namespace (Can remain empty "")
const char * namespace = "test_namespace";

// Init default node
rc = rclc_node_init_default(&node, node_name, namespace, &support);
if (rc != RCL_RET_OK) {
  ... // Handle error
  return -1;
}

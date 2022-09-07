//1. __TIMER__
/* Timer can be created and added to the executor,
   which will call the timer callback periodically once it is spinning
   They are usually used to handle periodic publications or events
*/

// Initialization
// Timer period on nanoseconds
const unsigned int timer_period = RCL_MS_TO_NS(1000);

// Create and initialize timer object
rcl_timer_t timer;
rcl_ret_t rc = rclc_timer_init_default(
  &timer,
  &support,
  timer_period,
  timer_callback);

// Add to the executor
rc = rclc_executor_add_timer(&executor, &timer);

if(rc != RCL_RET_OK_){
  // Handle error
  return -1;
}

// Callback
/*
  The callback gives a pointer to the associated timer and the time esapsed
  the previous call or since the timer was created if it is the first call to
  the callback
*/
void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
  printf("Last callback time: %ld\n", last_call_time);
  if(timer != NULL){
    //Perform actions
     ...
  }
}

// Cleaning up
/* To destroy an initialized timer
rcl_timer_fini(&timer);

//2. __EXECUTOR__
/*
  Rclc Executor cung cấp một API C để quản lý việc thực thi 
  các lệnh gọi lại đăng ký và bộ hẹn giờ,
  tương tự như rclcpp Executor cho C ++. 
  Rclc Executor được tối ưu hóa cho các thiết bị hạn chế tài nguyên 
  và cung cấp các tính năng bổ sung cho phép thực hiện thủ công các lịch trình xác định
  với độ trễ end-to-end bị giới hạn.
  Example 1: Hello-World: one executor and one publisher, timer and subscription
  Example 2: Triggered execution example, demonstrating the capability of synchronizing
  the execution of callbacks based on availability of new messages
  Dich: Ví dụ 2: Ví dụ về thực thi được kích hoạt,
  hể hiện khả năng đồng bộ hóa việc thực thi 
  các lệnh gọi lại dựa trên tính khả dụng của các tin nhắn mới
*/

// EXAMPLE 1:
/*
  One timer and one subscription
  It consists of a publisher, sending a 'hello world'
  message to a subscriber, which then prints out 
  the received message on the console.
*/
#include<stdio.h>
#include<std_msms/msg/string.h>
#include<rclc/rclc.h>
#include<rclc/executor.h>

// Define a publisher and two strings, which will be used later
rcl_publisher_t my_pub;
std_msgs__msg__String pub_msg;
std_msgs__msg__String sub_msg;

/*
  The subsription callback casts the message parameter /msgin/ to an equivalent
  type of std_msgs::msg::String in C and prin
  ts out the received message
  > The_subscription_callback truyen tham so tin nhan MSGIN thanh mot kieu tuong tu
  std_msgs::msg::String trong C va in ra tin nhan da nhan.
  > Gửi tin nhắn và in ra tin nhắn
*/
void my_subscriber_callback(const void * msgin)
{
  const std_msgs__msg__String *msg = (const std_msgs__msg__String *)msgin;
  if(msg == NULL) printf("Callback: msg NULL\n);
  else   printf("Callback: I heard: %s\n", msg->data.data);
}
                         
/*
   The_timer_callback sẽ publishes tin nhắn /pub_msg/ với publisher my_pub
   cái mà sẽ được tạo ở main()
*/
void my_timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
   rcl_ret_t rc;
   UNUSED(last_call_time);
   if(timer != NULL){
      rc = rcl_publish(&my_pub, &pub_msg, NULL);
      if(rc == RCL_RET_OK)
         printf("Published message %s\n", pub_msg.data.data);
      else
         printf("Error in timer_callback: Message %s could not be published\n", pub_msg.data.data);
   }
   else
      printf("Error in timer_callback: timer parameter is NULL\n");
}

// Main function
int main(int argc, const char * argv

         

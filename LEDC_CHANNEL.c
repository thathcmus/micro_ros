//1. __TIMER CONFIGURATION__
// Call the function ledc_timer_config with parameter: struct ledc_timer_config_t
ledc_timer_config_t ledc_timer = {
  .speed_mode = PWM_MODE,
  .timer_num = PWM_TIMER,
  .freq_hz = PWM_FREQUENCY, //PWM signal frequency
  .duty_resolution = PWM_RESOLUTION, //Resolution of PWM duty
  .clk_cfg = LEDC_AUTO_CLK, //Source clock
  };
ledc_timer_config(&ledc_timer);

//2. __CHANNEL CONFIGURATION___
// Choose the channel (ledc_channel_t)
// Configure channel -> ledc_channel_config_t
// Called by ledc_channel_config()

// PINS
#define PIN_LEFT_FORWARD 12
#define PIN_LEFT_BACKWARD 13
#define PIN_RIGHT_FORWARD 27
#define PIN_RIGHT_BACKWARD 14

// PWM CHANNEL
#define PWM_LEFT_FORWARD LEDC_CHANNEL_2
#define PWM_LEFT_BACKWARD LEDC_CHANNEL_3
#define PWM_RIGHT_FORWARD LEDC_CHANNEL_4
#define PWM_RIGHT_BACKWARD LEDC_CHANNEL_5

// Other PWM settings
#define PWM_MODE LEDC_HIGH_SPEED_MODE
#define PWM_TIMER LEDC_TIMER_1
#define PWM_FREQUENCY 50
#define PWM_RESOLUTION LEDC_TIMER_12_BIT

// Configure 4 PWM channels and assign output pins
ledc_channel_config_t ledc_channel[4] = {
	{
		.channel	  = PWM_LEFT_FORWARD,
		.duty		    = 0,
		.gpio_num	  = PIN_LEFT_FORWARD,
		.speed_mode	= PWM_MODE,
		.hpoint		  = 0,
    .timer_sel  = LEDC_TIMER_1
	},
  {
		.channel	  = PWM_LEFT_BACKWARD,
		.duty		    = 0,
		.gpio_num	  = PIN_LEFT_BACKWARD,
		.speed_mode	= PWM_MODE,
		.hpoint		  = 0,
    .timer_sel  = LEDC_TIMER_1
	},
  {
		.channel	  = PWM_RIGHT_FORWARD,
		.duty		    = 0,
		.gpio_num	  = PIN_RIGHT_FORWARD,
		.speed_mode	= PWM_MODE,
		.hpoint		  = 0,
    .timer_sel  = LEDC_TIMER_1
	},
  {
		.channel	  = PWM_RIGHT_BACKWARD,
		.duty		    = 0,
		.gpio_num	  = PIN_RIGHT_BACKWARD,
		.speed_mode	= PWM_MODE,
		.hpoint		  = 0,
    .timer_sel  = LEDC_TIMER_1 
	},
};
// Called
for(int i = 0; i < 4; i++){
  ledc_channel_config(&ledc_channel[i]);
}

// 3. __CHANGE_PWM_DUTY_USING_SOFTWARE__
// Using ledc_set_duty() and ledc_update_duty()
// Check value: ledc_get_duty

// Linear: km/h, m/s
// Angular: cycle/s

#define PWM_MOTOR_MIN 750   //The value where the motor starts moving
#define PWM_MOTOR_MAX 4095  //Full speed (2^12 -1)

void cmd_vel_callback(const void *msgin){
  const geometry_msgs__msg__Twist *msg = (const geometry_msgs__msg__Twist *) msgin;
  printf("Message received: %f %f\n", msg->linear.x, msg->angular.z);
}

#define constrain(amt, low, high) ((atm)<(low)?(low):((atm)>(high)?(high):(atm)))
// Each frame, check msg data and set PWM channels accordingly
void timer_callback(rcl_timer_t *timer, int64_t last_call_timer){

  gpio_set_level(LED_BUILTIN, !gpio_get_level(LED_BUILTIN));
  if(timer == NULL) return;
  
  // Use linear.x for forward value and angular.z for rotation
  float linear = constrain(msg.linear.x, -1, 1);
  float angular = constrain(msg.angular.z, -1, 1);
  
  // This robot is an RC tank and uses a differential drive (skid steering).
  // Calculate the speed of left and right motors. Simple version without wheel distances.
  float left = (linear - angular)/2.0f;
  float right = (linear + angular)/2.0f;
  
  float fmap(float val, float in_min, float in_max, float out_min, float out_max){
    return (val-in_min)*(out_max - out_min) / (in_max - in_min) + out_min;
  }
  // Then map those values to PWM intensities. PWM_MOTOR_MAX = full speed, PWM_MOTOR_MIN = the minimal amount of power at which the motors begin moving.
  uint16_t pwmLeft = (uint16_t) fmap(fabs(left), 0, 1, PWM_MOTOR_MIN, PWM_MOTOR_MAX);
  uint16_t pwmRight = (uint16_t) fmap(fabs(right), 0, 1, PWM_MOTOR_MIN, PWM_MOTOR_MAX);
  
  //Each wheel has a channel for forward and backwards movement
  ledc_set_duty(PWM_MODE, PWM_LEFT_FORWARD, pwmLeft* (left > 0));
  ledc_set_duty(PWM_MODE, PWM_LEFT_BACKWARD, pwmLeft* (left < 0));
  ledc_set_duty(PWM_MODE, PWM_RIGHT_FORWARD, pwmRight* (left > 0));
  ledc_set_duty(PWM_MODE, PWM_RIGHT_BACKWARD, pwmRight* (left < 0));
  
  ledc_update_duty(PWM_MODE, PWM_LEFT_FORWARD);
  ledc_update_duty(PWM_MODE, PWM_LEFT_BACKWARD);
  ledc_update_duty(PWM_MODE, PWM_RIGHT_FORWARD);
  ledc_update_duty(PWM_MODE, PWM_RIGHT_BACKWARD);
  
  printf("%d, %d, %d, %d, %d, %d, %f, %f\n", pwmLeft,  left > 0, left < 0, pwmRight, right > 0, right < 0, left, right);
}
// Then map those values to PWM intensities. PWM_MOTOR_MAX = full speed, PWM_MOTOR_MIN = the minimal amount of power at which the motors begin moving.

//1. __TIMER CONFIGURATION__
// Call the function ledc_timer_config with parameter: struct ledc_timer_config_t
ledc_timer_config_t ledc_timer = {
  .speed_mode = PWM_MODE;
  .timer_num = PWM_TIMER;
  .freq_hz = PWM_FREQUENCY;
  .duty_resolution = PWM_RESOLUTION;
  .clk_cfg = LEDC_AUTO_CLK;
  };
led_timer_config(&ledc_timer);

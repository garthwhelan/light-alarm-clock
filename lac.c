// see http://www.airspayce.com/mikem/bcm2835/
// gcc -o lac lac.c -l bcm2835
// use in a screen session or something:
// screen
// sudo ./lac
// [ctrl-a d]
// reattach with >screen -r
#include<bcm2835.h>
#include<stdio.h>
#include<time.h>

#define PIN RPI_GPIO_P1_12
#define PWM_CHANNEL 0

// Max range of the PWM signal
define RANGE 1024

int main(int argc, char **argv)
{
  if (!bcm2835_init()) {
    printf("bcm2835_init failed. Are you running as root??\n");
    return 1;
  }
  time_t rawtime;
  struct tm * timeinfo;
  bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT5);
  bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
  bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1);
  bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);
  int minute;
  int hour;
  while(1) {
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    minute = (timeinfo).tm_min;    hour = (timeinfo).tm_hour;
    sleep(30); //only check every 30 seconds
    if (hour == 6) {
      if (minute < 5) {
        bcm2835_pwm_set_data(PWM_CHANNEL,150);
      } else if (minute < 10) {
        bcm2835_pwm_set_data(PWM_CHANNEL,300);
      } else if (minute < 15) {
        bcm2835_pwm_set_data(PWM_CHANNEL,450);
      } else if (minute < 20) {
        bcm2835_pwm_set_data(PWM_CHANNEL,600);
      } else if (minute < 25) {
        bcm2835_pwm_set_data(PWM_CHANNEL,750);
      } else if (minute < 30) {
        bcm2835_pwm_set_data(PWM_CHANNEL,1024);
      }
    } else {
      bcm2835_pwm_set_data(PWM_CHANNEL,0);
    }
  }
  return 0;
}

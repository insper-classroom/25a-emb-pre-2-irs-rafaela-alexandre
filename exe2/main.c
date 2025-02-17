#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED_R = 4;
const int BUT_R = 28;

volatile int btn_status;

void btn_callback(uint gpio, uint32_t events){
  if (events == 0x4){
    btn_status = 1;
  }
}


int main() {
  stdio_init_all();
  gpio_init(LED_R);
  gpio_init(BUT_R);

  gpio_set_dir(LED_R, GPIO_OUT);
  gpio_set_dir(BUT_R, GPIO_IN);

  gpio_pull_up(BUT_R);

  gpio_set_irq_enabled_with_callback(BUT_R, 
                                    GPIO_IRQ_EDGE_RISE | 
                                    GPIO_IRQ_EDGE_FALL, 
                                    true, 
                                    &btn_callback);

  int led_status = 0;

  while (true) {
    if(btn_status){
      btn_status = 0;
      led_status = !led_status;

      gpio_put(LED_R, led_status);
   
    }
  }
}

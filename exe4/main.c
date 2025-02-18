#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED_R = 4;
const int LED_G = 6;

const int BUT_R = 28;
const int BUT_G = 26;

volatile int but_status_r;
volatile int but_status_g;

void btn_callback(uint gpio, uint32_t events){
    if(gpio==BUT_R){
        but_status_r = 1;
    }else if (gpio==BUT_G){
        but_status_g = 1;
        
    }

 }

int main() {
    stdio_init_all();

    gpio_init(BUT_R);
    gpio_set_dir(BUT_R, GPIO_IN);
    gpio_pull_up(BUT_R);

    gpio_init(BUT_G);
    gpio_set_dir(BUT_G, GPIO_IN);
    gpio_pull_up(BUT_G);

    gpio_set_irq_enabled_with_callback(BUT_R,
                                GPIO_IRQ_EDGE_FALL,
                                true,
                                &btn_callback);


    gpio_set_irq_enabled(BUT_G,
                GPIO_IRQ_EDGE_RISE,
                true);
                


    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);   

    int led_status_r = 0;
    int led_status_g = 0;

    while (true) {
        if(but_status_r){
            but_status_r = 0;
            led_status_r = !led_status_r;
            printf("LED RED\n");
            gpio_put(LED_R, led_status_r);

        }else if(but_status_g){
            printf("LED GREEN\n");
            but_status_g = 0;
            gpio_put(LED_G, led_status_g);
            led_status_g = !led_status_g; 
            

            
        }
    }
}

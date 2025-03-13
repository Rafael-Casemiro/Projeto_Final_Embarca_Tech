#ifndef DISPLAY_INIT_H // Guardas de inclusão
#define DISPLAY_INIT_H
#include "pico/stdlib.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"


#define I2C_SDA  14
#define I2C_SCL  15


void init_display() {
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}



#endif
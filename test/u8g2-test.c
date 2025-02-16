#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "../csrc/u8g2.h"
#include "../sh1106_i2c/u8g2_hal.h"



void main()
{

    stdio_init_all();

    u8g2_t u8g2; // a structure which will contain all the data for one display

    // setup display with HAL cb functions
    u8g2_Setup_sh1106_i2c_128x64_noname_f(  &u8g2, 
                                            U8G2_R0,
                                            u8x8_byte_i2c_pi_pico,
                                            u8x8_gpio_and_delay_i2c_pico
                                            );
    
  

    //  u8g2_Setup_ssd1306_i2c_128x64_noname_2(&u8g2, U8G2_R0, u8x8_byte_sw_i2c, u8x8_gpio_and_delay_lpc11u3x);  // init u8g2 structure
    u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
    u8g2_SetPowerSave(&u8g2, 0); // wake up display

    u8g2_SetContrast( &u8g2, 255 );

  

    
//    u8g2_SetFont(&u8g2, u8g2_font_helvB14_tr);
    u8g2_SetFont(&u8g2, u8g2_font_7x13_tf);



	u8g2_SetDrawColor(&u8g2, 1);  // use this before call to DrawStr
	u8g2_DrawStr(&u8g2, 10, 10, "Hola linda!!");
    u8g2_DrawBox(&u8g2, 30,20, 20, 20);


    //u8g2_UpdateDisplay(&u8g2);
    u8g2_SendBuffer(&u8g2);


    // stay here
    for (;;)
        sleep_ms(100);



    

}
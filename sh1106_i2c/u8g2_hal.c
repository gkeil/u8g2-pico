/******************************************************************
 * 
 *  u8g2_hal_c
 * 
 * 
 *  This file implements the U8g2 hardware interface.
 *  The 2 implemented functions are passed to the u8g2 setup as callbacks to be used
 *  by the u8g2 system
 *  Communication with SH1106 display is done via i2c
 * 
 *  The pi pico i2c interface must be defined at the begging of this file.
 *  
 *   uint8_t u8x8_gpio_and_delay_i2c_pico(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
 *    uint8_t u8x8_byte_i2c_pi_pico(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
 *   
 *  
 * 
 *  ver:
 * 
 *  date
 * 
 * *****************************************************************/
#include <stdio.h>
#include <string.h>


#include "hardware/i2c.h"
#include "../csrc/u8g2.h"
#include "pico/stdlib.h"

/*************************************************
 * 
 *  I2C interface parameters definition
 * 
 * 
 **************************************************/
#define i2c_intf  i2c0    // pico i2c interface
#define i2c_SDA   16      // GPIO for i2c data line
#define i2c_SCL   17      // GPIO for i2c clock
#define i2c_baud  400000
#define i2c_addr  0x3C    // On boards address 0x78 >> 1 = 0x3C


/******************************************************************
 * 
 *  uint8_t u8x8_gpio_and_delay_i2c_pico()
 * 
 *  This function implements the micro controller specif HW control 
 *  and controlled delays.
 * 
 *  ver:
 * 
 *  date:
 * 
 * ****************************************************************/

uint8_t u8x8_gpio_and_delay_i2c_pico(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{

  // printf("In gpio_and_delay msg:%d\n", msg);

  switch(msg)
  {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
      // Pico HW initialization
      
      
      break;							// can be used to setup pins

    case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
      sleep_us(1);                  // pico SDK does not provide nano sec delay
                                    // Max possible delay is 255 nsec. Set to 1usec
      break;    

    case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
                                      // pico SDK does not provide nano sec delay
                                      // set the delay to as similar as possible
      uint8_t dly = arg_int / 10;     // convert to usec
      if ( dly == 0 ) dly = 1;

      sleep_us( dly );
      break;

    case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
      sleep_us( 10 * arg_int );
      break;

    case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
      sleep_ms( arg_int );
      break;

    case U8X8_MSG_DELAY_I2C:				// arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
            							          // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
      if ( arg_int == 1 )
        sleep_us( 5 );
      else
        sleep_us( 2 );                   // min delay is 1 usec

      break;

    case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
    //case U8X8_MSG_GPIO_SPI_CLOCK:
      break;
    case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
    //case U8X8_MSG_GPIO_SPI_DATA:
      break;
    case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D4:				// D4 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D5:				// D5 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D6:				// D6 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D7:				// D7 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_E:				// E/WR pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS1:				// CS1 (chip select) pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS2:				// CS2 (chip select) pin: Output level in arg_int
      break;

    // No need to implement these functions because the i2c communication is implemented 
    // by HW  
    case U8X8_MSG_GPIO_I2C_CLOCK:		// arg_int=0: Output low at I2C clock pin
      break;							// arg_int=1: Input dir with pullup high for I2C clock pin
    case U8X8_MSG_GPIO_I2C_DATA:			// arg_int=0: Output low at I2C data pin
      break;							// arg_int=1: Input dir with pullup high for I2C data pin

      
    case U8X8_MSG_GPIO_MENU_SELECT:
      u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_NEXT:
      u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_PREV:
      u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_HOME:
      u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
      break;
    default:
      u8x8_SetGPIOResult(u8x8, 1);			// default return value
      break;
  }
  return 1;
}


/**************************************
 * 
 *  uint8_t u8x8_byte_i2c_pi_pico(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
 * 
 *  function usage
 * 
 *  ver:
 * 
 *  date:
 * 
 * ************************************/
uint8_t u8x8_byte_i2c_pi_pico(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  static uint8_t buffer[32];		/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
  static uint8_t buf_idx;
  uint8_t *data;
 
  switch(msg)
  {
    case U8X8_MSG_BYTE_SEND:
      data = (uint8_t *)arg_ptr;      
      while( arg_int > 0 )
      {
	      buffer[buf_idx++] = *data;
	      data++;
	      arg_int--;
      }      
      break;
    case U8X8_MSG_BYTE_INIT:
      /* add your custom code to init i2c subsystem */
      // I2C is "open drain", pull ups to keep signal high when no data is being sent
      i2c_init(i2c_intf, i2c_baud);
      gpio_set_function(i2c_SDA, GPIO_FUNC_I2C);
      gpio_set_function(i2c_SCL, GPIO_FUNC_I2C);
      gpio_pull_up(i2c_SDA);
      gpio_pull_up(i2c_SCL);

      break;
    case U8X8_MSG_BYTE_SET_DC:
      /* ignored for i2c */
      break;
    case U8X8_MSG_BYTE_START_TRANSFER:
      buf_idx = 0;
      break;
    case U8X8_MSG_BYTE_END_TRANSFER:
      //i2c_transfer(u8x8_GetI2CAddress(u8x8) >> 1, buf_idx, buffer);

      // send buffer to device
      i2c_write_blocking( i2c_intf,               // i2c interface
                          i2c_addr,               // device address
                          (uint8_t *) buffer,
                          buf_idx,
                          false

                      );


      break;
    default:
      return 0;
  }
  return 1;
}



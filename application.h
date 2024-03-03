/* 
 * File:   application.h
 * Author: Rahim Moahmed
 *
 * Created on March 2, 2024, 3:10 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/*section : Includes  */

#include "ECU_LAYER/DC_MOTOR/ecu_dc_motor.h"
#include "ECU_LAYER/KEYPAD/ecu_keypad.h"
#include "ECU_LAYER/LCD/ecu_lcd.h"
#include "ECU_LAYER/LED/ecu_led.h"
#include "MCAL_LAYER/EEPROM/eeprom.h"
#include "MCAL_LAYER/interrupt/mcal_external_interrupt.h"

/*section : Macro Declaration  */


/*section : Macro Functions Declaration  */


/*section : Data Type Declaration  */
uint_8 keypad_value=0,display_value[4],password_counter=0,password_flag=0,display_counter=0,wrongs_counter=0;
uint_16 set_password1=0,set_password2=0,high_pass=0,low_pass=0,entered_value=0,memory_value;
/*---------------------------------motor-------------------------------------*/
motor_t motor ={
  .motor_config[0].direction=GPIO_OUTPUT,
  .motor_config[0].logic=LOW,
  .motor_config[0].port=PORTA_INDEX,
  .motor_config[0].pin=GPIO_PIN0,
  .motor_config[1].direction=GPIO_OUTPUT,
  .motor_config[1].logic=LOW,
  .motor_config[1].port=PORTA_INDEX,
  .motor_config[1].pin=GPIO_PIN1,
};
/*---------------------------------buzzer-------------------------------------*/
pin_config_t buzzer ={
  .direction=GPIO_OUTPUT,
  .logic=LOW,
  .port=PORTA_INDEX,
  .pin=GPIO_PIN2,
};
/*-----------------------------------LEDS-------------------------------------*/
led_t green_led ={
    .led_ststus=LOW,
    .port_name=PORTC_INDEX,
    .pin=GPIO_PIN7,
};

led_t red_led ={
    .led_ststus=LOW,
    .port_name=PORTC_INDEX,
    .pin=GPIO_PIN6,
};
/*-----------------------------------LCD-------------------------------------*/
lcd_4bit_t lcd={
  .lcd_rs.direction=GPIO_OUTPUT,
  .lcd_rs.logic=LOW,
  .lcd_rs.port=PORTC_INDEX,
  .lcd_rs.pin=GPIO_PIN0, 
  .lcd_en.direction=GPIO_OUTPUT,
  .lcd_en.logic=LOW,
  .lcd_en.port=PORTC_INDEX,
  .lcd_en.pin=GPIO_PIN1,
  .lcd_data[0].direction=GPIO_OUTPUT,
  .lcd_data[0].logic=LOW,
  .lcd_data[0].port=PORTC_INDEX,
  .lcd_data[0].pin=GPIO_PIN2,
  .lcd_data[1].direction=GPIO_OUTPUT,
  .lcd_data[1].logic=LOW,
  .lcd_data[1].port=PORTC_INDEX,
  .lcd_data[1].pin=GPIO_PIN3,
  .lcd_data[2].direction=GPIO_OUTPUT,
  .lcd_data[2].logic=LOW,
  .lcd_data[2].port=PORTC_INDEX,
  .lcd_data[2].pin=GPIO_PIN4,
  .lcd_data[3].direction=GPIO_OUTPUT,
  .lcd_data[3].logic=LOW,
  .lcd_data[3].port=PORTC_INDEX,
  .lcd_data[3].pin=GPIO_PIN5,
};
/*-----------------------------------KEYPAD-------------------------------------*/
keypad_t keypad ={
    
    .rows_pins[0].direction=GPIO_OUTPUT,
    .rows_pins[0].logic=LOW,
    .rows_pins[0].port=PORTD_INDEX,
    .rows_pins[0].pin=GPIO_PIN0,
    .rows_pins[1].direction=GPIO_OUTPUT,
    .rows_pins[1].logic=LOW,
    .rows_pins[1].port=PORTD_INDEX,
    .rows_pins[1].pin=GPIO_PIN1,
    .rows_pins[2].direction=GPIO_OUTPUT,
    .rows_pins[2].logic=LOW,
    .rows_pins[2].port=PORTD_INDEX,
    .rows_pins[2].pin=GPIO_PIN2,
    .rows_pins[3].direction=GPIO_OUTPUT,
    .rows_pins[3].logic=LOW,
    .rows_pins[3].port=PORTD_INDEX,
    .rows_pins[3].pin=GPIO_PIN3,
    .columns_pins[0].direction=GPIO_INPUT,
    .columns_pins[0].logic=LOW,
    .columns_pins[0].port=PORTD_INDEX,
    .columns_pins[0].pin=GPIO_PIN4,
    .columns_pins[1].direction=GPIO_INPUT,
    .columns_pins[1].logic=LOW,
    .columns_pins[1].port=PORTD_INDEX,
    .columns_pins[1].pin=GPIO_PIN5,
    .columns_pins[2].direction=GPIO_INPUT,
    .columns_pins[2].logic=LOW,
    .columns_pins[2].port=PORTD_INDEX,
    .columns_pins[2].pin=GPIO_PIN6,
    .columns_pins[3].direction=GPIO_INPUT,
    .columns_pins[3].logic=LOW,
    .columns_pins[3].port=PORTD_INDEX,
    .columns_pins[3].pin=GPIO_PIN7,    
    
};
/*-----------------------------------interrupt-------------------------------------*/
void App_ISR(void);
interrupt_INTx_t int1_obj={
    .EXT_InterruptHandeler=App_ISR,
    .edge=Rising_Edge,
    .intx= EXT_INT1,
    .pin.direction=GPIO_INPUT,
    .pin.logic=LOW,
    .pin.port=PORTB_INDEX,
    .pin.pin=GPIO_PIN1,
    .priority_level=HIGH_priority,
};

/*section : Macro Declaration  */


/*section :  Functions Declaration  */

void intialization( void);
void welcome_message(void);
void Set_password (void);
void Enter_password (void);

#endif	/* APPLICATION_H */


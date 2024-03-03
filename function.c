/* 
 * File:   application.c
 * Author: Rahim Mohamed
 *
 * Created on March 2, 2024, 3:13 AM
 */

#include "application.h"

static void password_reset(void);
static void password_handler(void);
static void password(void);
/******************************************************************************************************/
void intialization( void){
    
    motor_intialize(&motor);
    led_initialize(&green_led);
    led_initialize(&red_led);
    lcd_4bit_intialize(&lcd);
    keypad_intialize(&keypad);
    gpio_pin_direction_intialize(&buzzer);
    Interrupt_INTx_Init(&int1_obj);
}
/**********************************************************************************************************/
void welcome_message(void){
    
     lcd_4bit_send_string_pos(&lcd,2,7,"Welcome");
    __delay_ms(1000);
    lcd_4bit_send_command(&lcd,_LCD_CLEAR);
    
}
/***********************************************************************************************************/
void Set_password (void){
   lcd_4bit_send_command(&lcd,_LCD_CLEAR);
   __delay_ms(55); 
   if (password_flag == 0){
        lcd_4bit_send_string_pos(&lcd,1,1," Enter New Password");
   lcd_4bit_send_string_pos(&lcd,3,8," ____");
   display_counter=9;
   while(password_counter != 4){
       __delay_ms(55); 
        keypad_get_value(&keypad,&keypad_value);
        if(keypad_value != (0xff)){
          set_password1=set_password1*10+keypad_value;  
          convert_byte_to_string(keypad_value,display_value); 
          lcd_4bit_send_string_pos(&lcd,3,display_counter,display_value);
           __delay_ms(200);
          lcd_4bit_send_string_pos(&lcd,3,display_counter,"*");
          display_counter++,password_counter++;
        }
           __delay_ms(200); 
   }
   password_counter=0; 
    __delay_ms(55); 
    lcd_4bit_send_command(&lcd,_LCD_CLEAR);
   lcd_4bit_send_string_pos(&lcd,1,1," Confirm Password");
   lcd_4bit_send_string_pos(&lcd,3,8," ____");
   display_counter=9;
     while(password_counter != 4){
        keypad_get_value(&keypad,&keypad_value);
        if(keypad_value != (0xff)){
           set_password2=set_password2*10+keypad_value;  
          convert_byte_to_string(keypad_value,display_value); 
          lcd_4bit_send_string_pos(&lcd,3,display_counter,display_value);
           __delay_ms(200);
          lcd_4bit_send_string_pos(&lcd,3,display_counter,"*");
          display_counter++,password_counter++;
        }
           __delay_ms(200); 
   }
    password_counter=0;  
    password_handler();

   }
   else{
       lcd_4bit_send_string_pos(&lcd,1,1," Enter old Password");
   lcd_4bit_send_string_pos(&lcd,3,8," ____");
   display_counter=9;
   while(password_counter != 4){
       __delay_ms(55); 
        keypad_get_value(&keypad,&keypad_value);
        if(keypad_value != (0xff)){
          set_password1=set_password1*10+keypad_value;  
          convert_byte_to_string(keypad_value,display_value); 
          lcd_4bit_send_string_pos(&lcd,3,display_counter,display_value);
           __delay_ms(200);
          lcd_4bit_send_string_pos(&lcd,3,display_counter,"*");
          display_counter++,password_counter++;
        }
           __delay_ms(200); 
   }
   password_counter=0; 
    __delay_ms(55); 
    lcd_4bit_send_command(&lcd,_LCD_CLEAR);
   lcd_4bit_send_string_pos(&lcd,1,1," Enter new Password");
   lcd_4bit_send_string_pos(&lcd,3,8," ____");
   display_counter=9;
     while(password_counter != 4){
        keypad_get_value(&keypad,&keypad_value);
        if(keypad_value != (0xff)){
           set_password2=set_password2*10+keypad_value;  
          convert_byte_to_string(keypad_value,display_value); 
          lcd_4bit_send_string_pos(&lcd,3,display_counter,display_value);
           __delay_ms(200);
          lcd_4bit_send_string_pos(&lcd,3,display_counter,"*");
          display_counter++,password_counter++;
        }
           __delay_ms(200); 
   }
    password_counter=0;  
    password_reset();
   }
   
   safe_flag=1;
   
}
/***********************************************************************************************************/
void Enter_password (void){
 
   lcd_4bit_send_command(&lcd,_LCD_CLEAR);
   __delay_ms(55); 
   lcd_4bit_send_string_pos(&lcd,1,1," Enter Password");
   lcd_4bit_send_string_pos(&lcd,3,8," ____");
   display_counter=9;
   while(password_counter != 4){
       __delay_ms(60); 
        keypad_get_value(&keypad,&keypad_value);
        if(keypad_value != (0xff)){
          entered_value=entered_value*10+keypad_value;  
          convert_byte_to_string(keypad_value,display_value);
          lcd_4bit_send_string_pos(&lcd,3,display_counter,display_value);
            __delay_ms(200);
          lcd_4bit_send_string_pos(&lcd,3,display_counter,"*");
          display_counter++,password_counter++;
        }
           __delay_ms(200); 
   }
   password_counter=0;
   password();
}
/***********************************************************************************************************/
void App_ISR(void){
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
     lcd_4bit_send_string_pos(&lcd,2,10," Locker Stopped");
     lcd_4bit_send_string_pos(&lcd,3,1,"Try after 1 min");
     safe_flag=0;
      motor_stop(&motor);
      led_turn_off(&green_led);
      led_turn_off(&red_led);
     gpio_pin_Write_logic(&buzzer,LOW);
     __delay_ms(5000); 
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
}


/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/
static void password_handler(void){
    
   if (set_password1 == set_password2){
     high_pass=set_password1/100;
     low_pass=set_password2%100;
    
     Data_EEPROM_WriteByte(0x3F9,high_pass);
     Data_EEPROM_WriteByte(0x3FA,low_pass);
     password_flag=1,wrongs_counter=0;
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
     lcd_4bit_send_string_pos(&lcd,2,10," Password Set");
     lcd_4bit_send_string_pos(&lcd,3,1," Successfully");
     __delay_ms(1500); 
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
   } 
   else{
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
     lcd_4bit_send_string_pos(&lcd,2,10," Error,happened");
     lcd_4bit_send_string_pos(&lcd,3,1," Please,Try again");
     __delay_ms(1500); 
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
   }
   set_password1=0,set_password2=0,high_pass=0,low_pass=0; 
}
/**********************************************************************************************************************************************/
static void password(void){
    
    Data_EEPROM_ReadByte(0x3F9,&high_pass);
    Data_EEPROM_ReadByte(0x3FA,&low_pass);
    
    memory_value=high_pass*100+low_pass;
    
    if(memory_value==entered_value){
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
     lcd_4bit_send_string_pos(&lcd,2,10," Password Correct");
     led_turn_on(&green_led);
     motor_move_right(&motor);
     __delay_ms(2500); 
     motor_stop(&motor);
     led_turn_off(&green_led);
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
    }
    else{
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
     lcd_4bit_send_string_pos(&lcd,2,10," Password Wrong!!");
     led_turn_on(&red_led);
     gpio_pin_Write_logic(&buzzer,HIGH);
     __delay_ms(2500); 
     motor_stop(&motor);
     led_turn_off(&red_led);
     gpio_pin_Write_logic(&buzzer,LOW);
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
           
    }
    entered_value=0,memory_value=0;
}
/**********************************************************************************************************************************************/
static void password_reset(void){
    Data_EEPROM_ReadByte(0x3F9,&high_pass);
    Data_EEPROM_ReadByte(0x3FA,&low_pass);
    
    memory_value=high_pass*100+low_pass;
    
     if(memory_value==set_password1){
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
      high_pass=set_password2/100;
     low_pass=set_password2%100;
     Data_EEPROM_WriteByte(0x3F9,high_pass);
     Data_EEPROM_WriteByte(0x3FA,low_pass);
     
     lcd_4bit_send_string_pos(&lcd,2,1," Password Changed");
     lcd_4bit_send_string_pos(&lcd,3,1," Successfully");
     __delay_ms(1500); 
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
    }
     else{
           lcd_4bit_send_command(&lcd,_LCD_CLEAR);
     lcd_4bit_send_string_pos(&lcd,2,1," Password Wrong");
     lcd_4bit_send_string_pos(&lcd,3,1," Please,Try again");
     __delay_ms(1500); 
     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
     }
      set_password1=0,set_password2=0,high_pass=0,low_pass=0; 
      entered_value=0,memory_value=0;
}
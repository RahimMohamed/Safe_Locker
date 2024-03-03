/* 
 * File:   application.c
 * Author: Rahim Mohamed
 *
 * Created on March 2, 2024, 3:13 AM
 */

#include "application.h"
/******************************************************************************************************/


int main(int argc, char** argv) {

    
    intialization();
    welcome_message();
     
        
    while (1){
       lcd_4bit_send_string_pos(&lcd,1,1," Choose Your Process.");
        lcd_4bit_send_string_pos(&lcd,3,1,"1-Enter Password.");
        lcd_4bit_send_string_pos(&lcd,4,1,"2-Set New password.");
        keypad_get_value(&keypad,&keypad_value);
      
       if(keypad_value != (0xff)){
        switch (keypad_value){
             case 1:
                 if(password_flag==1&&safe_flag==1){
                     Enter_password();
                 }
                 else
                 {  
                     lcd_4bit_send_command(&lcd,_LCD_CLEAR);
                     lcd_4bit_send_string_pos(&lcd,1,5," Please,Enter");
                     lcd_4bit_send_string_pos(&lcd,2,1," Password first");
                      __delay_ms(2000); 
                      lcd_4bit_send_command(&lcd,_LCD_CLEAR);
                 }
                 break;
             case 2: 
                    Set_password();
                    break;
              default:
                  break;
         }  
          
        }
         __delay_ms(215); 
    }
    
    
    return (EXIT_SUCCESS);
}


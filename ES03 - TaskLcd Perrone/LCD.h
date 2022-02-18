#ifndef __STM32L476G_DISCOVERY_LCD_H
#define __STM32L476G_DISCOVERY_LCD_H
#include <stdint.h>
#define bool _Bool


typedef enum{BAR0,BAR1,BAR2,BAR3} bar;
void LCD_Init(void);
void LCD_bar(void);
void LCD_Clock_Init(void);
void LCD_PIN_Init(void);
void LCD_Configure(void);
void LCD_Clear(void);
void LCD_DisplayString(uint8_t* ptr);
void LCD_DisplayStringEx(uint8_t* ptr);
void LCD_WriteChar(uint8_t* ch, bool point, bool colon, uint8_t position);
static void LCD_Conv_Char_Seg(uint8_t* c,bool point,bool colon, uint8_t* digit);
void LCD_Display_Name(void);
void LCD_contrastoUp(void);
void LCD_contrastoDown(void);
uint8_t LCD_contrasto_value(void);
void LCD_contrasto_set(uint8_t c);
void LCDbarOn(bar b);
void LCDbarOff(bar b);


#endif /* __STM32L476G_DISCOVERY_LCD_H */

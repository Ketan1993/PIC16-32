/* 
 * File:   lcd.h
 * Author: ketan
 *
 * Created on 17 August, 2019, 2:56 PM
 */

#ifndef LCD_H
#define	LCD_H


#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

    /*LCD
    ----------------------------------------------------------------

     +- LCD function
     |       +- Processor pin
     |       |       +- Explorer 16/32 net name(s)
     |       |       |                 +- Other pin usage on board
     |       |       |                 |
    /===\ /=====\ /===============\ /========================================\
    D0   |  RE0  |  P93_LCDD0      |  
    D1   |  RE1  |  P94_LCDD1      |  
    D2   |  RE2  |  P98_LCDD2      |
    D3   |  RE3  |  P99_LCDD3      |  
    D4   |  RE4  |  P100_LCDD4     |  
    D5   |  RE5  |  P3_LCDD5       |  
    D6   |  RE6  |  P4_LCDD6       |  
    D7   |  RE7  |  P5_LCDD7       |  
    RS   |  RB15 |  P44_LCDRS      |  
    E    |  RD4  |  P81_LCDE       |  
    RW   |  RD5  |  P82_LCDRW      |  Disconnectable via J19

     */
    
#define LCD_LENGTH                      32
#define LCD_COMMAND_CLEAR_SCREEN        0x01
#define LCD_COMMAND_RETURN_HOME         0x02
#define LCD_COMMAND_ENTER_DATA_MODE     0x06
#define LCD_COMMAND_CURSOR_OFF          0x0C
#define LCD_COMMAND_CURSOR_ON           0x0F
#define LCD_COMMAND_MOVE_CURSOR_LEFT    0x10
#define LCD_COMMAND_MOVE_CURSOR_RIGHT   0x14
#define LCD_COMMAND_SET_MODE_4_BIT      0x28
#define LCD_COMMAND_SET_MODE_8_BIT      0x38
#define LCD_COMMAND_ROW_0_HOME          0x80
#define LCD_COMMAND_ROW_1_HOME          0xC0
#define LCD_START_UP_COMMAND_1          0x33    
#define LCD_START_UP_COMMAND_2          0x32    
#define LCD_CGRAM_ADDRESS               0x40

#define LCD_MAX_COLUMN      16

#define CS1_BASE_ADDRESS    0x00020000ul

    typedef struct lcdDisplay lcdDisplay;

    struct lcdDisplay {
        bool (*LCD_open)(void);
        bool (*LCD_CommandWrite)(uint8_t Commnad);
        bool (*LCD_Clear)(lcdDisplay *dis);
        bool (*LCD_DataWrite)(char WriteBuf);
        uint8_t LCD_Length;
        bool allocated;
    };

    bool LcdMasterWriteString(lcdDisplay *disInstance, const char *buf, uint8_t line, bool flag);
    typedef lcdDisplay *(LcdDisplayCreate) (uint8_t inst);
    LcdDisplayCreate LcdDisplayInternalCreate;

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */


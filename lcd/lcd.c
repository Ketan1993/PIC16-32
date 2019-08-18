#include <stdint.h>
#include "../common_def.h"
#include "lcd.h"
#include "../delay.h"

/* Private Functions *************************************************/


bool Opne_Display(void);
bool LCD_Command(uint8_t Commnad);
bool LCD_Clear(lcdDisplay *dis);
bool LCD_Data(char WriteBuf);

/* Private variables ************************************************/
static __eds__ unsigned int __attribute__((noload, section("epmp_cs1"), address(CS1_BASE_ADDRESS))) ADDR0 __attribute__((space(eds)));
static __eds__ unsigned int __attribute__((noload, section("epmp_cs1"), address(CS1_BASE_ADDRESS))) ADDR1 __attribute__((space(eds)));

typedef struct displayInt {
    lcdDisplay dis;
} displayInt;

static displayInt DisplayInstance[1] = {
    {
        {
            Opne_Display, //opening LCD core
            LCD_Command, //send CMD to LCD
            LCD_Clear, //clear LCD Display
            LCD_Data, //send data to LCD
            LCD_LENGTH, //max length of LCD
            false
        }
    }
};

bool LCD_Command(uint8_t Commnad) {
    ADDR0 = Commnad;
    delay_ms(2);

    return true;
}

bool LCD_Data(char WriteBuf) {
    ADDR1 = WriteBuf;
    delay_ms(5);

    return true;
}

bool LCD_Clear(lcdDisplay *dis) {

    if (!dis)
        return false;

    //clear the LCD screen
    dis->LCD_CommandWrite(LCD_COMMAND_CLEAR_SCREEN);

    //return to home cursor
    dis->LCD_CommandWrite(LCD_COMMAND_RETURN_HOME);

    return true;
}

bool LcdMasterWriteString(lcdDisplay *disInstance, const char *buf, uint8_t line, bool flag) {

    displayInt *display = (displayInt*) disInstance;

    uint8_t index_len = 0;
    uint8_t row = 0;
    uint8_t column = 0;
    if (!display) {
        return false;
    }
    if (line > 3) {
        return false;
    }
    uint8_t len = strlen((const char*) buf);


    if (line == 1) {
        display->dis.LCD_CommandWrite(LCD_COMMAND_ROW_0_HOME);
    } else {
        display->dis.LCD_CommandWrite(LCD_COMMAND_ROW_1_HOME);
    }
    if (flag) {
        display->dis.LCD_Clear(&display->dis);
    }

    while (index_len != len) {

        if (index_len >= LCD_LENGTH) {
            break;
        }

        if (column >= LCD_MAX_COLUMN) {
            column = 0;
            if (row == 0) {
                display->dis.LCD_CommandWrite(LCD_COMMAND_ROW_1_HOME);
                row = 1;
            } else {
                display->dis.LCD_CommandWrite(LCD_COMMAND_ROW_0_HOME);
                row = 0;
            }
        }

        display->dis.LCD_DataWrite(*buf++);
        column++;

        index_len++;
    }
    return true;
}

bool Opne_Display(void) {
    //address and data will be on separated pin
    PMCON1bits.ADRMUX = 0;
    //continue read in idle mode
    PMCON1bits.PSIDL = 0;

    //master mode
    PMCON1bits.MODE = 3;

    //chip 1 is selected
    PMCON1bits.CSF = 0;

    //address Latch polarity is Active-low
    PMCON1bits.ALP = 0;

    //disable smart mode
    PMCON1bits.ALMODE = 0;

    //No interrupt generate
    PMCON1bits.IRQM = 0;

    //no used of high-impedance
    PMCON1bits.BUSKEEP = 0;

    // CS1 start address
    PMCS1BS = (CS1_BASE_ADDRESS >> 8);

    PMCS1CFbits.CSDIS = 0; // enable CS
    PMCS1CFbits.CSP = 1; // CS1 polarity
    PMCS1CFbits.BEP = 1; // byte enable polarity
    PMCS1CFbits.WRSP = 1; // write strobe polarity
    PMCS1CFbits.RDSP = 1; // read strobe polarity
    PMCS1CFbits.CSPTEN = 1; // enable CS port
    PMCS1CFbits.SM = 0; // read and write strobes on separate lines
    PMCS1CFbits.PTSZ = 2; // data bus width is 16-bit
    PMCS1MDbits.ACKM = 0; // PMACK is not used

    // The device timing parameters. Set the proper timing
    // according to the device used (the timing macros are defined in the hardware profile)
    PMCS1MDbits.DWAITB = 0b11; // access time 3 1/4 Tcy
    PMCS1MDbits.DWAITM = 0b1111;
    PMCS1MDbits.DWAITE = 0b11;


    // don't care since CS2 is not be used
    PMCON2bits.RADDR = 0;

    //Parallel master port writen enable
    PMCON3bits.PTWREN = 1;

    //parallel read Mode Enable
    PMCON3bits.PTRDEN = 1;

    //parallel master mode high nibble enable bit
    PMCON3bits.PTBE0EN = 1;

    //parallel master mode low nibble engable bit
    PMCON3bits.PTBE1EN = 1;

    PMCON3bits.AWAITM = 0b11; // set address latch pulses width to 3 1/2 Tcy
    PMCON3bits.AWAITE = 1; // set address hold time to 1 1/4 Tcy

    PMCON4 = 0x0001; // PMA0 - PMA15 address lines are enabled

    //enble the parallel master mode
    PMCON1bits.PMPEN = 1;

    //wait until 
    delay_ms(600);

    return true;

}

lcdDisplay *LcdDisplayInternalCreate(uint8_t inst) {

    displayInt *display = &DisplayInstance[inst];

    if (display->dis.allocated) {
        return false;
    }
    //initialized the driver
    display->dis.allocated = true;

    //open the driver
    display->dis.LCD_open();

    //lcd start-up command
    display->dis.LCD_CommandWrite(LCD_START_UP_COMMAND_1);

    //lcd start-up command
    display->dis.LCD_CommandWrite(LCD_START_UP_COMMAND_2);

    //set lcd Data mode
    display->dis.LCD_CommandWrite(LCD_COMMAND_SET_MODE_8_BIT);

    //set LCD cursor off command
    display->dis.LCD_CommandWrite(LCD_COMMAND_CURSOR_OFF);

    //set LCD data mode command
    display->dis.LCD_CommandWrite(LCD_COMMAND_ENTER_DATA_MODE);

    //clear the display
    display->dis.LCD_Clear(&display->dis);

    return (lcdDisplay*) display;

}


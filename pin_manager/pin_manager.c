#include "../pin_config.h"

void PIN_MANAGER_initialaztion(void) {
    RA0_SetDigitalOutput(); //RA0 as output
    Nop();
    RA1_SetDigitalOutput();  //check the power on reset happen 
    Nop();
    RA2_SetDigitalOutput();  //check the software reset happen 
    Nop();
    RF4_SetDigitalInput();    //RX PIN
    Nop();
    RF5_SetDigitalOutput();   //TX PIN
    Nop();
    
    __builtin_write_OSCCONL(OSCCON & 0xbf);

    /************** Peripheral Pin Configure for Debug ************************/

    RPINR19bits.U2RXR = 10; //  Debug UART Receiver
    Nop();
    RPOR8bits.RP17R = 5; //  Debug UART Transmitter
    Nop();

    __builtin_write_OSCCONL(OSCCON | 0x40);
    
}
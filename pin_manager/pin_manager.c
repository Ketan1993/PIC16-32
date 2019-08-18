#include "../pin_config.h"

void PIN_MANAGER_initialaztion(void) {
    RA0_SetDigitalOutput(); //RA0 as output

    
    RF4_SetDigitalInput();    //RX PIN
    RF5_SetDigitalOutput();   //TX PIN
    
    __builtin_write_OSCCONL(OSCCON & 0xbf);

    /************** Peripheral Pin Configure for Debug ************************/

    RPINR19bits.U2RXR = 10; //  Debug UART Receiver
    Nop();
    RPOR8bits.RP17R = 5; //  Debug UART Transmitter
    Nop();

    __builtin_write_OSCCONL(OSCCON | 0x40);
    
}
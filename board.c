#include "main.h"
#include "systems.h"
#include "pin_config.h"
#include "delay.h"
#include "uart/uart.h"
#include "lcd/lcd.h"
#include "utility/serial_log.h"

void SYSTEMS_Initialization(void) {
    SYSTEMS_Clock(); //intialization for the systems clock.
    PIN_MANAGER_initialaztion(); //intialiazation for the pin mapping
}

ApplicationSt g_globalStrcut;

void Board_Initialization(void) {

    char buf[35];
    //initilazation for the UART
    g_globalStrcut.uart = UART_CoreDriverInit(0);

    //initilazation for the lCD
    g_globalStrcut.display = LcdDisplayInternalCreate(0);

    sprintf(buf, "WELCOME TO TEST    VER %s", SOFTWARE_VERSION);
    LcdMasterWriteString(g_globalStrcut.display, buf, 1, true);

    delay_sec(1);
}

static void checResetReason(void) {
    if (RCONbits.POR) {
        RA1_Toggle();
        RCONbits.POR = 0;
        Nop();
    }
    if (RCONbits.SWR) {
        RA2_Toggle();
        RCONbits.SWR = 0;
        Nop();
    }
}

void Main_Application(void) {
    Board_Initialization(); // this function will initialize driver sub routine for the controller
    char lcdString[] = "HELLO THIS IS THE LCD TEST !!! ";
    char uartString[] = "HELLO THIS IS THE UART TEST !!! ";

    //checResetReason();
    while (1) {
        RA0_Toggle();
        delay_sec(1);

        LcdMasterWriteString(g_globalStrcut.display, lcdString, 1, true);
#if LOGLEVEL >= LOG_INFO
        UART_PRINT(g_globalStrcut.uart, uartString);
#endif
    }
}

#include "main.h"
#include "systems.h"
#include "pin_config.h"
#include "delay.h"
#include "uart/uart.h"
#include "lcd/lcd.h"

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

    delay_sec(2);
}

void Main_Application(void) {
    Board_Initialization(); // this function will initialize driver sub routine for the controller
    char *lcdString = "HELLO THIS IS THE LCD TEST !!! ";

    while (1) {
        RA0_Toggle();
        delay_sec(1);
        LcdMasterWriteString(g_globalStrcut.display, lcdString, 1, true);
        UART_Transmite(g_globalStrcut.uart, '1');

    }
}

#include "main.h"
#include "systems.h"
#include "pin_config.h"
#include "delay.h"

void SYSTEMS_Initialization(void)
{
    SYSTEMS_Clock();              //intialization for the systems clock.
    PIN_MANAGER_initialaztion();  //intialiazation for the pin mapping
}

void Board_Initialization(void)
{
    
}

void Main_Application(void)
{
    Board_Initialization();   // this function will initialize driver sub routine for the controller
    while(1)
    {
        RA0_Toggle();
        delay_ms(1000);
        RA1_Toggle();
        delay_ms(1000);
        RA2_Toggle();
        delay_ms(1000);
        RA3_Toggle();
        delay_ms(1000);
        RA4_Toggle();
        delay_ms(1000);
        RA5_Toggle();
        delay_ms(1000);
        RA6_Toggle();
        delay_ms(1000);
        RA7_Toggle();
    }
}

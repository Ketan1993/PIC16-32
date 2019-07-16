#include "../pin_config.h"


void PIN_MANAGER_initialaztion(void)
{
    RA0_SetDigitalOutput();   //RA0 as ouput led
    RA1_SetDigitalOutput();   //RA1 as output
    RA2_SetDigitalOutput();   //RA2 as output
    RA3_SetDigitalOutput();   //RA3 as output
    RA4_SetDigitalOutput();   //RA4 as output
    RA5_SetDigitalOutput();   //RA5 as output
}
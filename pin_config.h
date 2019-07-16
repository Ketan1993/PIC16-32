/* 
 * File:   pin_config.h
 * Author: ketan
 *
 * Created on 10 July, 2019, 3:47 PM
 */

#ifndef PIN_CONFIG_H
#define	PIN_CONFIG_H
#include "systems.h"
#ifdef	__cplusplus
extern "C" {
#endif



    /* LED pin mapping with MCU
     * ---------  ---------
     * DEV pin  |  MCU PIN  | 
     * --------   ---------  
     * P17_LED3 |  RA0
     * P38_LED4 |  RA1
     * P58_LED5 |  RA2
     * P59_LED6 |  RA3
     * P60_LED7 |  RA4
     * P61_LED8 |  RA5
     */

#define RA0_SetDigitalOutput()         do{ TRISAbits.TRISA0 = 0;} while(0)    
#define RA0_Toggle()                   do{ LATAbits.LATA0 = ~LATAbits.LATA0; }while(0)

#define RA1_SetDigitalOutput()         do{ TRISAbits.TRISA1 = 0;} while(0)    
#define RA1_Toggle()                   do{ LATAbits.LATA1 = ~LATAbits.LATA1; }while(0)

#define RA2_SetDigitalOutput()         do{ TRISAbits.TRISA2 = 0;} while(0)    
#define RA2_Toggle()                   do{ LATAbits.LATA2 = ~LATAbits.LATA2; }while(0)

#define RA3_SetDigitalOutput()         do{ TRISAbits.TRISA3 = 0;} while(0)    
#define RA3_Toggle()                   do{ LATAbits.LATA3 = ~LATAbits.LATA3; }while(0)

#define RA4_SetDigitalOutput()         do{ TRISAbits.TRISA4 = 0;} while(0)    
#define RA4_Toggle()                   do{ LATAbits.LATA4 = ~LATAbits.LATA4; }while(0)

#define RA5_SetDigitalOutput()         do{ TRISAbits.TRISA5 = 0;} while(0)    
#define RA5_Toggle()                   do{ LATAbits.LATA5 = ~LATAbits.LATA5; }while(0)

    void PIN_MANAGER_initialaztion(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PIN_CONFIG_H */


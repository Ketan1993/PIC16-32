/* 
 * File:   main.h
 * Author: ketan
 *
 * Created on 10 July, 2019, 3:37 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SOFTWARE_VERSION         ((char*)("1.0.0"))
    
    typedef struct ApplicationSt{
        
        struct UART_Internal *uart;
        struct lcdDisplay *display;
        
    }ApplicationSt;
    
    extern ApplicationSt g_globalStrcut;
    
    void SYSTEMS_Initialization(void);
    void Board_Initialization(void);
    void Main_Application(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */


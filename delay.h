/* 
 * File:   delay.h
 * Author: ketan
 *
 * Created on 16 July, 2019, 10:38 PM
 */

#ifndef DELAY_H
#define	DELAY_H

#define FCY 16000000UL

#include <libpic30.h>

#ifdef	__cplusplus
extern "C" {
#endif

    /* delay in milli second 
     * Before use this function, define the FCY XXXXX in header file and #include <libpic30.h>
     * delay_count : delay count in milli second
     * return      : it's delay not need of return value
     */
    void delay_ms(int delay_count);

    /* delay in micro-second 
     * Before use this function, define the FCY XXXXX in header file and #include <libpic30.h>
     * delay_count : delay count in micro-second
     * return      : it's delay not need of return value
     */
    void delay_us(int delay_count);


#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */


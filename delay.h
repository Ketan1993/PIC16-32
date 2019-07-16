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

    void delay_ms(int delay_count);
    void delay_us(int delay_count);


#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */


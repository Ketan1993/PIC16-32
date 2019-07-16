/* 
 * File:   systems.h
 * Author: ketan
 *
 * Created on 10 July, 2019, 3:30 PM
 */

#ifndef SYSTEMS_H
#define	SYSTEMS_H

//common header file for PIC24FJ128GA series controller 
#include <xc.h>



#ifdef	__cplusplus
extern "C" {
#endif

    
    void SYSTEMS_Clock(void);
    void SOSC_Configuration(void);

    void __attribute__((__interrupt__, auto_psv)) _OscillatorFail(void);
    void __attribute__((__interrupt__, auto_psv)) _AddressError(void);
    void __attribute__((__interrupt__, auto_psv)) _StackError(void);
    void __attribute__((__interrupt__, auto_psv)) _MathError(void);

    void __attribute__((__interrupt__, auto_psv)) _AltOscillatorFail(void);
    void __attribute__((__interrupt__, auto_psv)) _AltAddressError(void);
    void __attribute__((__interrupt__, auto_psv)) _AltStackError(void);
    void __attribute__((__interrupt__, auto_psv)) _AltMathError(void);




#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEMS_H */


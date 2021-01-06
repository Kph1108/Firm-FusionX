/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Enable interrupts */
//    PCONbits.SBODEN = 1;
    WDTCON = 0x17;               //Watch Dog timer reset to 1:65536 SWDTEN set high 2s nominal
    //OPTION_REGbits.nGPPU = 0;   // All internal pull up are enabled
    PORTA =0;
    LATA = 0;
    ANSELA = 0;
    PORTC =0;
    LATC = 0;
    ANSELC = 0;
    
    //Set Outputs
    TRISA = ~(_TRISA_TRISA2_MASK + _TRISA_TRISA4_MASK); //PINS of PortA as output
    TRISC = ~(_TRISC_TRISC0_MASK + _TRISC_TRISC1_MASK + _TRISC_TRISC2_MASK); //PINS of PortA as output
    OUT1 = (0);
    OUT2 = (0);
    OUT3 = (0);
    OUT4 = (0);
    //Set Inputs
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;
  
    //ANSELAbits.ANSA5 = 0;
    TRISAbits.TRISA5 = 1;
    //WPUA = 0x20;                    //weak pull up enabled for RA5;
    //WPUC = 0x00;                    //weak pull up enabled for RA5;
   
    bGLOBAL_ENABLE_LEDS = false;

    /*interrupt setup */
    // Loop to make sure Sync line is pulled high before starting the program
    CLRWDT();
    WaitForSYNC_PU();               //Typical time till Pull up stabilized < ~2.5ms
   
    //WaitForSYNC_PU();              //Typical time till pull up stabilized at this location < ~1.7ms
    /* Timer 0 setup */
    //TMR2 = Background_Interrupt_Timer;
    T2CON |= 0;        // bits 6-3 Post scaler 1:1 thru 1:16
    T2CONbits.TMR2ON = 1;  // bit 2 turn timer2 on;
    T2CONbits.T2CKPS1 = 1; // bits 1-0  Prescaler Rate Select bits
    T2CONbits.T2CKPS0 = 0;
    PR2 = 12;         // PR2 (Timer2 Match value)
    TMR2IE = 1;
    PEIE = 1;
    GIE = 1;
}


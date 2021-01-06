/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */



/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
volatile unsigned char GLOBAL_sub_patterns_index = 0;         //used to communicate the selected sub pattern
volatile unsigned char GLOBAL_sub_patterns_index_copy = 0;
volatile unsigned char GLOBAL_sub_patterns_column_index = 0;  //used to move inside the selected sub pattern
volatile unsigned char GLOBAL_combo_patterns_index = 0;       //used to communicate the selected combo pattern
volatile unsigned char GLOBAL_combo_patterns_index_copy = 0;
volatile unsigned char GLOBAL_combo_patterns_column_index = 0;//used to move inside the selected combo pattern
volatile unsigned char GLOBAL_sub_patterns_timer=0;       //used to update the timer counter
volatile unsigned char GLOBAL_combo_patterns_counter=0;
volatile unsigned char GLOBAL_Selected_Mode_Number = 0;
volatile unsigned char GLOBAL_Selected_Mode_Type = 0;
volatile unsigned char GLOBAL_Selected_Mode_Type_copy = 0;
volatile unsigned char GLOBAL_Dummy_Counter = 0;
volatile unsigned char GLOBAL_Dummy_Counter2 = 0;
volatile unsigned char GLOBAL_MODE1_counter  = 0 ;
volatile unsigned char GLOBAL_SYNC_Line_counter  = 0;
volatile unsigned char GLOBAL_MODE2_counter  = 0;
volatile unsigned char COLOR_DETECT_counter = 0;
volatile unsigned char GLOBAL_MODE1_LOW_counter  = 0;
volatile unsigned char GLOBAL_SYNC_Line_LOW_counter  = 0;
volatile unsigned char GLOBAL_MODE2_LOW_counter  = 0;
volatile unsigned char COLOR_DETECT_LOW_counter = 0;
volatile unsigned char GLOBAL_Mode_copy[MAX_MODES] = 0;
volatile unsigned char GLOBAL_SYNC_PULSE_Counter = 0;
volatile unsigned char GLOBAL_CHANNELS_EN_copy =0;

volatile unsigned char GLOBAL_Sync_Count_truefalse = 0;
volatile unsigned char GLOBAL_Sync_Count_LOW_truefalse  = 0;

volatile bool bGLOBAL_DISABLE_SYNC_Line_PRESSED = false;
volatile bool bGLOBAL_CHANGING_PATTERN = false;
volatile bool bGLOBAL_CHANGING_PATTERN_Enforce = false;
volatile bool bGLOBAL_SYNC_SENT = false;
volatile bool bGLOBAL_END_OF_CYCLE_COND1 = false;
volatile bool bGLOBAL_END_OF_CYCLE_COND2 = false;
volatile bool bGLOBAL_IS_PROGRAMMING = false;
volatile bool bGLOBAL_InPhase;
volatile bool bGLOBAL_InPhase_copy[MAX_MODES];
volatile bool bGLOBAL_ENABLE_LEDS = false;

volatile bool enableOutputsToFlashPatterns = false;

volatile bool bGLOBAL_MODE1_PRESSED = false;
volatile bool bGLOBAL_MODE2_PRESSED = false;
volatile bool bCOLOR_DETECT_PRESSED = false;
volatile bool bPrev_COLOR_DETECT_PRESSED = false;
volatile bool bGLOBAL_SYNC_Line_PRESSED = false;
volatile bool SYNC_LINE_TRUE = false;
volatile bool bGLOBAL_OUTPUT_BUFFER_CHANGED = false;
volatile bool bGLOBAL_STEADY_ON = false;

volatile unsigned char colorState[MAX_MODES] = {0,0,0};
volatile unsigned char currentColorCounter = 0;
volatile unsigned char currentColor = 99;

volatile unsigned char OUTPUT_BUFFER = 0; //OUTPUT_BUFF_type
volatile unsigned char OUTPUT_BUFFER_COPY = 0;

volatile unsigned char CurrentColorMax[Chan1Chan2Chan3Chan4+1] = {1,1,1,1,2,2,2,2,2,2,3,3,3,4};

static unsigned char hasNotBeenSet = 1;

volatile bool GLOBAL_changedModePattern = false;

const unsigned char ROM_Sub_Patterns [MAX_Sub_Patterns][MAX_Sub_Patterns_Columns] = {
// ALL Channels disabled
    {{OFFF},                                                            //0
    {OFFF},
    {OFFF},
    {OFFF},
    {OFFF},
    {OFFF},
    {OFFF}},
// End of ALL Channels disabled

     {{BOTH},                                                               //1
     {BOTH},
     {BOTH},   //Had to change this frame from BOTH so that there would be enough off time 300ms to get 120 FPM. KPH 01/25/2019
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH}},

     {{OFFF},                                                                //2
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF}},

     {{BOTH},                                                               //3
     {BOTH},
     {BOTH},  //Had to change this frame from BOTH so that there would be enough off time 480ms to get 75 FPM. KPH 01/25/2019
     {BOTH},   //Had to change this to split up frame 2 and 3 from 18 into 2 for timing of sync being pulled low.
     {BOTH},
     {BOTH},
     {BOTH}},
// Double
     {{BOTH},                                                               //4
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH}},
// tripple
     {{BOTH},                                                               //5
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH}},

 // Double fast
     {{BOTH},                                                               //6
     {OFFF},
     {BOTH},
     {OFFF},
     {OFF},
     {OFFF},
     {BOTH}},

  // tripple fast
     {{BOTH},                                                               //7
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH}},
    
     {{BOTH},                                                               //8
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH}},

    ////////////////////////////////////////////////////////////////
    
     {{OFFF},                                                               //9
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF}},
    
     {{BOTH},                                                               //10
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH}},
    
     {{BOTH},                                                               //11
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH}},
    
     {{OFFF},                                                               //12
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF}},
    
     {{BOTH},                                                               //13
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH}},
    
     {{OFFF},                                                               //14
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF}},
    
     {{BOTH},                                                               //15
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH}},
    
     {{OFFF},                                                               //16
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF}},
     
     {{OFFF},                                                               //17
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF}}
};
const unsigned char ROM_Sub_Patterns_Time [MAX_Sub_Patterns][MAX_Sub_Patterns_Columns] = {
    {14,16, 0, 0, 0, 0, 0},          //0 Single Color Ch1 or Ch2 OFF    Fast
    {10,10, 0, 0, 0, 0, 0},         //1 Single Color Ch1 or Ch2 Single Fast
    {25,14, 9, 0, 0, 0, 0},          //2 Single Color Ch1 or Ch2 OFF    Slow               //This DOES affect single color dual slow pattern off time.
    {16,16, 0, 0, 0 , 0, 0},             //3 Single Color Ch1 or Ch2 Single Slow
    {16, 8, 16, 0, 0, 0, 0},       //4 Single Color Ch1 or Ch2 Double Slow                 //Index 4+2 of this array=Double slow  //This DOES affect double slow patterns. Both Color 1 and 2 independentaly. It affects the combo slow fast pattern as well. Does not affect the dual color patterns though including dead time and no dead time.
    {11, 4, 11, 4, 11, 0, 0},      //5 Single Color Ch1 or Ch2 Triple Slow
    {10, 5, 10, 0, 0, 0, 0},        //6 Single Color Ch1 or Ch2 Double Fast
    {7, 3, 6, 3, 6, 0, 0},          //7 Single Color Ch1 or Ch2 Triple Fast
    {10,10, 6, 0, 0, 0, 0},         //8
    
    {8,9,0,0,0,0,0},                //9
    {8,8,0,0,0,0,0},                //10
    {3,3,7,0,0,0,0},                //11
    {7,8,0,0,0,0,0},                //12
    {3,3,3,3,3,3,7},                //13
    {13,13,0,0,0,0,0},              //14
    {4,7,0,0,0,0,0},                //15
    {4,6,0,0,0,0,0},//16
    
    {25,16, 0, 0, 0, 0, 0}, //17 Instead of 2 used 17
    {14,12, 0, 0, 0, 0, 0}, //18 Instead of 0 used 18,
    ///////////Every time above is for single color patterns.///////////////   
 
//    {35, 6, 0, 0, 0, 0, 0},          //8 CHN1 SLOW
//    {35, 6, 0, 0, 0, 0, 0},          //9 CHN2 SLOW
//    {35, 6, 0, 0, 0, 0, 0},          //10 ALL CHN OFF SLOW For dead time
//    {15, 6, 0, 0, 0, 0, 0},          //11 CHN1 FAST
//    {15, 6, 0, 0, 0, 0, 0},          //12 CHN2 FAST
//    {15, 6, 0, 0, 0, 0, 0},          //13 ALL CHN OFF FAST for dead time
//    { 1, 2, 1,10, 0, 0, 0},          //14 Double slow CH1                     //This only affects Color 1 on dual color patterns not single color patterns.
//    { 16, 8, 16,40, 0, 0, 0},          //15 Double slow CH2
//    { 16, 8, 16,40, 0, 0, 0},          //16 Double slow OFF TIME
//    { 6, 6, 6,15, 0, 0, 0},          //17 Double fast CH1
//    { 6, 6, 6,15, 0, 0, 0},          //18 Double fast CH2
//    { 6, 6, 6,15, 0, 0, 0},          //19 Double fast OFF TIME
//    { 8, 8, 8, 8, 8,35, 0},          //20 Triple slow CH1
//    { 8, 8, 8, 8, 8,35, 0},          //21 Triple slow CH2
//    { 8, 8, 8, 8, 8,35, 0},          //22 Triple slow OFF TIME
//    { 6, 6, 6, 6, 6,15, 0},          //23 Triple fast CH1
//    { 6, 6, 6, 6, 6,15, 0},          //24 Triple fast CH2
//    { 6, 6, 6, 6, 6,15, 0},          //25 Triple fast OFF TIME
//    {10,10, 0, 0, 0, 0, 0},          //26 CHN1 Steady
//    {10,10, 0, 0, 0, 0, 0},          //27 CHN2 Steady
//    { 6, 6, 6, 6, 6, 6, 0},          //28 Triple fast CH1 Brake
//    { 6, 6, 6, 6, 6, 6, 0},          //29 Triple fast CH2 Brake
};
const unsigned char ROM_COMBO_Patterns_TwoFour [MAX_Combo_Patterns][MAX_Combo_Patterns_Columns] = {
    { 3, 2, 3, 2,3,2,3,2,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //0 single slow
    { 1, 0, 1, 0,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //1 single fast
    { 3, 2, 3, 2, 3, 2, 1, 0, 1, 0, 1, 0, 1, 0,99,99,99,99,99,99,99,99},       //2 combo
    { 4, 17, 4, 17,4,17,4,17,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //3 double slow
    { 6, 18, 6, 18,6,18,6,18,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //4 double fast
    { 4, 17, 4, 17, 4, 17, 6, 18, 6, 18, 6, 18, 6, 18,99,99,99,99,99,99,99,99},       //5 combo
    { 5, 17, 5, 17,5,17,5,17,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //6 triple slow
    { 7, 18, 7, 18,7,18,7,18,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //7 triple fast
    { 5, 17, 5, 17, 5, 17, 7, 18, 7, 18, 7, 18, 7, 18,99,99,99,99,99,99,99,99},       //8 combo
    { 13, 14, 13, 14,15,15,16,16,15,15,16,16,11,12,11,12,10,9,10,9,10,9,99},       //9 Attack 1
    { 10, 9, 10, 9, 13, 13, 16, 16, 15, 15, 16, 16, 15, 15, 16, 16, 15, 15, 13, 14, 13, 14,99},       //10 Attack 2
    { 7, 8, 8, 8,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //11 Brake, 6 LED Tripple fast then 6 LED steady ON
    { 8, 8, 8, 8,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //12 Steady on 12 LED
    { 8, 8, 8, 8,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99}       //13  Steady on 12 LED dim
};

const unsigned char ROM_COMBO_Patterns_Three [MAX_Combo_Patterns][MAX_Combo_Patterns_Columns] = {
//  { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,24,25,25,26,26,27,27,28,28,29,29,30,30}
    { 3, 2, 3, 2,3,2,99},       //0 single slow
    { 1, 0, 1, 0,1,0,99},       //1 single fast
    { 3, 2, 3, 2, 3, 2, 1, 0, 1, 0, 1, 0, 1, 0,99,99,99,99,99,99,99,99},       //2 combo
    { 4, 2, 4, 2,4,2,99},       //3 double slow
    { 6, 18, 6, 18,6,18,99},       //4 double fast
    { 4, 2, 4, 2, 4, 2, 6, 18, 6, 18, 6, 18, 6, 18,99,99,99,99,99,99,99,99},       //5 combo
    { 5, 2, 5, 2,5,2,99},       //6 triple slow
    { 7, 18, 7, 18,7,18,99},       //7 triple fast
    { 5, 2, 5, 2, 5, 2, 7, 18, 7, 18, 7, 18, 7, 18,99,99,99,99,99,99,99,99},       //8 combo
    
    { 13, 14, 13, 14,15,15,16,16,15,15,16,16,11,12,11,12,10,9,10,9,10,9,99},       //9 Attack 1
    { 10, 9, 10, 9, 13, 13, 16, 16, 15, 15, 16, 16, 15, 15, 16, 16, 15, 15, 13, 14, 13, 14,99},       //10 Attack 2
    
    { 7, 8, 8, 8,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //11 Brake, 6 LED Tripple fast then 6 LED steady ON
    { 8, 8, 8, 8,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //12 Steady on 12 LED
    { 8, 8, 8, 8,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99}       //13  Steady on 12 LED dim
};

volatile unsigned char channelToBeDisplayed = 0;
volatile unsigned char GLOBAL_CHANNELS_EN_DUAL = 0;
volatile unsigned bool pwmBool = false;
volatile unsigned char pwmStartUpCount = 0;

volatile unsigned bool GLOCAL_Program_Color = false;

volatile unsigned bool bGiveControlToColorProgram = false;

volatile unsigned char startUpProgram = 0;
static unsigned char indexOfMode = 0;
/*
 * Description of the COMBO matrix :
 * {Sub_Pattern_index, # of repetition, Sub_Pattern_index, # of repetition, ... }
 * {Sub_Pattern_index, # of repetition, Sub_Pattern_index, # of repetition, ... }
 *
 *
 */
eeprom unsigned char EEprom_mode [MAX_MODES];
eeprom unsigned char EEprom_Written_Flag;
eeprom unsigned char EEpromNeverWritten_Flag;
eeprom bool EEprom_InPhase [MAX_MODES];
eeprom unsigned char EEprom_ColorState[MAX_MODES];

static unsigned long counter = 0;
static unsigned long counter2 = 0;
static unsigned char state = 0; 

static unsigned long colorResetCounter = 0;

volatile unsigned char earlyOutput = 0;

inline void GPIO(unsigned char i)
{
    if(i==0)
    {
        if((i&0x04) == 0x04)
        {
            OUT3 = 1;
        }
        else
        {
            OUT3 = 0;
        }

        if((i&0x02) == 0x02)
        {
            OUT2 = 1;
        }
        else
        {
            OUT2 = 0;
        }

        if((i&0x01) == 0x01)
        {
            OUT1 = 1;
        }
        else
        {
            OUT1 = 0;
        }

        if((i&0x08) == 0x08)
        {
            OUT4 = 1;
        }
        else
        {
            OUT4 = 0;
        }
    }
    else
    {
        if((i&0x04) == 0x04)
        {
            OUT3 = 1;
        }
        else
        {
            OUT3 = 0;
        }

        if((i&0x02) == 0x02)
        {
            OUT2 = 1;
        }
        else
        {
            OUT2 = 0;
        }

        if((i&0x01) == 0x01)
        {
            OUT1 = 1;
        }
        else
        {
            OUT1 = 0;
        }

        if((i&0x08) == 0x08)
        {
            OUT4 = 1;
        }
        else
        {
            OUT4 = 0;
        }
        
        if((i&0x20) == 0x20)
        {
            SYNC_CTRL = 1;
        }
        else
        {
            SYNC_CTRL = 0;
        }
    }

    //SYNC_CTRL = (i&0x20)>>5;
}

void SetOUTPUT(void)
{
    static unsigned char temporaryGPIO = 0x00;
	static unsigned char pwmCounter = 0;
    
    startUpProgram++;
    if(startUpProgram>START_UP_TIME)
    {
        startUpProgram=START_UP_TIME+2;
        enableOutputsToFlashPatterns = true;
    }
    
    if(startUpProgram<START_UP_TIME)
    {
        //OUTPUT_BUFFER = OUTPUT_BUFFER&0x20;
        bGLOBAL_ENABLE_LEDS = false;
        OUT1 = (0);
        OUT2 = (0);
        OUT3 = (0);
        OUT4 = (0);
        enableOutputsToFlashPatterns = false;
    }
    
    if(GLOBAL_changedModePattern == true)
    {
        GLOBAL_changedModePattern = false;
    }
    
    {
        if(enableOutputsToFlashPatterns==true)
        {
            if(bGiveControlToColorProgram == false)// && startUpProgram == true)
            {
                if (bGLOBAL_ENABLE_LEDS && !bCOLOR_DETECT_PRESSED)
                {        
                    if(currentColor == 0)
                    {
                        temporaryGPIO = OUTPUT_BUFFER & CH1_SYNC;
                    }
                    else if(currentColor ==1)
                    {
                        temporaryGPIO = OUTPUT_BUFFER & CH2_SYNC;
                    }
                    else if(currentColor ==2)
                    {
                        temporaryGPIO = OUTPUT_BUFFER & CH3_SYNC;
                    }
                    else if(currentColor ==3)
                    {
                        temporaryGPIO = OUTPUT_BUFFER & CH4_SYNC;
                    }

                    if(pwmBool == true)
                    {
                        pwmCounter++;
                        if(pwmCounter<5)
                        {
                            GPIO(temporaryGPIO);
                        }
                        else
                        {
                            GPIO(0);
                        }

                        if(pwmCounter>11)
                        {
                            pwmCounter = 0;
                        }
                    }
                    else
                    {
                        GPIO(temporaryGPIO);
                    }   
                }
                else
                {
					if (bGLOBAL_IS_PROGRAMMING)
                    {
                        if (!bGLOBAL_CHANGING_PATTERN)
                        {
                            if (bGLOBAL_InPhase)
                                GPIO(CH1_SYNC);
                            else
                                GPIO(CH2_SYNC);
                        }
                    }
					else
					{
						GPIO(0);
					}
                }
            }
            else
            {
                temporaryGPIO = OUTPUT_BUFFER & 0x20;
                GPIO(temporaryGPIO);
            }
        }
    }
}



void WaitForSYNC_PU(void)
{
        unsigned char temp001 = 0;
        while(temp001 < 250)
        {
            if (SYNC_Line)
                temp001++;
            else
                temp001 = 0;
        }
}

void WriteEEPROMDefaults(void)
{
    GLOBAL_Mode_copy[0] = 0;          //Starting Pattern
    GLOBAL_Mode_copy[1] = 0;          //starting pattern
    GLOBAL_Mode_copy[2] = 0;          // starting pattern
    bGLOBAL_InPhase_copy[0] = true;
    bGLOBAL_InPhase_copy[1] = true;
    bGLOBAL_InPhase_copy[2] = true;
    //colorState[0] = 0;
    //colorState[1] = 0;
    //colorState[2] = 0;

    ReWriteEEPROM();
    EEpromNeverWritten_Flag = 1;
    
    //if (EEprom_Written_Flag != EEprom_Written_Flag_Value)
    //    while (1) {}        //lock program and special flash the status LED because could not write to EEprom
}

unsigned char setColorState(void)
{
    static unsigned char currentColorNumberOfChannels = 0;
    
        indexOfMode = 0;
    if (bGLOBAL_MODE1_PRESSED)
        indexOfMode = 1;
    if (bGLOBAL_MODE2_PRESSED)
        indexOfMode = 2;
    
    switch(colorState[indexOfMode])
        {
            case Chan1:
                currentColor = 0;
                break;
            case Chan2:
                currentColor = 1;
                break;
            case Chan3:
                currentColor = 2;
                break;
            case Chan4:
                currentColor = 3;
                break;
            case Chan1Chan2:
                switch(currentColorCounter)
                {
                    case 0:
                        currentColor = 0;
                        currentColorCounter = 1;
                        break;
                    case 1:
                        currentColor = 1;
                        currentColorCounter = 0;
                        break;
                    default:
                        break;
                }
                break;    
            case Chan1Chan3:
                switch(currentColorCounter)
                {
                    case 0:
                        currentColor = 0;
                        currentColorCounter = 1;
                        break;
                    case 1:
                        currentColor = 2;
                        currentColorCounter = 0;
                        break;
                    default:
                        break;
                }
                break; 
            case Chan1Chan4:        //Had to swap to match other products
                switch(currentColorCounter)
                {
                    case 0:
                        currentColor = 3;
                        currentColorCounter = 1;
                        break;
                    case 1:
                        currentColor = 0;
                        currentColorCounter = 0;
                        break;
                    default:
                        break;
                }
                break;    
            case Chan2Chan3:
                switch(currentColorCounter)
                {
                    case 0:
                        currentColor = 1;
                        currentColorCounter = 1;
                        break;
                    case 1:
                        currentColor = 2;
                        currentColorCounter = 0;
                        break;
                    default:
                        break;
                }
                break;  
            case Chan2Chan4:        //Had to swap to match other products
                switch(currentColorCounter)
                {
                    case 0:
                        currentColor = 3;
                        currentColorCounter = 1;
                        break;
                    case 1:
                        currentColor = 1;
                        currentColorCounter = 0;
                        break;
                    default:
                        break;
                }
                break;    
            case Chan3Chan4:        //Had to swap to match other products
                switch(currentColorCounter)
                {
                    case 0:
                        currentColor = 3;
                        currentColorCounter = 1;
                        break;
                    case 1:
                        currentColor = 2;
                        currentColorCounter = 0;
                        break;
                    default:
                        break;
                }
                break; 
            case Chan1Chan2Chan3:
                switch(currentColorCounter)
                {
                    case 0:
                        currentColor = 1;
                        currentColorCounter = 1;
                        break;
                    case 1:
                        currentColor = 2;
                        currentColorCounter = 2;
                        break;
                    case 2:
                        currentColor = 0;
                        currentColorCounter = 0;
                        break;    
                    default:
                        break;
                }
                break;    
            case Chan1Chan2Chan4:
                switch(currentColorCounter)
                {
                    case 0:
                        currentColor = 1;
                        currentColorCounter = 1;
                        break;
                    case 1:
                        currentColor = 3;
                        currentColorCounter = 2;
                        break;
                    case 2:
                        currentColor = 0;
                        currentColorCounter = 0;
                        break;    
                    default:
                        break;
                }
                break; 
            case Chan1Chan3Chan4:
                switch(currentColorCounter)
                {
                    case 0:
                        currentColor = 2;
                        currentColorCounter = 1;
                        break;
                    case 1:
                        currentColor = 3;
                        currentColorCounter = 2;
                        break;
                    case 2:
                        currentColor = 0;
                        currentColorCounter = 0;
                        break;    
                    default:
                        break;
                }
                break;                 
            case Chan2Chan3Chan4:
                switch(currentColorCounter)
                {
                    case 0:
                        currentColor = 2;
                        currentColorCounter = 1;
                        break;
                    case 1:
                        currentColor = 3;
                        currentColorCounter = 2;
                        break;
                    case 2:
                        currentColor = 1;
                        currentColorCounter = 0;
                        break;    
                    default:
                        break;
                }
                break;    
            case Chan1Chan2Chan3Chan4:
                switch(currentColorCounter)
                {
                    case 0:
                        currentColor = 0;
                        currentColorCounter = 1;
                        break;
                    case 1:
                        currentColor = 1;
                        currentColorCounter = 2;
                        break;
                    case 2:
                        currentColor = 2;
                        currentColorCounter = 3;
                        break; 
                    case 3:
                        currentColor = 3;
                        currentColorCounter = 0;
                        break;     
                    default:
                        break;
                }
                break;     
            default:
                break;
        }
    
    if((colorState[indexOfMode]>=0) && (colorState[indexOfMode]<4))
    {
        currentColorNumberOfChannels = 0;
    }
    else if(colorState[indexOfMode]>=4 && colorState[indexOfMode] <10)
    {
        currentColorNumberOfChannels = 1;
    }
    else if(colorState[indexOfMode]>=10 && colorState[indexOfMode] <14)
    {
        currentColorNumberOfChannels = 2;
    }
    else if(colorState[indexOfMode]==14)
    {
        currentColorNumberOfChannels = 3;
    }
    
    return currentColorNumberOfChannels;
    
}

void ReWriteEEPROM (void) //This function must not be called except when updated values are saved in the shadow RAM arrays : GLOBAL_TAKEDOWN_MODULES[] and GLOBAL_Mode_copy[]
{
    EEprom_Written_Flag = 0xFF; //clear the EEprom flag before any write to EEprom
    for (unsigned char i=0;i<MAX_MODES;i++)
    {
       // while(EEprom_mode[i] != GLOBAL_Mode_copy[i])
        {
            EEprom_mode[i] = GLOBAL_Mode_copy[i];
        }

        //while( EEprom_InPhase[i] != bGLOBAL_InPhase_copy[i])
        {
             EEprom_InPhase[i] = bGLOBAL_InPhase_copy[i];
        }
        
        //while(EEprom_ColorState[i] != colorState[i])
        {
            EEprom_ColorState[i] = colorState[i];
        }
    }
    EEprom_Written_Flag = EEprom_Written_Flag_Value;
}

void INC_EEPROM_MODE (void)
{
    unsigned char Temp_Mode_Data;
    unsigned char inputSync;
    Temp_Mode_Data = GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type];
    if (GLOBAL_Selected_Mode_Type == 2)
    {
        if (Temp_Mode_Data < (MAX_MODE_PATTERNS - 1))
        GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type]++;
        else GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type] = 0;
    }
    if (GLOBAL_Selected_Mode_Type == 1)
    {
        if (Temp_Mode_Data < (MAX_MODE_PATTERNS - 1))
        GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type]++;
        else GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type] = 0;
    }
    if (GLOBAL_Selected_Mode_Type == 0)
    {
        if (Temp_Mode_Data < (MAX_MODE_PATTERNS - 1))
        GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type]++;
        else GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type] = 0;
    }
    
    GLOBAL_changedModePattern = true;
    
    ReWriteEEPROM();
    currentColorCounter = 0;
    Update_ComboPattern_Index();
}

void Update_Input_Mode_Type(void)
{
    static unsigned char toggle = 0;
    GLOBAL_Selected_Mode_Type = 0;
    if (bGLOBAL_MODE1_PRESSED)
        GLOBAL_Selected_Mode_Type = 1;
    if (bGLOBAL_MODE2_PRESSED)
        GLOBAL_Selected_Mode_Type = 2;
    if (GLOBAL_Selected_Mode_Type_copy != GLOBAL_Selected_Mode_Type)
    {
        pwmStartUpCount = 0;
        Update_ComboPattern_Index();
        startUpProgram = 0;
    }
    bGLOBAL_InPhase = bGLOBAL_InPhase_copy[GLOBAL_Selected_Mode_Type];
    GLOBAL_Selected_Mode_Type_copy = GLOBAL_Selected_Mode_Type;
    
}

void resetColor(void)
{
    //if(bCOLOR_DETECT_PRESSED == true)
    {
        pwmStartUpCount = 0;
        {
            Update_Input_Mode_Type();
            colorResetCounter = 0;
            colorState[GLOBAL_Selected_Mode_Type] = 0;
            //bGiveControlToColorProgram = true;
            OUT1 = 0;
            OUT2 = 0;
            OUT3 = 0;
            OUT4 = 0;
            while(colorResetCounter<10000)
            {
                CLRWDT();
                OUT1 = 1;
                colorResetCounter++;
            }
            colorResetCounter = 0;
            ReWriteEEPROM();
            colorResetCounter = 0;
            CLRWDT();
            //bGiveControlToColorProgram = false;
        }
    }
}

void Increment_Color_State(void)
{    
    static unsigned char resetFlagColor = 0;
    
    if(GLOCAL_Program_Color == false && bCOLOR_DETECT_PRESSED == true)
    {
            TMR2IE = 0;
            GLOCAL_Program_Color = true;
            pwmStartUpCount = 0;
            bGiveControlToColorProgram = true;

            Update_Input_Mode_Type();
            colorState[GLOBAL_Selected_Mode_Type]++;
            if(colorState[GLOBAL_Selected_Mode_Type]>14)
            {
                colorState[GLOBAL_Selected_Mode_Type] = 0;
            }
            
            colorResetCounter = 0;
            ReWriteEEPROM();
            ReWriteEEPROM();
            colorResetCounter = 0;
            currentColorCounter = 0;
            
            GLOBAL_sub_patterns_column_index = 0;
            GLOBAL_Dummy_Counter = 0;
            //GLOBAL_sub_patterns_column_index = MAX_Sub_Patterns_Columns; //under this condition the detected sync pulse must be 20ms to 60ms wide
            GLOBAL_sub_patterns_timer =0;
            GLOBAL_combo_patterns_column_index = 0;
            GLOBAL_SYNC_PULSE_Counter = 0;
            bGLOBAL_END_OF_CYCLE_COND1 = false;
            bGLOBAL_END_OF_CYCLE_COND2 = false;
            
            
            //Update_ComboPattern_Index();
            colorResetCounter = 0;
            while(COLOR_DETECT)
            {
                CLRWDT();
                OUT1 = 0;
                OUT2 = 0;
                OUT3 = 0;
                OUT4 = 0;
                colorResetCounter++;
                if(colorResetCounter>50000)
                {
                    colorResetCounter = 0;
                    resetFlagColor = 1;
                    break;
                }
            }
            
            if(resetFlagColor == 1)
            {
                resetFlagColor = 0;
                resetColor();
            }
            colorResetCounter = 0;
            //bGiveControlToColorProgram = false;
            
            TMR2IE = 1;
    }
}

void Read_Mode_Input(void)
{
    static unsigned char inputSync = 0;
    static unsigned char previous_SYNC_Line = 0;
    
    
    
    
   if (MODE1)
   {   GLOBAL_MODE1_LOW_counter = 0;
       if (GLOBAL_MODE1_counter < General_Debounce_Max_Count) GLOBAL_MODE1_counter++;
       else bGLOBAL_MODE1_PRESSED = true;
   }   else {
       GLOBAL_MODE1_counter = 0;
       if (GLOBAL_MODE1_LOW_counter < General_Debounce_Max_Count) GLOBAL_MODE1_LOW_counter++;
       else bGLOBAL_MODE1_PRESSED = false;
   }
   if (MODE2)
   {   GLOBAL_MODE2_LOW_counter = 0;
       if (GLOBAL_MODE2_counter < General_Debounce_Max_Count) GLOBAL_MODE2_counter++;
       else bGLOBAL_MODE2_PRESSED = true;
   }   else {
       GLOBAL_MODE2_counter = 0;
       if (GLOBAL_MODE2_LOW_counter < General_Debounce_Max_Count) GLOBAL_MODE2_LOW_counter++;
       else bGLOBAL_MODE2_PRESSED = false;
   }
      if (COLOR_DETECT)
   {   COLOR_DETECT_LOW_counter = 0;
       if (COLOR_DETECT_counter < General_Debounce_Max_Count) COLOR_DETECT_counter++;
       else
       {
           //bCOLOR_DETECT_PRESSED = true;
       }
   }   else {
       COLOR_DETECT_counter = 0;
       if (COLOR_DETECT_LOW_counter < General_Debounce_Max_Count) COLOR_DETECT_LOW_counter++;
       else{ 
           GLOCAL_Program_Color = false;
           
           colorResetCounter++;
           if(colorResetCounter>100)
           {
                colorResetCounter = 0;
                bGiveControlToColorProgram = false;
           }
           
           //bCOLOR_DETECT_PRESSED = false;
       }
   } 
    
   if (!SYNC_Line) //For Pattern line PRESSED = true status is not asserted here
   {   GLOBAL_SYNC_Line_LOW_counter = 0;
       if (GLOBAL_SYNC_Line_counter < SYNC_Line_Debounce_Max_Count) 
        {
           GLOBAL_SYNC_Line_counter++;
            //else bGLOBAL_SYNC_Line_PRESSED = true;
        }
   }   
   else 
   {
       GLOBAL_SYNC_Line_counter = 0;
       if (GLOBAL_SYNC_Line_LOW_counter < General_Debounce_Low_Max_Count) 
       {
           GLOBAL_SYNC_Line_LOW_counter++;
       }
       else
       { 
           bGLOBAL_SYNC_Line_PRESSED = false;
       }
   }
    

    
}


void Update_ComboPattern_Index(void)
{
    GLOBAL_Selected_Mode_Number = GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type];
    GLOBAL_combo_patterns_index = GLOBAL_Selected_Mode_Number;
    pwmBool = false;
    
    if(GLOBAL_Selected_Mode_Number < 11)    //CH1 patterns
    {
        bGLOBAL_STEADY_ON = false;
        GLOBAL_combo_patterns_index = GLOBAL_Selected_Mode_Number;
        //bDualColor = false;
    }
    else if(GLOBAL_Selected_Mode_Number >= 11 && GLOBAL_Selected_Mode_Number < 14) //CH2 Steady on pattens
    {
        if(GLOBAL_Selected_Mode_Number == 12)
        {
            pwmBool = true;
            pwmStartUpCount = 0;
        }
        
        GLOBAL_Selected_Mode_Number = GLOBAL_Selected_Mode_Number;
        GLOBAL_combo_patterns_index = GLOBAL_Selected_Mode_Number;
        bGLOBAL_STEADY_ON = true;
        //bDualColor = false;
        
        if(GLOBAL_Selected_Mode_Number >= 11 && GLOBAL_Selected_Mode_Number < 14)
        {
            if(colorState[GLOBAL_Selected_Mode_Type]>3)
            {
                colorState[GLOBAL_Selected_Mode_Type] = 0;
            }
        }
        
    }
    
    GLOBAL_sub_patterns_column_index = MAX_Sub_Patterns_Columns;
    GLOBAL_sub_patterns_timer = 0;
    GLOBAL_Dummy_Counter2 = 0;

}

void readFromEEPROMBeforeSteadyOn(void)
{
    for (unsigned char i=0;i<MAX_MODES;i++)
    {
        GLOBAL_Mode_copy[i] = EEprom_mode[i];
        if(GLOBAL_Mode_copy[i] >= MAX_MODE_PATTERNS)
        {
            GLOBAL_Mode_copy[i] = 0;
        }
        //bGLOBAL_InPhase_copy[i] = EEprom_InPhase[i];
        //if(bGLOBAL_InPhase_copy[i] != true &&  bGLOBAL_InPhase_copy[i] != false)
        //{
        //    bGLOBAL_InPhase_copy[i] = false;
        //}
        colorState[i] = EEprom_ColorState[i];
        if(colorState[i] > Chan1Chan2Chan3Chan4)
        {
            colorState[i] = Chan1Chan2;
        }
    }  
}

void readFromEEPROM(void)
{
    for (unsigned char i=0;i<MAX_MODES;i++)
    {
        GLOBAL_Mode_copy[i] = EEprom_mode[i];
        if(GLOBAL_Mode_copy[i] >= MAX_MODE_PATTERNS)
        {
            GLOBAL_Mode_copy[i] = 0;
        }
        bGLOBAL_InPhase_copy[i] = EEprom_InPhase[i];
        if(bGLOBAL_InPhase_copy[i] != true &&  bGLOBAL_InPhase_copy[i] != false)
        {
            bGLOBAL_InPhase_copy[i] = false;
        }
        colorState[i] = EEprom_ColorState[i];
        if(colorState[i] > Chan1Chan2Chan3Chan4)
        {
            colorState[i] = 0;
        }
    }  
}

void Initial_Start (void)
{
    unsigned char read_data;
    read_data = EEpromNeverWritten_Flag;
    if (EEpromNeverWritten_Flag == 0)
        WriteEEPROMDefaults();
  
    readFromEEPROMBeforeSteadyOn();
    __delay_us(20);
    readFromEEPROMBeforeSteadyOn();
    __delay_us(550);
    
    enableOutputsToFlashPatterns = false;
    indexOfMode = 0;
    if (MODE1)
    {   
        indexOfMode = 1;
    }
    if (MODE2)
    {  
        indexOfMode = 2;
    }   
    
    if(GLOBAL_Mode_copy[indexOfMode] >= 11 && GLOBAL_Mode_copy[indexOfMode] < 14)
    {
        switch(colorState[indexOfMode])
        {
            case Chan1:
                OUT1 = (1);
                currentColor = 0;
                break;
            case Chan2:
                OUT2 = (1);
                currentColor = 1;
                break;
            case Chan3:
                OUT3 = (1);
                currentColor = 2;
                break;
            case Chan4:
                OUT4 = (1);
                currentColor = 3;
                break;
            default:
                OUT1 = (0);
                OUT2 = (0);
                OUT3 = (0);
                OUT4 = (0);
                break;
        }
    }

    readFromEEPROM();
    __delay_us(20);
    readFromEEPROM();
    __delay_us(550);
    
    Update_Input_Mode_Type();
    Update_ComboPattern_Index();
}
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    unsigned char tempvar1;
    unsigned char tester = 0;
    static unsigned long testerCounter = 0;
    
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    TRISA = ~(_TRISA_TRISA2_MASK + _TRISA_TRISA4_MASK); //PINS of PortA as output
    TRISC = ~(_TRISC_TRISC0_MASK + _TRISC_TRISC1_MASK + _TRISC_TRISC2_MASK); //PINS of PortA as output
    OUT1 = (0);
    OUT2 = (0);
    OUT3 = (0);
    OUT4 = (0);
    /* Initialize I/O and Peripherals for application */
    //
    InitApp();
    bGLOBAL_ENABLE_LEDS = false;
    OUT1 = (0);
    OUT2 = (0);
    OUT3 = (0);
    OUT4 = (0);
    Initial_Start(); //Verify and set the EEprom on initial start
    bGLOBAL_ENABLE_LEDS = false;
    
        //if(bGLOBAL_SYNC_Line_PRESSED  ==false){    
    //} 
    
    //startUpProgram = 0;
    while(1)
    {
        if (!bGLOBAL_IS_PROGRAMMING)
        {
            CLRWDT();
        }   
        //Update_Input_Mode_Type();
        Update_Input_Mode_Type();
        Increment_Color_State();
        /* TODO <INSERT USER APPLICATION CODE HERE> */
        
        if(bGiveControlToColorProgram == false){
        if ((GLOBAL_SYNC_Line_counter == SYNC_Line_Debounce_Max_Count) && (!bGLOBAL_SYNC_Line_PRESSED))
        {
            bGLOBAL_SYNC_Line_PRESSED = true;
            bGLOBAL_ENABLE_LEDS = false;
            SetOUTPUT();
        }        
        
        if (bGLOBAL_SYNC_Line_PRESSED && (!bGLOBAL_IS_PROGRAMMING))
        {
            GLOBAL_Dummy_Counter = 0;
            while ((!SYNC_Line) && (GLOBAL_Dummy_Counter < 199)) {}
            tempvar1 = GLOBAL_Dummy_Counter;
            CLRWDT();
                  
            if (tempvar1 > 198)
            {
                GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type] = 0;
                bGLOBAL_CHANGING_PATTERN = false;
                bGLOBAL_InPhase = !bGLOBAL_InPhase;
                bGLOBAL_InPhase_copy[GLOBAL_Selected_Mode_Type] = bGLOBAL_InPhase;
                bGLOBAL_IS_PROGRAMMING = true;               
                
                ReWriteEEPROM();
                ReWriteEEPROM();
                ReWriteEEPROM();
                SetOUTPUT();  
                colorResetCounter = 0;
                Update_ComboPattern_Index();
            }

            if (tempvar1 < 199)
            {
                GLOBAL_Dummy_Counter = 0;
                while (SYNC_Line && GLOBAL_Dummy_Counter < 2) {}   //this is added to check if the line was effectively released between 10ms to 20ms high
                if (GLOBAL_Dummy_Counter > 1)                      // and a pattern change command is the intended command to be sent on the line
                {
                    bGLOBAL_CHANGING_PATTERN = true;
                    INC_EEPROM_MODE();
                    GLOBAL_Dummy_Counter = 0;
                    bGLOBAL_IS_PROGRAMMING = true;
                    currentColorCounter = 0;
                }
            }
        }

        if (((GLOBAL_SYNC_Line_LOW_counter > 3) || (GLOBAL_Dummy_Counter > 4)) && (!bGLOBAL_CHANGING_PATTERN_Enforce) && bGLOBAL_CHANGING_PATTERN)
        {
            bGLOBAL_CHANGING_PATTERN_Enforce = true; // this condition will generate a pull down of the sync line
            GLOBAL_Dummy_Counter = 0;                  //after the Changing pattern condition is flagged to ensure all modules are changing pattern
            SYNC_CTRL = 1;                              //the line will stay high for at least 30 ms before pulling the sync line low
        }

        if (bGLOBAL_CHANGING_PATTERN_Enforce && (GLOBAL_Dummy_Counter > 12))
        {
            GLOBAL_Dummy_Counter = 0;                       //this condition will release the sync line after a duration of 130ms
            bGLOBAL_DISABLE_SYNC_Line_PRESSED = true;       //this condition will not be executed unless the changing pattern enforce flag is set
            SYNC_CTRL = 0;
        }

        if (bGLOBAL_DISABLE_SYNC_Line_PRESSED)
        {
            if (!SYNC_Line)                     //if sync line stays low after the MCU finishes sending the pattern change enforce signal for a 130ms
            {                                    //then the sync line counter will be always cleared not allowing the code to enter into another programming sequence
                GLOBAL_Dummy_Counter = 0;       //the sync line counter will be allowed back to increment until
                GLOBAL_SYNC_Line_counter = 0;   //the MCU sees the Sync line high for a continous duration of (General_Debounce_Low_Max_Count + 3)
            }
            if (GLOBAL_Dummy_Counter > General_Debounce_Low_Max_Count + 3)
               bGLOBAL_DISABLE_SYNC_Line_PRESSED = false;
        }
        
       if (!bGLOBAL_SYNC_Line_PRESSED)
        {
            bGLOBAL_ENABLE_LEDS = true;
            bGLOBAL_CHANGING_PATTERN = false;
            bGLOBAL_CHANGING_PATTERN_Enforce = false;
            bGLOBAL_IS_PROGRAMMING = false;
        }
    }
    }
}

unsigned char isComboPattern(void)
{
    static indexLocal = 0;
     indexLocal = 0;
    if (MODE1)
    {   
        indexLocal = 1;
    }
    if (MODE2)
    {  
        indexLocal = 2;
    }   
    //Checks Attack too
    if(GLOBAL_Mode_copy[indexLocal] == 2 || GLOBAL_Mode_copy[indexLocal] == 5 || GLOBAL_Mode_copy[indexLocal] == 8 || GLOBAL_Mode_copy[indexLocal] == 9 || GLOBAL_Mode_copy[indexLocal] == 10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
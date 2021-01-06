/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define OUT1            (PORTCbits.RC2) //
#define OUT2            (PORTCbits.RC1) //
#define OUT3            (PORTCbits.RC0)
#define OUT4            (PORTAbits.RA2)
#define SYNC_CTRL       (PORTAbits.RA4) //

#define MODE1           (PORTCbits.RC5) //for F6-S
#define MODE2           (PORTCbits.RC4) // for F6-S and HAW
#define COLOR_DETECT    (PORTCbits.RC3) // for F6-S and HAW
#define SYNC_Line       (PORTAbits.RA5) //

#define EEprom_Written_Flag_Value 0xA6
#define OFF 0
#define OFFF 0
#define CH1 0x01
#define CH2 0x02
#define CH3 0x04
#define CH4 0x08

#define CH1_SYNC 0x21
#define CH2_SYNC 0x22
#define CH3_SYNC 0x24
#define CH4_SYNC 0x28

#define DISABLED 0
#define BOTH 0x0F
#define MAX_Sub_Patterns     19
#define MAX_Sub_Patterns_Columns        7
#define MAX_MODE_PATTERNS               14                    //
#define MAX_MODES                       3
#define MAX_Combo_Patterns              (MAX_MODE_PATTERNS)
#define MAX_Combo_Patterns_Columns      35
#define General_Debounce_Max_Count      4
#define General_Debounce_Low_Max_Count  7
#define SYNC_Line_Debounce_Max_Count    9+0              //added from 25 to 9

    //CH1               0
    //CH2               1
    //CH3               2
    //CH4               3
    //CH1+CH2           4
    //CH1+CH3           5
    //CH1+CH4           6
    //CH2+CH3           7
    //CH2+CH4           8
    //CH3+CH4           9
    //CH1+CH2+CH3       10
    //CH1+CH2+CH4       11
    //CH1+CH3+CH4       12
    //CH2+CH3+CH4       13
    //CH1+CH2+CH3+CH4   14

#define Chan1 0
#define Chan2 1
#define Chan3 2
#define Chan4 3
#define Chan1Chan2 4
#define Chan1Chan3 5
#define Chan1Chan4 6
#define Chan2Chan3 7
#define Chan2Chan4 8
#define Chan3Chan4 9
#define Chan1Chan2Chan3 10
#define Chan1Chan2Chan4 11
#define Chan1Chan3Chan4 12
#define Chan2Chan3Chan4 13
#define Chan1Chan2Chan3Chan4 14

/* TODO Application specific user parameters used in user.c may go here */
extern volatile unsigned char GLOBAL_sub_patterns_index;         //used to communicate the selected sub pattern
extern volatile unsigned char GLOBAL_sub_patterns_index_copy;
extern volatile unsigned char GLOBAL_sub_patterns_column_index;  //used to move inside the selected sub pattern
extern volatile unsigned char GLOBAL_combo_patterns_index;       //used to communicate the selected combo pattern
extern volatile unsigned char GLOBAL_combo_patterns_index_copy;
extern volatile unsigned char GLOBAL_combo_patterns_column_index;//used to move inside the selected combo pattern
extern volatile unsigned char GLOBAL_sub_patterns_timer;       //used to update the timer counter
extern volatile unsigned char GLOBAL_combo_patterns_counter;
extern volatile unsigned char GLOBAL_Selected_Mode_Number;
extern volatile unsigned char GLOBAL_Selected_Mode_Type;
extern volatile unsigned char GLOBAL_Dummy_Counter;
extern volatile unsigned char GLOBAL_Dummy_Counter2;
extern volatile unsigned char GLOBAL_MODE1_counter;
extern volatile unsigned char GLOBAL_SYNC_Line_counter;
extern volatile unsigned char GLOBAL_MODE2_counter;
extern volatile unsigned char GLOBAL_TEMP_REG;
extern volatile unsigned char GLOBAL_MODE1_LOW_counter;
extern volatile unsigned char GLOBAL_SYNC_Line_LOW_counter;
extern volatile unsigned char GLOBAL_MODE2_LOW_counter;
extern volatile unsigned char GLOBAL_SYNC_PULSE_Counter;
extern volatile unsigned char GLOBAL_CHANNELS_EN;

extern volatile bool bGLOBAL_CHANGING_PATTERN;
extern volatile bool bGLOBAL_SYNC_SENT;
extern volatile bool bGLOBAL_END_OF_CYCLE_COND1;
extern volatile bool bGLOBAL_END_OF_CYCLE_COND2;
extern volatile bool bGLOBAL_IS_PROGRAMMING;
extern volatile bool bGLOBAL_InPhase;
extern volatile bool bGLOBAL_ENABLE_LEDS;
extern volatile bool bGLOBAL_SYNC_Line_PRESSED;
extern volatile bool bGLOBAL_OUTPUT_BUFFER_CHANGED;
extern volatile bool bGLOBAL_STEADY_ON ;

extern volatile unsigned char OUTPUT_BUFFER;
extern volatile unsigned char OUTPUT_BUFFER_COPY;
extern const unsigned char ROM_Sub_Patterns [MAX_Sub_Patterns][MAX_Sub_Patterns_Columns];
extern const unsigned char ROM_Sub_Patterns_Time [MAX_Sub_Patterns][MAX_Sub_Patterns_Columns];
extern const unsigned char ROM_COMBO_Patterns_TwoFour [MAX_Combo_Patterns][MAX_Combo_Patterns_Columns];
extern const unsigned char ROM_COMBO_Patterns_Three [MAX_Combo_Patterns][MAX_Combo_Patterns_Columns];

extern const unsigned char ROM_COMBO_Patterns_TwoFourSlave [MAX_Combo_Patterns][MAX_Combo_Patterns_Columns];
extern const unsigned char ROM_COMBO_Patterns_ThreeSlave [MAX_Combo_Patterns][MAX_Combo_Patterns_Columns];

extern volatile unsigned char channelToBeDisplayed;
extern volatile bool bDualColor;
extern volatile unsigned char GLOBAL_CHANNELS_EN_DUAL;
extern volatile unsigned char currentColorCounter;
extern volatile unsigned char startUpProgram;

extern volatile unsigned bool pwmBool;
extern volatile unsigned char pwmStartUpCount;

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
void SetOUTPUT(void);
void Read_Mode_Input(void);
void Update_ComboPattern_Index(void);
void ReWriteEEPROM(void);
void WaitForSYNC_PU(void);
unsigned char setColorState(void);
inline void GPIO(unsigned char i);
unsigned char isComboPattern(void);
void SetMasterSlaveOutput(void);

#define START_UP_TIME 0
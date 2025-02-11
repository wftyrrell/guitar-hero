/************** ECE2049 Lab #2 ******************/
/**************   September 28 2022   ******************/
/***************************************************/

#include <msp430.h>


#include "peripherals.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

// Declare globals variables
long unsigned int timer_cnt = 0;
long unsigned int leap_cnt = 0;

// Function Prototypes
void runtimerA2(void);

void swDelay(char numLoops);

void lightUpLedBuzz(int arrayVal, int delay);

void outKeyLcd(int key);

void buzzerOn(int pwmVal);

void buzzerOff(void);

int createRandomNum(void);

unsigned char getKeys(void);

void configureButtons(void);

char buttonsPressed(void);

void lightUserLED(char inbits);

void configLpadLEDs(void);

void turnOffUserLED(char inbits);


struct Note{
    int note; // Note Frequencies
    int duration;  //duration of note
    char buttonAssoc;//button associated with each note
    int restFromPrevious; // the rest time between previous and present note that is played
    char ledColor; // led color for each note
};

void runtimerA2(void){

    TA2CTL = TASSEL_1 + MC_1 + ID_0;
    TA2CCR0 = 163;
    TA2CCTL0 = CCIE;

}


#pragma vector=TIMER2_A0_VECTOR
__interrupt void Timer_A2_ISR(void) {

    if(leap_cnt < 1024) {

        timer_cnt++;
        leap_cnt++;
    } else {

        timer_cnt+=2;
        leap_cnt = 0;
    }

}



void main(void)
{

    unsigned char currKey=0;
    int delayTime=(BIT5|BIT2);
    int state=0, counter=0, index=0, randomNum=0, num=0;
    struct Note notes[59];
    long unsigned int timer_on=0;

    // For Case 11
    int error = 0;
    int isCorrect = false;
    char button = '0';


    //For buzzerOn()

       //Note Number 1
       notes[0].note = 262;
       notes[0].duration = 300;
       notes[0].buttonAssoc = BIT2;
       notes[0].restFromPrevious = 0;
       notes[0].ledColor = BIT1;


       //Note Number 2
       notes[1].note = 262;
       notes[1].duration = 50;
       notes[1].buttonAssoc = BIT2;
       notes[1].restFromPrevious = 300;
       notes[1].ledColor = BIT1;


       //Note Number 3
       notes[2].note = 294;
       notes[2].duration = 50;
       notes[2].buttonAssoc = BIT1;
       notes[2].restFromPrevious = 0;
       notes[2].ledColor = BIT2;

       //Note Number 4
       notes[3].note = 330;
       notes[3].duration = 50;
       notes[3].buttonAssoc = BIT1;
       notes[3].restFromPrevious = 0;
       notes[3].ledColor = BIT2;

       //Note Number 5
       notes[4].note = 349;
       notes[4].duration = 400;
       notes[4].buttonAssoc = BIT0;
       notes[4].restFromPrevious = 0;
       notes[4].ledColor = BIT3;

       //Note Number 6
       notes[5].note = 349;
       notes[5].duration = 50;
       notes[5].buttonAssoc = BIT0;
       notes[5].restFromPrevious = 300;
       notes[5].ledColor = BIT3;

       //Note Number 7
       notes[6].note = 330;
       notes[6].duration = 50;
       notes[6].buttonAssoc = BIT1;
       notes[6].restFromPrevious = 0;
       notes[6].ledColor = BIT2;

       //Note Number 8
       notes[7].note = 294;
       notes[7].duration = 50;
       notes[7].buttonAssoc = BIT1;
       notes[7].restFromPrevious = 0;
       notes[7].ledColor = BIT2;

       //Note Number 9
       notes[8].note = 262;
       notes[8].duration = 400;
       notes[8].buttonAssoc = BIT2;
       notes[8].restFromPrevious = 0;
       notes[8].ledColor = BIT1;

       //Note Number 10
       notes[9].note = 262;
       notes[9].duration = 50;
       notes[9].buttonAssoc = BIT2;
       notes[9].restFromPrevious = 300;
       notes[9].ledColor = BIT1;

       //Note Number 11
       notes[10].note = 294;
       notes[10].duration = 50;
       notes[10].buttonAssoc = BIT1;
       notes[10].restFromPrevious = 0;
       notes[10].ledColor = BIT2;

       //Note Number 12
       notes[11].note = 330;
       notes[11].duration = 50;
       notes[11].buttonAssoc = BIT1;
       notes[11].restFromPrevious = 0;
       notes[11].ledColor = BIT2;

       //Note Number 13
       notes[12].note = 330;
       notes[12].duration = 425;
       notes[12].buttonAssoc = BIT1;
       notes[12].restFromPrevious = 0;
       notes[12].ledColor = BIT2;

       //Note Number 14
       notes[13].note = 294;
       notes[13].duration = 400;
       notes[13].buttonAssoc = BIT1;
       notes[13].restFromPrevious = 0;
       notes[13].ledColor = BIT2;

       //Note Number 15
       notes[14].note = 262;
       notes[14].duration = 300;
       notes[14].buttonAssoc = BIT2;
       notes[14].restFromPrevious = 300;
       notes[14].ledColor = BIT1;

       //Note Number 16
       notes[15].note = 262;
       notes[15].duration = 50;
       notes[15].buttonAssoc = BIT2;
       notes[15].restFromPrevious = 300;
       notes[15].ledColor = BIT1;

       //Note Number 17
       notes[16].note = 294;
       notes[16].duration = 50;
       notes[16].buttonAssoc = BIT1;
       notes[16].restFromPrevious = 0;
       notes[16].ledColor = BIT2;

       //Note Number 18
       notes[17].note = 330;
       notes[17].duration = 50;
       notes[17].buttonAssoc = BIT1;
       notes[17].restFromPrevious = 0;
       notes[17].ledColor = BIT2;

       //Note Number 19
       notes[18].note = 349;
       notes[18].duration = 400;
       notes[18].buttonAssoc = BIT0;
       notes[18].restFromPrevious = 0;
       notes[18].ledColor = BIT3;

       //Note Number 20
       notes[19].note = 349;
       notes[19].duration = 50;
       notes[19].buttonAssoc = BIT0;
       notes[19].restFromPrevious = 300;
       notes[19].ledColor = BIT3;

       //Note Number 21
       notes[20].note = 330;
       notes[20].duration = 50;
       notes[20].buttonAssoc = BIT1;
       notes[20].restFromPrevious = 0;
       notes[20].ledColor = BIT2;

       //Note Number 22
       notes[21].note = 294;
       notes[21].duration = 50;
       notes[21].buttonAssoc = BIT1;
       notes[21].restFromPrevious = 0;
       notes[21].ledColor = BIT2;

       //Note Number 23
       notes[22].note = 262;
       notes[22].duration = 400;
       notes[22].buttonAssoc = BIT2;
       notes[22].restFromPrevious = 0;
       notes[22].ledColor = BIT1;

       //Note Number 24
       notes[23].note = 262;
       notes[23].duration = 50;
       notes[23].buttonAssoc = BIT2;
       notes[23].restFromPrevious = 300;
       notes[23].ledColor = BIT1;

       //Note Number 25
       notes[24].note = 294;
       notes[24].duration = 50;
       notes[24].buttonAssoc = BIT1;
       notes[24].restFromPrevious = 0;
       notes[24].ledColor = BIT2;

       //Note Number 26
       notes[25].note = 330;
       notes[25].duration = 50;
       notes[25].buttonAssoc = BIT1;
       notes[25].restFromPrevious = 0;
       notes[25].ledColor = BIT2;

       //Note Number 27
       notes[26].note = 247;
       notes[26].duration = 500;
       notes[26].buttonAssoc = BIT2;
       notes[26].restFromPrevious = 0;
       notes[26].ledColor = BIT1;

       //Note Number 28
       notes[27].note = 262;
       notes[27].duration = 400;
       notes[27].buttonAssoc = BIT2;
       notes[27].restFromPrevious = 0;
       notes[27].ledColor = BIT1;

       //Note Number 29
       notes[28].note = 330;
       notes[28].duration = 50;
       notes[28].buttonAssoc = BIT1;
       notes[28].restFromPrevious = 0;
       notes[28].ledColor = BIT2;

       //Note Number 30
       notes[29].note = 330;
       notes[29].duration = 50;
       notes[29].buttonAssoc = BIT1;
       notes[29].restFromPrevious = 0;
       notes[29].ledColor = BIT2;

       //Note Number 31
       notes[30].note = 294;
       notes[30].duration = 50;
       notes[30].buttonAssoc = BIT1;
       notes[30].restFromPrevious = 0;
       notes[30].ledColor = BIT2;

       //Note Number 32
       notes[31].note = 262;
       notes[31].duration = 300;
       notes[31].buttonAssoc = BIT2;
       notes[31].restFromPrevious = 0;
       notes[31].ledColor = BIT1;

       //Note Number 33
       notes[32].note = 262;
       notes[32].duration = 50;
       notes[32].buttonAssoc = BIT2;
       notes[32].restFromPrevious = 400;
       notes[32].ledColor = BIT1;

       //Note Number 34
       notes[33].note = 247;
       notes[33].duration = 50;
       notes[33].buttonAssoc = BIT2;
       notes[33].restFromPrevious = 0;
       notes[33].ledColor = BIT1;

       //Note Number 35
       notes[34].note = 220;
       notes[34].duration = 50;
       notes[34].buttonAssoc = BIT3;
       notes[34].restFromPrevious = 0;
       notes[34].ledColor = BIT0;

       //Note Number 36
       notes[35].note = 196;
       notes[35].duration = 300;
       notes[35].buttonAssoc = BIT3;
       notes[35].restFromPrevious = 0;
       notes[35].ledColor = BIT0;

       //Note Number 37
       notes[36].note = 262;
       notes[36].duration = 50;
       notes[36].buttonAssoc = BIT2;
       notes[36].restFromPrevious = 400;
       notes[36].ledColor = BIT1;

       //Note Number 38
       notes[37].note = 294;
       notes[37].duration = 50;
       notes[37].buttonAssoc = BIT1;
       notes[37].restFromPrevious = 0;
       notes[37].ledColor = BIT2;

       //Note Number 39
       notes[38].note = 330;
       notes[38].duration = 50;
       notes[38].buttonAssoc = BIT1;
       notes[38].restFromPrevious = 0;
       notes[38].ledColor = BIT2;

       //Note Number 40
       notes[39].note = 330;
       notes[39].duration = 300;
       notes[39].buttonAssoc = BIT1;
       notes[39].restFromPrevious = 0;
       notes[39].ledColor = BIT2;

       //Note Number 41
       notes[40].note = 294;
       notes[40].duration = 50;
       notes[40].buttonAssoc = BIT1;
       notes[40].restFromPrevious = 50;
       notes[40].ledColor = BIT2;

       //Note Number 42
       notes[41].note = 294;
       notes[41].duration = 300;
       notes[41].buttonAssoc = BIT1;
       notes[41].restFromPrevious = 0;
       notes[41].ledColor = BIT2;

       //Note Number 43
       notes[42].note = 262;
       notes[42].duration = 300;
       notes[42].buttonAssoc = BIT2;
       notes[42].restFromPrevious = 400;
       notes[42].ledColor = BIT1;

       //Note Number 44
       notes[43].note = 330;
       notes[43].duration = 50;
       notes[43].buttonAssoc = BIT1;
       notes[43].restFromPrevious = 300;
       notes[43].ledColor = BIT2;

       //Note Number 45
       notes[44].note = 330;
       notes[44].duration = 50;
       notes[44].buttonAssoc = BIT1;
       notes[44].restFromPrevious = 0;
       notes[44].ledColor = BIT2;

       //Note Number 46
       notes[45].note = 294;
       notes[45].duration = 50;
       notes[45].buttonAssoc = BIT1;
       notes[45].restFromPrevious = 0;
       notes[45].ledColor = BIT2;

       //Note Number 47
       notes[46].note = 262;
       notes[46].duration = 300;
       notes[46].buttonAssoc = BIT2;
       notes[46].restFromPrevious = 0;
       notes[46].ledColor = BIT1;

       //Note Number 48
       notes[47].note = 262;
       notes[47].duration = 50;
       notes[47].buttonAssoc = BIT2;
       notes[47].restFromPrevious = 400;
       notes[47].ledColor = BIT1;

       //Note Number 49
       notes[48].note = 262;
       notes[48].duration = 300;
       notes[48].buttonAssoc = BIT2;
       notes[48].restFromPrevious = 0;
       notes[48].ledColor = BIT1;

       //Note Number 50
       notes[49].note = 247;
       notes[49].duration = 50;
       notes[49].buttonAssoc = BIT2;
       notes[49].restFromPrevious = 0;
       notes[49].ledColor = BIT1;

       //Note Number 51
       notes[50].note = 220;
       notes[50].duration = 50;
       notes[50].buttonAssoc = BIT3;
       notes[50].restFromPrevious = 0;
       notes[50].ledColor = BIT0;

       //Note Number 52
       notes[51].note = 196;
       notes[51].duration = 300;
       notes[51].buttonAssoc = BIT3;
       notes[51].restFromPrevious = 0;
       notes[51].ledColor = BIT0;

       //Note Number 53
       notes[52].note = 330;
       notes[52].duration = 50;
       notes[52].buttonAssoc = BIT1;
       notes[52].restFromPrevious = 300;
       notes[52].ledColor = BIT2;

       //Note Number 54
       notes[53].note = 330;
       notes[53].duration = 50;
       notes[53].buttonAssoc = BIT1;
       notes[53].restFromPrevious = 0;
       notes[53].ledColor = BIT2;

       //Note Number 55
       notes[54].note = 294;
       notes[54].duration = 50;
       notes[54].buttonAssoc = BIT1;
       notes[54].restFromPrevious = 0;
       notes[54].ledColor = BIT2;

       //Note Number 56
       notes[55].note = 262;
       notes[55].duration = 300;
       notes[55].buttonAssoc = BIT2;
       notes[55].restFromPrevious = 0;
       notes[55].ledColor = BIT1;

       //Note Number 57
       notes[56].note = 247;
       notes[56].duration = 500;
       notes[56].buttonAssoc = BIT2;
       notes[56].restFromPrevious = 0;
       notes[56].ledColor = BIT1;

       //Note Number 58
       notes[57].note = 262;
       notes[57].duration = 400;
       notes[57].buttonAssoc = BIT2;
       notes[57].restFromPrevious = 0;
       notes[57].ledColor = BIT1;

       //Note Number 59
       notes[58].note = 392;
       notes[58].duration = 400;
       notes[58].buttonAssoc = BIT0;
       notes[58].restFromPrevious = 0;
       notes[58].ledColor = BIT3;





    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer.



    initLeds();
    configLpadLEDs();
    configureButtons();
    configDisplay();
    configKeypad();

    Graphics_clearDisplay(&g_sContext); // Clear the display


    srand(time(0));


    _BIS_SR(GIE); // Global Interrupt enable
    runtimerA2();

    while (1)    // Forever loop
    {





        // state machine for "MSP430 Hero" game
        switch (state) {

            case 0:
            {
                state=0;
                counter=0;


                Graphics_drawStringCentered(&g_sContext, "MSP430", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT); // Display welcome screen
                Graphics_drawStringCentered(&g_sContext, "HERO", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT); // Display welcome screen
                Graphics_drawStringCentered(&g_sContext, "Press * to Start", AUTO_STRING_LENGTH, 48, 55, TRANSPARENT_TEXT); // Display welcome screen
                Graphics_flushBuffer(&g_sContext);
                currKey = getKey();

                if (currKey == '*') {

                    state = 1;
                    counter = 1;

                    Graphics_clearDisplay(&g_sContext); // Clear the display
                    timer_on = timer_cnt;
                    while (timer_cnt < (timer_on + 200)) {

                        Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                        Graphics_flushBuffer(&g_sContext);
                        lightUserLED(1);
                    }

                    Graphics_clearDisplay(&g_sContext); // Clear the display
                    turnOffUserLED(1);
                    timer_on = timer_cnt;
                    while (timer_cnt < (timer_on + 200)) {

                        Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                        Graphics_flushBuffer(&g_sContext);
                        lightUserLED(2);
                    }

                    Graphics_clearDisplay(&g_sContext); // Clear the display
                    turnOffUserLED(2);
                    timer_on = timer_cnt;
                    while (timer_cnt < (timer_on + 200)) {

                        Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                        Graphics_flushBuffer(&g_sContext);
                        lightUserLED(1);
                    }

                    Graphics_clearDisplay(&g_sContext); // Clear the display
                    turnOffUserLED(1);
                    timer_on = timer_cnt;
                    while (timer_cnt < (timer_on + 200)) {

                        Graphics_drawStringCentered(&g_sContext, "GO", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                        Graphics_flushBuffer(&g_sContext);
                        lightUserLED(3);
                    }
                    turnOffUserLED(3);

                }

                break;
            }
            case 1:
            {
                Graphics_clearDisplay(&g_sContext); // Clear the display


                int i;
                for (i=0; i<59; i++) {


                    // case where user wants to restart the game
                    currKey = getKey();
                    if((currKey == '#') && (counter == 1)) {
                        state=0;
                        counter=0;
                        index=0;
                        currKey=0;
                        randomNum=0;
                        delayTime=36;
                        num=0;

                        Graphics_clearDisplay(&g_sContext); // Clear the display
                        break;
                    }


                    isCorrect = false;
                    timer_on = timer_cnt;

                    while (timer_cnt < (timer_on + notes[i].duration)) { // notes[i].duration


                        buzzerOn(notes[i].note);
                        setLeds(notes[i].ledColor);
                        button = buttonsPressed();


                        if(button == notes[i].buttonAssoc){
                            isCorrect = true;
                        }
                    }

                    buzzerOff();
                    // Turn off peripheral LEDs
                    setLeds(0);
                    timer_on = timer_cnt;
                    while (timer_cnt < timer_on + 50) {

                    }


                    if (!isCorrect) {
                        error+=1;
                    }

                    if (error==3) { // If user makes 3 mistakes they lose!
                        state=3; // "Game Over" state
                        break;
                    }

                }

                if (state!=3){
                    state = 4; // "You WIN" state
                }


                break;
            }

            case 2: // Check Player Input
            {
                int check=0;
                for(check=0; check<index; check++){
                        currKey = getKeys();
                        num = currKey - '0';
                        lightUpLedBuzz(num, BIT3);
                        outKeyLcd(num);


                  }
                swDelay(BIT3);

                if(state == 3) break;

                state = 1;
                break;
            }
            case 3: {
                Graphics_clearDisplay(&g_sContext); // Clear the display
                Graphics_drawStringCentered(&g_sContext, "Game Over!", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);

                int k=0;
                int i=16;
                while (i != 0){
                    k = (k % 4) + 1;
                    lightUpLedBuzz(k, BIT2);
                    i--;
                }

                timer_on = timer_cnt;
                while (timer_cnt < (timer_on + 600)){

                    // Keep displaying "Game Over" screen for 3 seconds
                }

                state = 0;
                Graphics_clearDisplay(&g_sContext); // Clear the display
                break;
            }
            case 4: {
                Graphics_clearDisplay(&g_sContext); // Clear the display
                Graphics_drawStringCentered(&g_sContext, "You Won!", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);

                int k=0;
                int i=0;
                while (i != 16){
                    k = (k % 4) + 1;
                    lightUpLedBuzz(k, BIT2);
                    i++;
                }

                timer_on = timer_cnt;
                while (timer_cnt < (timer_on + 600)){

                       // Keep displaying "You Won" screen for 3 seconds
                }


                state = 0;
                Graphics_clearDisplay(&g_sContext); // Clear the display
                break;
            }
        }



    }  // end while (1)
}


void swDelay(char numLoops)
{

    volatile unsigned int i,j;  // volatile to prevent removal in optimization
                                // by compiler. Functionally this is useless code

    for (j=0; j<numLoops; j++)
    {
        i = 3000 ;                  // SW Delay
        while (i > 0)
           i--;
    }
}


void lightUpLedBuzz(int arrayVal, int delay) // Have a delay of 0 in user input and a "delayTime" delay when outputting the next sequence
{
    switch(arrayVal){

        case 1:
            setLeds(BIT3);
            buzzerOn(250);
            swDelay(delay);
            setLeds(0);
            buzzerOff();
            swDelay(delay);
            break;
        case 2:
            setLeds(BIT2);
            buzzerOn(350);
            swDelay(delay);
            setLeds(0);
            buzzerOff();
            swDelay(delay);
            break;
        case 3:
            setLeds(BIT1);
            buzzerOn(450);
            swDelay(delay);
            setLeds(0);
            buzzerOff();
            swDelay(delay);
            break;
        case 4:
            setLeds(BIT0);
            buzzerOn(550);
            swDelay(delay);
            setLeds(0);
            buzzerOff();
            swDelay(delay);
            break;
    }
}



void outKeyLcd(int key)
{
    switch(key){

        case 1:
            Graphics_clearDisplay(&g_sContext); // Clear the display
            Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 20, 48, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
            break;

        case 2:
                Graphics_clearDisplay(&g_sContext); // Clear the display
                Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 40, 48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                break;
        case 3:
                Graphics_clearDisplay(&g_sContext); // Clear the display
                Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 60, 48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                break;
        case 4:
                Graphics_clearDisplay(&g_sContext); // Clear the display
                Graphics_drawStringCentered(&g_sContext, "4", AUTO_STRING_LENGTH, 80, 48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                break;
    }
}


void buzzerOn(int noteFreq)
{
    unsigned int ACLK = 32768;

    // Initialize PWM output on P3.5, which corresponds to TB0.5
    P3SEL |= BIT5; // Select peripheral output mode for P3.5
    P3DIR |= BIT5;

    TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
    TB0CTL  &= ~TBIE;                       // Explicitly Disable timer interrupts for safety

    // Now configure the timer period, which controls the PWM period
    int inputVal = (ACLK/noteFreq);
    TB0CCR0   = inputVal;                    // Set the PWM period in ACLK ticks
    TB0CCTL0 &= ~CCIE;                  // Disable timer interrupts

    // Configure CC register 5, which is connected to our PWM pin TB0.5
    TB0CCTL5  = OUTMOD_7;                   // Set/reset mode for PWM
    TB0CCTL5 &= ~CCIE;                      // Disable capture/compare interrupts
    TB0CCR5   = TB0CCR0/2;                  // Configure a 50% duty cycle
}

/*
 * Disable the buzzer on P7.5
 */
void buzzerOff(void)
{
    // Disable both capture/compare periods
    TB0CCTL0 = 0;
    TB0CCTL5 = 0;
}

//Creates random number

int createRandomNum(void)
{
    int num = (rand() % 4) + 1;
    return num;
}





unsigned char getKeys(void)
{
    // Returns ASCII value of key pressed from keypad or 0.



    unsigned char ret_val = 0;

    while (ret_val == 0) {


            P1OUT &= ~BIT5;
            P2OUT |= (BIT5|BIT4);
            // Now check value from each rows
            if ((P4IN & BIT3)==0)
                ret_val = '1';
            if ((P1IN & BIT2)==0)
                ret_val = '4';
            if ((P1IN & BIT3)==0)
                ret_val = '7';
            if ((P1IN & BIT4)==0)
                ret_val = '*';
            P1OUT |= BIT5;


            P2OUT &= ~BIT4;
            // Now check value from each rows
            if ((P4IN & BIT3)==0)
                ret_val = '2';
            if ((P1IN & BIT2)==0)
                ret_val = '5';
            if ((P1IN & BIT3)==0)
                ret_val = '8';
            if ((P1IN & BIT4)==0)
                ret_val = '0';
            P2OUT |= BIT4;


            P2OUT &= ~BIT5;
            // Now check value from each rows
            if ((P4IN & BIT3)==0)
                ret_val = '3';
            if ((P1IN & BIT2)==0)
                ret_val = '6';
            if ((P1IN & BIT3)==0)
                ret_val = '9';
            if ((P1IN & BIT4)==0)
                ret_val = '#';
            P2OUT |= BIT5;

    }

    return(ret_val);
}


void configureButtons()
{
    P7SEL &= ~(BIT0);
    P3SEL &= ~(BIT6);
    P2SEL &= ~(BIT2);
    P7SEL &= ~(BIT4);

    P7DIR &= ~(BIT0);
    P3DIR &= ~(BIT6);
    P2DIR &= ~(BIT2);
    P7DIR &= ~(BIT4);

    P7REN |= (BIT0);
    P3REN |= (BIT6);
    P2REN |= (BIT2);
    P7REN |= (BIT4);

    P7OUT |= (BIT0);
    P3OUT |= (BIT6);
    P2OUT |= (BIT2);
    P7OUT |= (BIT4);

}

char buttonsPressed(){
    char holderS1 = 0x00;
    char holderS2 = 0x00;
    char holderS3 = 0x00;
    char holderS4 = 0x00;
    char outBits = 0x00;

    holderS1 |= (P7IN & BIT0);

    holderS2 |= (P3IN & BIT6);
    holderS2 = holderS2 >> 5;

    holderS3 |= (P2IN & BIT2);

    holderS4 |= (P7IN & BIT4);
    holderS4 = holderS4 >> 1;


    outBits = holderS1 | holderS2 | holderS3 | holderS4;


    switch (outBits) {
       case 0: {
           return 15;
           break;
       }
       case 1: {
           return 14;
           break;
       }
       case 2: {
          return 13;
          break;
       }
       case 3: {
           return 12;
         break;
       }

       case 4:{
          return 11;
          break;
       }
       case 5:{
          return 10;
          break;
       }
       case 6:{
          return 9;
          break;
       }
       case 7:{
          return 8;
          break;
       }
       case 8:{
          return 7;
          break;
       }
       case 9:{
          return 6;
          break;
       }
       case 10:{
          return 5;
          break;
       }
       case 11:{
          return 4;
          break;
       }
       case 12:{
          return 3;
          break;
       }
       case 13:{
          return 2;
          break;
       }
       case 14:{
          return 1;
          break;
       }
       case 15:{
          return 0;
          break;
       }

    }

    return outBits;
}

void lightUserLED(char inbits){

    if ((inbits & BIT0) == 0x01){
        P1OUT |= BIT0;
    }
    if ((inbits & BIT1) == 0x02){
        P4OUT |= BIT7;
    }


}

void turnOffUserLED(char inbits){

    if ((inbits & BIT0) == 0x01){
         P1OUT &= ~BIT0;
     }

     if ((inbits & BIT1) == 0x02){
         P4OUT &= ~BIT7;
     }

}


void configLpadLEDs(){

    P4SEL &= ~(BIT7);
    P1SEL &= ~(BIT0);

    P4DIR |= BIT7;
    P1DIR |= BIT0;

    // Turn Launchpad LEDs OFF
    P1OUT &= ~BIT0;
    P4OUT &= ~BIT7;


}

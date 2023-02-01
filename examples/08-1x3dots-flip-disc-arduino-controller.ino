/*----------------------------------------------------------------------------------*
 * Flip-disc display controller & 1 x 3x1 dot display                               *
 * Example connection diagram: https://bit.ly/AC1-1x3x1DOTS                         *
 *                                                                                  *
 * The MIT License                                                                  *
 * Marcin Saj 01 Feb 2023                                                           *
 * https://github.com/marcinsaj/FlipDisc                                            *
 *                                                                                  *
 * A dedicated controller is required: https://bit.ly/AC1-FD                        *
 *----------------------------------------------------------------------------------*/

#include <FlipDisc.h>   /* https://github.com/marcinsaj/FlipDisc */ 

/* DO NOT CHANGE IT - pin declaration for the controller */
#define EN_PIN  A7
#define CH_PIN  A2 
#define PL_PIN  A3

void setup() 
{
  /* FlipDisc.Pin(); it is the most important function and first to call before everything else. 
  The function is used to declare pin functions. Before starting the device, double check 
  that the declarations and connection are correct. If the declarations of the control outputs 
  is incorrect, the display may be physically damaged. */
  
  FlipDisc.Pin(EN_PIN, CH_PIN, PL_PIN);
  
  /* FlipDisc.Init(display1, display2, ... display8); it is the second most important function. 
  Initialization function for a series of displays. Up to 8 displays can be connected in series 
  in any configuration. The function has 1 default argument and 7 optional arguments. 
  The function also prepares SPI. Correct initialization requires code names of the serially 
  connected displays:
  - SEG - 7-segment display
  - DOTS - 2x1 or 3x1 dot display
  - FLIP3 - 1x3 display
  - FLIP7 - 1x7 display   
  Example function call for 8 modules: FlipDisc.Init(SEG,SEG,DOTS,SEG,SEG,DOTS,SEG,SEG); */

  FlipDisc.Init(DOTS);
  delay(3000);
}

void loop() 
{
  /* The function is used to turn off (clear) all displays */
  FlipDisc.Clear();
  delay(3000);
  
  /* The function is used to turn on (set) all discs of all displays */
  FlipDisc.All();
  delay(3000);

  FlipDisc.Clear();
  delay(1000);

  /* Function allows you to control a selected disc in a selected dot display. 
  You can control only one dot of the selected display at a time.
  - FlipDisc.ToDot(moduleNumber, dotNumber, dotStatus);
  The first argument moduleNumber is the relative number of the display in the series of all displays. 
  For example, if we have a combination of DOTS, SEG, DOTS, then the second DOTS display 
  will have a relative number of 2 even though there is a SEG display between the DOTS displays. 
  - moduleNumber - relative number of the DOTS display
  - dotNumber - display dot number counting from top to bottom 1-3
  - dotStatus - reset dot "0" or set disc "1" */
  
  FlipDisc.ToDot(1, 1, 1);  /* Set first dot of the first dot display */
  delay(1000);
  FlipDisc.ToDot(1, 2, 1);  /* Set second dot */
  delay(1000);
  FlipDisc.ToDot(1, 3, 1);  /* Set third dot */
  delay(3000);

  /* Function allows you to control one, two or three dots of the selected display. 
  The first argument is the relative number "moduleNumber" of the display in the series 
  of all displays. For example, if we have a combination of DOTS, SEG, DOTS, then 
  the second DOTS display will have a relative number of 2 even though there is a SEG display 
  between the DOTS displays. 
  - FlipDisc.Dot(moduleNumber, dot1, dot2, dot3);
  - moduleNumber - relative number of the DOTS display
  - dot1, dot2, dot3 - display dots counting from top to bottom 1-3 */
  
  FlipDisc.Dot(1, 0);       /* Reset first dot of the first dot display */
  delay(1000);
  FlipDisc.Dot(1, 1, 0);    /* Set first dot and reset second dot */
  delay(1000);
  FlipDisc.Dot(1, 0, 1, 0); /* Reset first dot, set second and reset third */
  delay(3000);

  for(int i = 0; i < 5; i++)
  {
    FlipDisc.Dot(1, 0, 1, 0);
    delay(500);
    FlipDisc.Dot(1, 1, 0, 1);
    delay(500);   
  }

  for(int i = 0; i < 10; i++)
  {
    FlipDisc.ToDot(1, 1, 1);
    delay(200);
    FlipDisc.ToDot(1, 2, 1);
    delay(200); 
    FlipDisc.ToDot(1, 3, 1);
    delay(200); 
    
    FlipDisc.ToDot(1, 1, 0);
    delay(200);
    FlipDisc.ToDot(1, 2, 0);
    delay(200); 
    FlipDisc.ToDot(1, 3, 0);
    delay(200);  
  }
}

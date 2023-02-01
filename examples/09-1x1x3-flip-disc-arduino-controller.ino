/*----------------------------------------------------------------------------------*
 * Flip-disc display controller & 1 x 1x3 display                                   *
 * Example connection diagram: https://bit.ly/AC1-1x1x3                             *
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
  that the declaration and connection are correct. If the declaration of the control outputs 
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

  FlipDisc.Init(FLIP3);
  delay(3000);
}

void loop() 
{
  /* The function is used to turn off (clear) all displays */
  FlipDisc.Clear();
  delay(1000);
  
  /* The function is used to turn on (set) all discs of all displays */
  FlipDisc.All();
  delay(1000);

  FlipDisc.Clear();
  delay(3000);

  /* The function allows you to control up to three discs of the selected display. 
  FlipDisc.Flip3(moduleNumber, disc1,disc2,disc3);
  The first argument is the relative number "moduleNumber" of the display in the series 
  of all displays. For example, if we have a combination of FLIP3, SEG, FLIP3, 
  then the second FLIP3 display will have a relative number of 2 even though 
  there is a SEG display between the FLIP3 displays.
  - moduleNumber - relative number of the FLIP3 display
  - disc1, disc2, disc3 - counting from left to right 1-3 */
  
  /* Set all discs */
  FlipDisc.Flip3(1,1,1,1);
  delay(1000);
  /* Reset first disc */
  FlipDisc.Flip3(1,0);
  delay(1000);
  /* Set first disc and reset second */
  FlipDisc.Flip3(1,1,0);
  delay(1000);
  /* Reset all discs */
  FlipDisc.Flip3(1,0,0,0);
  delay(3000);

  FlipDisc.All();
  delay(1000);

  /* Function allows you to control a selected disc in a selected FLIP3 display.
  You can control only one disc of the selected display at a time.
  FlipDisc.ToFlip3(moduleNumber, discNumber, discStatus);
  The first argument moduleNumber is the relative number of the display 
  in the series of all displays. For example, if we have a combination of 
  FLIP3, SEG, FLIP3, then the second FLIP3 display will have a relative number of 2 
  even though there is a SEG display between the FLIP3 displays.
  - moduleNumber - relative number of the FLIP3 display
  - discNumber - display disc number counting from left to right 1-3
  - discStatus - reset disc "0" or set disc "1" */
  
  /* Reset selected dots of the first FLIPO3 display counting from the left */
  FlipDisc.ToFlip3(1, 1, 0);
  delay(1000);
  FlipDisc.ToFlip3(1, 2, 0);
  delay(1000);
  FlipDisc.ToFlip3(1, 3, 0);
  delay(1000);

  /* Set selected dots */
  FlipDisc.ToFlip3(1, 1, 1);
  delay(1000);
  FlipDisc.ToFlip3(1, 3, 1);
  delay(3000);
  
  FlipDisc.Clear();
  delay(1000);
}

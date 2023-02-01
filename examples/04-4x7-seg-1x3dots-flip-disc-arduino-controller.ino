/*----------------------------------------------------------------------------------*
 * Flip-disc display controller & 4 x 7-segment and 1 x 3x1 dot display             *
 * Example connection diagram: https://bit.ly/AC1-4x7SEG-1x3x1DOTS                  * 
 *                                                                                  *
 * The MIT License                                                                  *
 * Marcin Saj 01 Feb 2023                                                           *
 * https://github.com/marcinsaj/FlipDisc                                            *
 *                                                                                  *
 * A dedicated controller is required to operate the display: https://bit.ly/AC1-FD *                    
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

  FlipDisc.Init(SEG, SEG, DOTS, SEG, SEG);
  delay(3000);
}

void loop() 
{
  /* The function is used to test all declared displays - turn on and off all displays */
  FlipDisc.Test();
  delay(3000);

  /* The function is used to set the delay effect between flip discs. 
  The default value without calling the function is 0. Can be called multiple times 
  anywhere in the code. Recommended delay range: 0 - 100ms, max 255ms */
  FlipDisc.Delay(50);

  /* The function is used to turn on (set) all discs of all displays */
  FlipDisc.All();
  delay(3000);

  /* The function is used to turn off (clear) all displays */
  FlipDisc.Clear();
  delay(3000);

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
  FlipDisc.Dot(moduleNumber, dot1, dot2, dot3);
  - moduleNumber - relative number of the DOTS display
  - dot1, dot2, dot3 - display dots counting from top to bottom 1-3 */
  FlipDisc.Dot(1, 0);       /* Reset first dot of the first dot display */
  delay(1000);
  FlipDisc.Dot(1, 1, 0);    /* Set first dot and reset second dot */
  delay(1000);
  FlipDisc.Dot(1, 0, 1, 0); /* Reset first dot, set second and reset third */
  delay(3000);

  FlipDisc.Delay(25);
  
  /* The function allows you to control one 7-segment display. 
  The first argument "moduleNumber" is the relative number of the display in the series 
  of all displays. For example, if we have a combination of SEG, DOTS, SEG then 
  the second SEG display will have a relative number of 2 even though there is a DOTS display 
  between the SEG displays.
  FlipDisc.ToSeg(moduleNumber, data);
  - moduleNumber - relative number of the SEG display
  - data - symbol to display */ 
  /* An example of calling the functions to display e.g. time 09:23 */
  FlipDisc.ToSeg(1, 0);       /* Display no.1 from the left */
  FlipDisc.ToSeg(2, 9);       /* Display no.2 */
  FlipDisc.ToDot(1, 1, 1);    /* Set dot no.1 */
  FlipDisc.ToDot(1, 2, 1);    /* Set dot no.2 */
  FlipDisc.ToDot(1, 3, 0);    /* Reset dot no.3 */
  FlipDisc.ToSeg(3, 2);       /* Display no.3 */
  FlipDisc.ToSeg(4, 3);       /* Display no.4 */ 
  delay(3000);

  FlipDisc.Clear();
  delay(1000);

  /* Function to control up to eight 7-segment displays. 
  The first argument is the default and the others are optional. 
  This function allows you to display numbers and symbols
  FlipDisc.Seg(data1,data2,data3,data4,data5,data6,data7,data8); */
  /* An example of calling the functions to display e.g. time 12:59 */ 
  FlipDisc.Seg(1, 2, 5, 9);
  FlipDisc.Dot(1, 1, 1, 0);   /* Set dot no.1 & 2, reset dot no.3 */
  delay(3000);
  
  /* Code names for symbols:
  - 8/ALL - Set all discs
  - 10/CLR - Clear Display
  - 11/DEG - "°" - Degree symbol
  - 12/CEL - "C" - Celsius symbol
  - 13/FAH - "F" - Fahrenheit symbol
  - 14/HUM - "H" - Humidity symbol
  - 15/PFH - "%" - Percent first half symbol
  - 16/PSH - "%" - Percent second half symbol
  - 17/UPD - "¯" - Upper dash symbol
  - 18/MID - "-" - Middle dash symbol
  - 19/BTD - "_" - Bottom dash symbol
  - 20/ALD - All three dashes */ 

  FlipDisc.Delay(0);
  
  /* Display temperature: 71°F */
  FlipDisc.Seg(7, 1, DEG, FAH);
  FlipDisc.Dot(1, 0, 0, 0);
  delay(3000);

  /* Display temperature: 71.7F */
  FlipDisc.Seg(7, 1, 7, FAH);
  FlipDisc.Dot(1, 0, 0, 1);
  delay(3000);

  /* Display temperature: 23°C */
  FlipDisc.Seg(2, 3, DEG, CEL);
  FlipDisc.Dot(1, 0, 0, 0);
  delay(3000);

  /* Display temperature: 23.5C */
  FlipDisc.Seg(2, 3, 5, CEL);
  FlipDisc.Dot(1, 0, 0, 1);
  delay(3000);

  /* Display humidity: 49% */
  FlipDisc.Seg(4, 9, PFH, PSH);
  FlipDisc.Dot(1, 0, 0, 0);
  delay(3000);  
}

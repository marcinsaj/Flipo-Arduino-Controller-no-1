/*----------------------------------------------------------------------------------*
 * Flip-disc display controller & 6 x 7-segment display                             *
 * Example connection diagram: https://bit.ly/AC1-6x7SEG                            *
 *                                                                                  *
 * The MIT License                                                                  *
 * Marcin Saj 01 Feb 2023                                                           *
 * https://github.com/marcinsaj/FlipDisc                                            *
 *                                                                                  *
 * A dedicated controller is required: https://bit.ly/AC1-FD                        *
 *----------------------------------------------------------------------------------*/

#include <FlipDisc.h>   // https://github.com/marcinsaj/FlipDisc 

// Pin declaration for Arduino Controller #1
#define EN_PIN  A7  // Start & End SPI transfer data
#define CH_PIN  A2  // Charging PSPS module - turn ON/OFF
#define PL_PIN  A3  // Release the current pulse - turn ON/OFF

void setup() 
{
  /* Flip.Pin(); it is the most important function and first to call before everything else. 
  The function is used to declare pin functions. Before starting the device, double check 
  that the declarations and connection are correct. If the connection of the control outputs 
  is incorrect, the display may be physically damaged. */
  Flip.Pin(EN_PIN, CH_PIN, PL_PIN);
  
  /* Flip.Init(display1, display2, ... display8); it is the second most important function. 
  Initialization function for a series of displays. Up to 8 displays can be connected in series 
  in any configuration. The function has 1 default argument and 7 optional arguments. 
  The function also prepares SPI. Correct initialization requires code names of the serially 
  connected displays:
  - D7SEG - 7-segment display
  - D2X1 - 2x1 display
  - D3X1 - 3x1 display
  - D1X3 - 1x3 display
  - D1X7 - 1x7 display */
  Flip.Init(D7SEG, D7SEG, D7SEG, D7SEG, D7SEG, D7SEG);
  delay(3000);
}

void loop() 
{
  /* The function is used to test all declared displays - turn on and off all displays */
  Flip.Test();
  delay(3000);

  /* The function is used to set the delay effect between flip discs. 
  The default value without calling the function is 0. Can be called multiple times 
  anywhere in the code. Recommended delay range: 0 - 100ms, max 255ms */
  Flip.Delay(50);

  /* The function is used to turn on (set) all discs of all displays */
  Flip.All();
  delay(3000);

  Flip.Delay(25);

  /* The function is used to turn off (clear) all displays */
  Flip.Clear();
  delay(3000);
  
  /* The function allows you to control one 7-segment display. 
  The first argument "module_number" is the relative number of the display in the series 
  of all displays. For example, if we have a combination of D7SEG, D3X1, SEG then 
  the second SEG display will have a relative number of 2 even though there is a D3X1 display 
  between the SEG displays.
  Flip.Display_7Seg(module_number, data);
  - module_number - relative number of the SEG display
  - data - symbol to display */ 
  /* An example of calling the functions to display number 09 23 45 */
  Flip.Display_7Seg(1, 0);       /* Display no.1 from the left */
  Flip.Display_7Seg(2, 9);       /* Display no.2 */

  Flip.Display_7Seg(3, 2);       /* Display no.3 */
  Flip.Display_7Seg(4, 3);       /* Display no.4 */

  Flip.Display_7Seg(5, 4);       /* Display no.5 */
  Flip.Display_7Seg(6, 5);       /* Display no.6 */ 
  delay(3000);

  Flip.Delay(10);
  Flip.Clear();
  delay(1000);

  /* Function to control up to eight 7-segment displays. 
  The first argument is the default and the others are optional. 
  This function allows you to display numbers and symbols
  Flip.Matrix_7Seg(data1,data2,data3,data4,data5,data6,data7,data8); */
  /* An example of calling the functions to display e.g. time 12 59 33 */ 
  Flip.Matrix_7Seg(1, 2, 5, 9, 3, 3);
  delay(3000);

  Flip.Clear();
  delay(1000);
  Flip.Delay(0);

  /* An example of calling the function to set disc no.19 of the first 7-Segment display */
  Flip.Disc_7Seg(1, 19, 1);
  delay(1000);  

/* 0  1  2  3  4
  19           5
  18           6
  17 20 21 22  7
  16           8
  15           9
  14 13 12 11 10 */

  /* Set All discs */
  for(int i = 0; i <= 22; i ++)
  {
  Flip.Disc_7Seg(1, i, 1);
  Flip.Disc_7Seg(2, i, 1);
  Flip.Disc_7Seg(3, i, 1);
  Flip.Disc_7Seg(4, i, 1);
  Flip.Disc_7Seg(5, i, 1);
  Flip.Disc_7Seg(6, i, 1);  
  delay(200);
  }
  
  delay(1000);

  /* Reset disc no.13 */ 
  Flip.Disc_7Seg(2, 13, 0);
  delay(3000);
  
  Flip.Clear();
  delay(1000);

  /* 7-Segment displays allow the display of numbers and symbols.
  Symbols can be displayed using their code name or number e.g. 37/DEG - "°" Degree symbol
  The full list of symbols can be found in the FlipDisc.h library repository https://github.com/marcinsaj/FlipDisc
  Code names for symbols:
  - 0-9
  - 1/VLR  - " |" - Vertical line - right
  - 8/ALL  - Set all discs
  - 10/CLR - Clear display
  - 11/A
  - 12/B
  - 13/C
  - 14/D
  - 15/E
  - 16/F
  - 17/G
  - 18/H
  - 19/I
  - 20/J
  - 21/K
  - 22/L
  - 23/M
  - 24/N
  - 25/O
  - 26/P
  - 27/Q
  - 28/R
  - 29/S
  - 30/T
  - 31/U
  - 32/V
  - 33/W
  - 34/X
  - 35/Y
  - 36/Z
  - 37/DEG - "°"  - Degree symbol
  - 37/PFH - "%"  - Percent first half symbol
  - 38/PSH - "%"  - Percent second half symbol
  - 39/HLU - "¯"  - Horizontal line - upper
  - 40/HLM - "-"  - Horizontal line - middle
  - 41/HLL - "_"  - Horizontal line - lower
  - 42/HLT - "="  - Horizontal line - upper & lower
  - 43/HLA - "≡"  - All three lines
  - 40/MIN - "-"  - Minus symbol
  - 44/VLL - "| " - Vertical line - left
  - 1/VLR  - " |" - Vertical line - right
  - 45/VLA - "||" - All Vertical lines */
  
  /* Display temperature: 71°F */
  Flip.Matrix_7Seg(CLR, CLR, 7, 1, DEG, F);
  Flip.Display_3x1(1, 0, 0, 0);
  delay(3000);

  /* Display temperature: 23°C */
  Flip.Matrix_7Seg(2, 3, DEG, C, CLR, CLR);
  Flip.Display_3x1(1, 0, 0, 0);
  delay(3000);

  /* Display temperature: -12°C */
  Flip.Matrix_7Seg(CLR, MIN, 1, 2, DEG, C);
  Flip.Display_3x1(1, 0, 0, 0);
  delay(3000);

  /* Display humidity: 49% */
  Flip.Matrix_7Seg(4, 9, PFH, PSH, CLR, H);
  Flip.Display_3x1(1, 0, 0, 0);
  delay(3000);  
}

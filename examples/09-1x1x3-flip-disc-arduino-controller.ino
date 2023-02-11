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
  in any configuration. The function also prepares SPI. Correct initialization requires 
  code names of the serially connected displays:
  - D7SEG - 7-segment display
  - D2X1 - 2x1 display
  - D3X1 - 3x1 display
  - D1X3 - 1x3 display
  - D1X7 - 1x7 display 
  Example for two D1X3 displays: Flip.Init(D1X3, D1X3); */
  Flip.Init(D1X3);
  delay(3000);
}

void loop() 
{
  /* The function is used to turn off (clear) all displays */
  Flip.Clear();
  delay(1000);
  
  /* The function is used to turn on (set) all discs of all displays */
  Flip.All();
  delay(1000);

  Flip.Clear();
  delay(3000);

  /* The function allows you to control up to three discs of the selected display. 
  Flip.Display_1x3(module_number, disc1,disc2,disc3);
  The first argument is the relative number "module_number" of the display in the series 
  of all displays. For example, if we have a combination of D1X3, D7SEG, D1X3, 
  then the second D1X3 display will have a relative number of 2 even though 
  there is a D7SEG display between the D1X3 displays.
  - module_number - relative number of the D1X3 display
  - disc1, disc2, disc3 - counting from left to right 1-3 */
  /* Set all discs */
  Flip.Display_1x3(1,1,1,1);
  delay(1000);
  /* Reset first disc */
  Flip.Display_1x3(1,0);
  delay(1000);
  /* Set first disc and reset second */
  Flip.Display_1x3(1,1,0);
  delay(1000);
  /* Reset all discs */
  Flip.Display_1x3(1,0,0,0);
  delay(3000);

  Flip.All();
  delay(1000);

  /* Function allows you to control a selected disc in a selected D1X3 display.
  You can control only one disc of the selected display at a time.
  Flip.Disc_1x3(module_number, discNumber, discStatus);
  The first argument module_number is the relative number of the display 
  in the series of all displays. For example, if we have a combination of 
  D1X3, D7SEG, D1X3, then the second D1X3 display will have a relative number of 2 
  even though there is a D7SEG display between the D1X3 displays.
  - module_number - relative number of the D1X3 display
  - discNumber - display disc number counting from left to right 1-3
  - discStatus - reset disc "0" or set disc "1" */
  /* Reset selected discs of the first FLIPO3 display counting from the left */
  Flip.Disc_1x3(1, 1, 0);
  delay(1000);
  Flip.Disc_1x3(1, 2, 0);
  delay(1000);
  Flip.Disc_1x3(1, 3, 0);
  delay(1000);

  /* Set selected discs */
  Flip.Disc_1x3(1, 1, 1);
  delay(1000);
  Flip.Disc_1x3(1, 3, 1);
  delay(3000);
  
  Flip.Clear();
  delay(1000);
}

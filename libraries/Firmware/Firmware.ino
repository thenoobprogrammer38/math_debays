
// Include Libraries
#include "Arduino.h"
#include "LiquidCrystal_PCF8574.h"
#include "LDR.h"


// Pin Definitions
#define LDR_1_PIN_SIG	A1
#define LDR_2_PIN_SIG	A0
#define LDR_3_PIN_SIG	A2



// Global variables and defines
// There are several different versions of the LCD I2C adapter, each might have a different address.
// Try the given addresses by Un/commenting the following rows until LCD works follow the serial monitor prints. 
// To find your LCD address go to: http://playground.arduino.cc/Main/I2cScanner and run example.
#define LCD_ADDRESS 0x3F
//#define LCD_ADDRESS 0x27
// Define LCD characteristics
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define SCROLL_DELAY 150
#define BACKLIGHT 255
#define THRESHOLD_ldr_1   100
int ldr_1AverageLight;
#define THRESHOLD_ldr_2   100
int ldr_2AverageLight;
#define THRESHOLD_ldr_3   100
int ldr_3AverageLight;
// object initialization
LiquidCrystal_PCF8574 lcdI2C;
LDR ldr_1(LDR_1_PIN_SIG);
LDR ldr_2(LDR_2_PIN_SIG);
LDR ldr_3(LDR_3_PIN_SIG);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    // initialize the lcd
    lcdI2C.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT); 
    ldr_1AverageLight = ldr_1.readAverage();
    ldr_2AverageLight = ldr_2.readAverage();
    ldr_3AverageLight = ldr_3.readAverage();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // LCD 16x2 I2C - Test Code
    // The LCD Screen will display the text of your choice.
    lcdI2C.clear();                          // Clear LCD screen.
    lcdI2C.print("  Circuito.io  ");                   // Print print String to LCD on first line
    lcdI2C.selectLine(2);                    // Set cursor at the begining of line 2
    lcdI2C.print("     Rocks!  ");                   // Print print String to LCD on second line
    delay(1000);

    }
    else if(menuOption == '2') {
    // LDR (Mini Photocell) #1 - Test Code
    // Get current light reading, substract the ambient value to detect light changes
    int ldr_1Sample = ldr_1.read();
    int ldr_1Diff = abs(ldr_1AverageLight - ldr_1Sample);
    Serial.print(F("Light Diff: ")); Serial.println(ldr_1Diff);

    }
    else if(menuOption == '3') {
    // LDR (Mini Photocell) #2 - Test Code
    // Get current light reading, substract the ambient value to detect light changes
    int ldr_2Sample = ldr_2.read();
    int ldr_2Diff = abs(ldr_2AverageLight - ldr_2Sample);
    Serial.print(F("Light Diff: ")); Serial.println(ldr_2Diff);

    }
    else if(menuOption == '4') {
    // LDR (Mini Photocell) #3 - Test Code
    // Get current light reading, substract the ambient value to detect light changes
    int ldr_3Sample = ldr_3.read();
    int ldr_3Diff = abs(ldr_3AverageLight - ldr_3Sample);
    Serial.print(F("Light Diff: ")); Serial.println(ldr_3Diff);

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) LCD 16x2 I2C"));
    Serial.println(F("(2) LDR (Mini Photocell) #1"));
    Serial.println(F("(3) LDR (Mini Photocell) #2"));
    Serial.println(F("(4) LDR (Mini Photocell) #3"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing LCD 16x2 I2C"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing LDR (Mini Photocell) #1"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing LDR (Mini Photocell) #2"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing LDR (Mini Photocell) #3"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/
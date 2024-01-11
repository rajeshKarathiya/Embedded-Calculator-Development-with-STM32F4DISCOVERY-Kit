# Embedded-Calculator-Development-with-STM32F4DISCOVERY-Kit
Designed a calculator using  STM32 microcontroller and STM32F4DISCOVERY kit. Integrated 4x4 keypad for input and 16x2  LCD display for output. Developed efficient GPIO code for keypress and display. Implemented  basic arithmetic operations. Used embedded C and debugging tools.

 
Peripherals used: GPIO Interfacing (STM32VGTx) 
 
The STM32F4DISCOVERY Discovery kit leverages the capabilities of the STM32F407 high-performance microcontrollers, to allow users to develop audio applications easily. It includes an ST-LINK/V2-A embedded debug tool, one ST-MEMS digital accelerometer, one digital microphone, one audio DAC with integrated class D speaker driver, LEDs, LCD display push-buttons, and a USB OTG Micro-AB connector. 
 
To learn GPIO-Interfacing in STM-32 microcontroller, we built a simple calculator using 4*4 keypad matrix and LCD display (16*2). 4*4 matrix is interfaced. Interfacing diagram is shown below. 
 
The usage of STM32 GPIO pins is to interface and read a keypad matrix. We have developed a code of Keypad interfacing. event of key pressing and Key detection. And to display the result in 16*2 led matrix. 

![project_kit](https://github.com/rajeshKarathiya/Embedded-Calculator-Development-with-STM32F4DISCOVERY-Kit/assets/90998760/62e7836d-596f-47d0-bec9-f5d1f101d3d9)


 	 
4*4 keypad Matrix 
 
First of all, we’ll discuss how the keypad matrix works and the general procedure for reading buttons in a keypad. How to actually interface a keypad with any microcontroller. The concept is pretty simple. The Keys in the keypad are divided into ROWs and COLs and we are going to use this to find out which key has been pressed. 
 
we need to configure 8 GPIO pins. Four of which will be inputs and the other 4 are going to be output pins. Then you can hook the column pins to either the input or output pins, but for convenience, I’ll connect them to the 4 output pins. And last but not least, the 4-row pins will be connected to the 4 input pins of the microcontroller. As you can see in the diagram down below. 
 
Whenever the key is pressed, the connection between ROW and COL get completed and the COL pin will read 0. This will tell us that the ROW and COL are both 0 (low) and we will know what key was pressed. 
 
For e.g.- Let’s say I pressed 5. To identify this, I need to pull the second ROW to LOW and then check for the Columns. Whenever the ‘5’ is pressed, the second column will become LOW as the connection between second ROW and second COL will be completed. And this combination of ROW and COLUMN being LOW, will be assigned value ‘5’. 
 
The method using here is the POLLING as the microcontroller keep on polling for the key pressed. 
 
For e.g.- Let’s say I pressed 5. To identify this, I need to pull the second ROW to LOW and then check for the Columns. Whenever the ‘5’ is pressed, the second column will become LOW as the connection between second ROW and second COL will be completed. And this combination of ROW and COLUMN being LOW, will be assigned value ‘5’. 
 
![keypad_4x4](https://github.com/rajeshKarathiya/Embedded-Calculator-Development-with-STM32F4DISCOVERY-Kit/assets/90998760/04e0a557-df19-488c-a66a-af1286d4286d)

![internal_structure_of_keypad](https://github.com/rajeshKarathiya/Embedded-Calculator-Development-with-STM32F4DISCOVERY-Kit/assets/90998760/8eaa5d24-61bd-4c7e-802a-4d642af5037e)

    
 	 
1.3   Liquid Crystal Display(16*2) 
 
LCD (Liquid Crystal Display) screen is an electronic display module and finds a wide range of applications. A 16×2 LCD display is a very basic module and is very commonly used in various devices and circuits. A 16×2 LCD means it can display 16 characters per line and there are 2 such lines. In this LCD each character is displayed in 5×7-pixel matrix. This LCD has two registers, namely, Command and Data. 
 
The command register stores the command instructions given to the LCD. A command is an instruction given to LCD to do a predefined task like initializing it, clearing its screen, setting the cursor position, controlling display etc. The data register stores the data to be displayed on the LCD. The data is the ASCII value of the character to be displayed on the LCD. 
 
 
 ![16X2-LCD-PINS](https://github.com/rajeshKarathiya/Embedded-Calculator-Development-with-STM32F4DISCOVERY-Kit/assets/90998760/102f6648-c53d-4665-ab16-e73ea2c244e1)

 ![s-l1200](https://github.com/rajeshKarathiya/Embedded-Calculator-Development-with-STM32F4DISCOVERY-Kit/assets/90998760/3dba3259-8ca3-438f-9b22-6d5254945dd7)

 





1.3.1   Circuit Diagram & Connection 
 
The circuit diagram for interfacing 16X2 LCD Display with STM32 Development Board is given below: 
 
•	Supply 5V to LCD pins 2,15 from 5V pin of STM32 
•	Connect pin 1,5,16 of LCD to GND of STM32 
•	Connect pin 3 of LCD to 10K Pot as shown in above circuit. 
•	Connect pin 4 (RS) of LCD to PB11 of STM32 
•	Connect pin 6 (EN) of LCD to PB10 of STM32 
•	Connect pin 11 (DB4) of LCD to PA4 of STM32 • Connect pin 12 (DB5) of LCD to PA3 of STM32 • Connect pin 13 (DB6) of LCD to PA2 of STM32 
•	Connect pin 14 (DB7) of LCD to PA1 of STM32 

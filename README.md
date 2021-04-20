# **Weather Station V1**
A project in which I created a working device.

## **Introduction**
Why do a project like this? It's because recently (in the past few months), I joined the Science Club SBT - [**"SBT - Solar Boat Team"**](http://solarboat.pwr.edu.pl/) at Wrocław University of Science and Technology, where due to the influence of passionate, more experienced students,I started to study STM32 architecture. I have never done hardware stuff like this, the idea of designing a working device which can be useful quickly piqued my interests.


## **Project Guidelines**
The listing below shows main goals which the project aims to be:
- Have fun
- Design a working device
- Study STM32 architecture
- Study techniques of programming an external embedded system
- Study analog signal processing in **C** Programming Language
- Gather ideas for future projects
- **What should I do next with gained experience?**

## **Final Device Requirements**
The Device should:
- [x] Have a total budget no more than 10$
- [x] Consume input voltage: 3.3V/5V
- [x] Update current ambient temperature (Celsius scale)
- [x] Update current air humidity (Percent scale)
- [x] Print necessary data on the screen (screen with user friendly graphics)
- [x] Light a LED bulb on data update
- [x] Have RESET button

## **Final Device Outlook**
### **User Interface**
![Alt text](/readme-images/screen-background.png?raw=true "Bluepill pinout used")

### **Chosen Screen**
![Alt text](/readme-images/screen-nokia5110.jpg?raw=true "Nokia5110 LCD screen (SPI interface)")

### **Chosen Sensor**
![Alt text](/readme-images/sensor-dht11.png?raw=true "DHT11 sensor")

## **Implementation Process**
### **Final Device Hardware**
- Stm32f103c8t6 board (BluePill)
- Nokia LCD screen, 5110 84x48px
- DHT11 temperature&humidity sensor
- LED Red bulb
- 3.3kΩ pull-up resistor (for sensor)
- some random 1mm cables

### **Work Organization Process**
1. Setup necessary environment in order to be ablew to save binary file in Bluepill
2. Check connection computer-board. Via program ST-Link Utility, via ST-Link V2 (usb device which allows me to teach Bluepill the code I write - give Bluepill binary/hex .exe file which then is being executed while standalone)
3. Program Bluepill with basic 'toggling-LED' program to test whether it's programmable or not.
4. Choose cheap devices which fulfill project criterions.
5. Ask STM32-experienced students for directions when choosing.
6. Choose proper devices compatible with Bluepill, buy them.
7. Study their manuals to get into the technical part.
8. Configure CUBEMX pinouts, then generate code for pinout - STM32 HAL library:
    - Screen - SPI interface
    - Sensor - Gives analog signal which can be captured via one pin.
    - LED    - Pin output
    - STM32 clocking stuff

![Alt text](/readme-images/cube-config.png?raw=true "CUBEMX configuration pinout")

9. Write LCD class, display some text with predefined font.
10. Display not just text, but a photo
   - Since Nokia5110 LCD screeen is black|white (blue|black) I had to **convert** needed images to proper screen 84x48px
   - And set alpha threshold so it just displays pixels in form of 0/1 dots.
11. Learn about sensor data capturing.
12. Write DHT11 class - sensor class, handle digitization of one pin analog signal.
13. Capture 40 bits of data:
    - [0-7] - integer part of humidity    (in Percent)
    - [8-15]- fractional part of humidity
    - [16-23]-integer part of temperature (in Celsius)
    - [24-31]-fractional part of temperature
    - [32-39]- control sum
14. Display data on the screen and signal with LED red
15. Mount and solder device (since testing it was just on contact palete)
16. Add RESET button - short circuit Bluepill pins : (RESET, GND) makes hardware reset.
17. Program device with last working version of code.

# **Final Device Photos**

![Alt text](/readme-images/1.jpg?raw=true "Photo 1")
![Alt text](/readme-images/2.jpg?raw=true "Photo 2")

### **Bluepill pinout used**
![Alt text](/readme-images/bluepill-pinout.png?raw=true "Bluepill pinout used")


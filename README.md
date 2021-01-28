# **My Weather Station V1**
A project in which I wanted to create working device from scrap - weather station.

## **Introduction**
Why project like this?
Because recently (in the past few months) I joined Science Club [**SBT - Solar Boat Team**](http://solarboat.pwr.edu.pl/)
at **Wrocław University of Science and Technology**, where due to influence of passion of more experienced, older students, I started to study STM32 architecture. Though, I have never been doing hardware stuff like this, the idea of designing a working device which can be useful - quickly found my interests. 

## **Project Guidelines**
Below listing shows main goals which project aimed to be:
- Have fun
- Design a working device
- Study STM32 architecture
- Study techniques of programming an external embedded system
- Study analog signal processing in **C** Programming Language
- Gather ideas for future projects
- **What should you I next with this knowledge?**

## **Final Device Requirements**
Device should:
- [x] Have total budget no more than 10$
- [x] Consume input voltage: 3.3V/5V
- [x] Update current ambient temperature (Celsius scale)
- [x] Update current air humidity (Percent scale)
- [x] Print necessary data on the screen (screen with user friendly graphics)
- [x] Light a LED bulb on data update
- [x] Have RESET button

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
8. Configure CUBEMX pinouts for:
  - Screen - SPI interface
  - Sensor - Gives analog signal which can be captured via one pin.
  - LED    - Pin output
  - STM32 clocking stuff
9. Write LCD class, display some text with predefined font.
10. Display not just text, but a photo
  - Since Nokia5110 LCD screeen is black|white (blue|black) I had to **convert** needed images to proper screen 84x48px
  - And set alpha threshold so it just displays pixels in form of 0/1 dots.
11. Learn about sensor data capturing.
12. Write DHT11 class - sensor class, handle digitization of one pin analog signal.
13. Capture 40 bits of data:
  - [0-7] -  integer part of humidity
  - [8-15]

### **1. STM32 pinout configuration**
![Alt text](/readme-images/cube-config.png?raw=true "CUBEMX configuration pinout")

# **My Weather Station V1**
A project in which I wanted to create working device from scrap - weather station.

## **Introduction**
Why project like this?
Because recently (in the past few months) I joined Science Club [**SBT - Solar Boat Team**](http://solarboat.pwr.edu.pl/)
at **Wrocław University of Science and Technology**, where due to influence of passion of more experienced, older students, I started to study STM32 architecture. Though, I have never been doing hardware stuff like this, the idea of designing a working device which can be useful - quickly found my interests. 

## **Project Guidelines**
Below listing shows main goals which project aimed to achieve:
- Have fun
- Design a working device
- Study STM32 architecture
- Study techniques of programming an external embedded system
- Study analog signal processing in **C** Programming Language
- Gather ideas for future projects
- **What would you do next with this knowledge?**

## **Final Device Requirements**
Device should:
- [x] Have total budget no more than 10$
- [x] Consume input voltage: 3.3V/5V
- [x] Update current ambient temperature (Celsius scale)
- [x] Update current air humidity (Percent scale)
- [x] Print necessary data on the screen
- [x] Light a LED bulb on data update
- [x] Have RESET button

## **Implementation Process**
### **Final Device Hardware**
- stm32f103c8t6 board (BluePill)
- Nokia LCD screen, 5110 84x48px
- DHT11 temperature&humidity sensor
- LED Red bulb
- 3.3kΩ pull-up resistor (for sensor)
- some random 1mm cables

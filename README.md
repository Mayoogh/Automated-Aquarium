# Automated-Aquarium 
This device will automatically change contaminated water from aquarium and refill fresh water just by powering on the device.

## Tinkercad Simulation 
[Link to Simulation](https://www.tinkercad.com/things/a0lOm6MZeaU-automated-aquarium/editel?sharecode=9W0NZiMz0UEaZwgyq93BXftexpjfx08QcJxxL9miNgA=)



## Working
* Once the device is powered, it will check the water level status using the two float switch.If full water is there then it will print  `Full Water Detected` on LCD and will start the draining `Draining....`
* It will drain water till the lower float switch position.
* Once the draining is over, the refilling pump will turn ON and refills water till the top float switch
* Once the refilling is done it will notify the user by the buzzer sound
*  **Blackout Recovery**, While draining or refilling the water if power failure occurs the device can detect it. It will print `Blackout Occured, Resuming` on the LCD and will continue the process

## Features

* Fully automated draining and refilling
* Power failer recovery
* Buzzer notification

##### Why?

The soldering iron station I used was much older than me and had a few drawbacks, including a random heat-to-infinity function if you don't pay attention. So I decided to renew it, but using the old housing and transformers.

##### PCB:

For more Information refer to the pcb, its full of comments.

+ pcb/alte_schaltung_*.*     - the legacy reverse engeneered pcb. (Including switch, trimmer and plugs which are not directly on the pcb)
+ pcb/neue_schaltung.*	     - my new pcb, double sided, excluding switches, the trimmer, the plugs.
+ pcb/out/		     - this is outdated and need to be regenerated! (the 7905 has different pinouts)



##### Features:

+ galvanic seperated
+ Auto timeout (currently 2 min)
+ Enought power (<30s to 300°C)
+ Temperature Display
+ Switch heat on @ zero passing of sine wave.
+ On and off via software (turn trim resistor to left/right dead stop)
+ Display in house temperature

##### Missing: 

+ a nice controller (kalman or at least something which can filter the gwn of the measurements). I really would like to improve this, but currently I'm using 2032 od 2048 bytes of flash. An AtTiny861A would have been better :(

##### Build:

+ If you should ever build this, make shure you understand every part of the hardware and the software. You need to calibrate the timer value and the temperature calculation coefficient and offset.
+ Depending on the used voltages and transformers, you may need to adjust some resistors etc.
+ Pay attention when handeling voltages above 30V, and even more attention with 110 or 230V. Always remove plug before opening the housing and vice versa.
+ I needed to force the position of the holes and the led to match the legacy pcb. You may want to move the holes.
+ Check which type of thermocouple (=thermoeelement) you are using and adjust the amplification if neccessary.

##### Possible improvements:

+ Use Attiny861A with 8000 instead of 2000 kb flash and add more features to the software.
+ Make the led to light up at both the positive and negative half wave.
+ Make some EMV improvements.
+ You probably can omit the negative voltage generation, the currently used opamp is capable of only using a positive one. (I former planed to use another opamp).
+ The polygons that create the ground area can be adjusted, so the triac and the led have more spacing to the surrounding ground area.





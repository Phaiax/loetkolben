
The soldering iron station I used was much older than me and had a few drawbacks, including a random heat-to-infinity function if you don't pay attention. So I decided to renew it, but using the old housing and transformers.

For more Information refer to the pcb, its full of comments.

+ pcb/alte_schaltung_*.*     - the legacy reverse engeneered pcb. (Including switch, trimmer and plugs which are not directly on the pcb)
+ pcb/neue_schaltung.*	     - my new pcb, double sided, excluding switches, the trimmer, the plugs.
+ pcb/out/		     - this is outdated and need to be regenerated! (the 7905 has different pinouts)



====Features:====
+ galvanic seperated
+ Auto timeout (currently 2 min)
+ Enought power
+ Temperature Display
+ Switch heat on @ zero passing of sine wave.
+ On and off via software (turn trim resistor to left/right dead stop)
+ Display in house temperature

====Missing:====
+ a nice controller. I really would like to improve this, but currently I'm using 2032 od 2048 bytes of flash. An AtTiny861A would have been better :(



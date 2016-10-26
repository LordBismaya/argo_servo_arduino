27th July
=========
The ARDUINO servo code used to run the accelerator servo. Arduino MiniPro 5V. 
Had an issue with ROSSERIAL communication. It was due to selection of 3.3V (8MHz) instead of 5V (16Mhz).

Update (25/10/2016):
===================
1. The Servo8 file is the one thats currently written.
2. Servo 7 is just for backup. 
3. To use Create another project and copy it there. Both files cant exist together in the same project.
4. Servo 8 has servo threshold reduced to 10, intial velocity as 0. Also has Servo brake read capability.
5. Reads Left brake info at ADC1. Range 140-275
6. Reads Right Brake Info at ADC0. Range 130-300. 

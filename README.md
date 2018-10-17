# Byggern
Dette er for prosjektet Ping Pong i faget BYGGERN

Build script: cd --> makefile .. $ make
Run scritps: $ sudo make flash

Avr libraries: 
https://github.com/vancegroup-mirrors/avr-libc/blob/master/avr-libc/include/avr/iom162.h

Teste av minnne:
avr-size -C --mcu=atmega162 build/a.out

/dev/ttyACM0 Serial communication for Node2
/dev/ttyS0 Serial communication for Node1


For å finne usb greier: 
dmesg --follow

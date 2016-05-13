Fuse setting command for ATmega328 with internal 8Mhz clock:

    avrdude -c dragon_pp -p atmega328p -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m
    
This [site](http://www.engbedded.com/fusecalc/) has been used much by me to find these things...

Use command

    platformio run --target program
    
with this in your platformio.ini file

    [env:atmega328]
    board = uno
    framework = arduino
    platform = atmelavr
    board_mcu = atmega328p
    board_f_cpu = 8000000L
    upload_protocol = dragon_pp
    upload_flags = -P usb
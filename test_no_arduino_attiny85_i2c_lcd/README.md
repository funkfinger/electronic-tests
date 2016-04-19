---
layout: post
title: "A Mostly No Arduino ATTiny85 I2C LCD"
comments: true
date: 2016-04-19 05:26:42
categories: [attiny85,i2c,lcd]
---

[This is hacked to all get out](https://github.com/funkfinger/electronic-tests/tree/master/test_no_arduino_attiny85_i2c_lcd), but using some sometimes modded Arduino libraries as a start and info found all over the net, I finally managed to get my ATTiny85 talking I2C to a [cheap I2C LCD](http://www.ebay.com/sch/i.html?_odkw=i2c+lcd+2x16&_osacat=0&_from=R40&_trksid=p2045573.m570.l1313.TR0.TRC0.H0.Xi2c+lcd+2x16+1602.TRS0&_nkw=i2c+lcd+2x16+1602&_sacat=0). Why no Arduino? Because I want my own timer interrupts and the ATTiny Arduino core uses the timer(s?) I want to use for `millis()` stuff...

Here's some ATTiny I2C inspiration I found hanging around...

* [https://platis.solutions/blog/2015/03/22/diy-interactive-name-tag/](https://platis.solutions/blog/2015/03/22/diy-interactive-name-tag/)
* [https://github.com/platisd/ATtiny85-LCD-library](ATTiny85 I2C LCD Library)
* [http://mythopoeic.org/adafruit-trinket-i2c/](http://mythopoeic.org/adafruit-trinket-i2c/)
* [http://www.eevblog.com/forum/microcontrollers/good-usi-i2c-master-slave-attiny85-library-(optionally-master-arbitration-)/](http://www.eevblog.com/forum/microcontrollers/good-usi-i2c-master-slave-attiny85-library-(optionally-master-arbitration-)/)
* [https://github.com/adafruit/TinyWireM](https://github.com/adafruit/TinyWireM)
* [http://codinglab.blogspot.com/2008/10/i2c-on-avr-using-bit-banging.html](http://codinglab.blogspot.com/2008/10/i2c-on-avr-using-bit-banging.html)



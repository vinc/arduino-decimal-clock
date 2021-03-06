Arduino Decimal Clock
=====================

    ........................................................................
    ...######.........##...................######......######....##########.
    ..########.......###..................########....########...##########.
    .###....###.....####.................###....###..###....###..........##.
    .##......##....##.##.................##......##..##......##..........##.
    .........##...##..##.........................##..........##.........##..
    ........###..##...##........................###.........###.........##..
    .....#####........##.....................#####.......#####.........##...
    .....#####........##.....................#####.......#####.........##...
    ........###.......##........................###.........###.......##....
    .........##.......##.........................##..........##.......##....
    .##......##.......##.................##......##..##......##......##.....
    .###....###.......##..........#......###....###..###....###......##.....
    ..########...##########......###......########....########......##......
    ...######....##########.......#........######......######.......##......
    ........................................................................


Synopsis
--------

This project is a modern revival of an old revolutionary idea. It started as a
clock representing the Metric Time with kiloseconds but was forked to Decimal
Time displayed as centidays.

The present source code is aimed at an Arduino platform using HT1632C chips to
drive three 16x24 LED matrix panels from Adafruit. A custom 12x16 font is also
provided.


Installation
------------

    $ git clone --recursive git://github.com/vinc/arduino-decimal-clock.git
    $ cd arduino-decimal-clock
    $ rake


License
-------

Copyright (C) 2012-2013 Vincent Ollivier. Released under GNU GPL License v3.

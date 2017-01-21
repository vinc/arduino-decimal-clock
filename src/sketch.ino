/* Copyright (C) 2012-2013 Vincent Ollivier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "font.h"

//#define SERIAL 1
#define MATRIX 1

#ifdef MATRIX
#include "Adafruit_HT1632.h"
#endif

#define DATA   2 // Digital pin
#define WR     3 // Digital pin
#define CS     4 // Digital pin
#define CS2    5 // Digital pin
#define CS3    6 // Digital pin
#define S1     8 // Digital pin
#define S2     9 // Digital pin
#define LED   13 // Digital pin

#define COUNT(array) sizeof(array) / sizeof(array[0])

#define BEAT 864000L // 1 beat == 0.864 seconds

#ifdef MATRIX
Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(DATA, WR, CS, CS2, CS3);
#endif

char screen[] = "******";
unsigned long centidays = 0L;
unsigned long time = micros();

void draw(char c, int offset) {
    if (screen[offset] != c) {
        screen[offset] = c;

        for (int x = 0; x < FONT_WIDTH; x++) {
            for (int y = 0; y < FONT_HEIGHT; y++) {
                int pixel = FONT_PIXEL(c, x, y);
#ifdef MATRIX
                matrix.drawPixel(offset * FONT_WIDTH + x, y, pixel);
#endif
            }
        }
    }
}

void setup()
{
#ifdef SERIAL
    Serial.begin(9600);
#endif

#ifdef MATRIX
    matrix.begin(ADA_HT1632_COMMON_16NMOS);
    matrix.clearScreen();
    matrix.setBrightness(0);
#endif

    pinMode(LED, OUTPUT);
    pinMode(S1, INPUT);
    pinMode(S2, INPUT);
    digitalWrite(S1, HIGH); // Turn on pullup resistors
    digitalWrite(S2, HIGH); // Turn on pullup resistors
}

void write()
{
#ifdef SERIAL
    Serial.println(screen);
#endif

#ifdef MATRIX
    matrix.writeScreen();
#endif
}

void loop()
{
    if (micros() - time > BEAT) { // FIXME: Overflow?
        time += BEAT; // FIXME: Overflow?

        digitalWrite(LED, HIGH);

        int s1 = digitalRead(S1); // Add 1 milliday for switch #1
        int s2 = digitalRead(S2); // Add 1 centiday for switch #2
        int tick = 1 + (s1 == LOW ? 100 : 0) + (s2 == LOW ? 1000 : 0);

        centidays = (centidays + tick) % 100000;

        unsigned long t = centidays;
        int i = COUNT(screen) - 1;
        while (i --> 0) {
            char c;
            if (i == 2) {
                c = '.';
            } else {
                c = '0' + (t % 10);
                t = t / 10;
            }
            draw(c, i);
        }
        write();

        digitalWrite(LED, LOW);
    }
}

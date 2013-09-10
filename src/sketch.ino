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
#include "HT1632.h"
#endif

#define DATA   2 // Digital pin
#define WR     3 // Digital pin
#define CS     4 // Digital pin
#define CS2    5 // Digital pin
#define CS3    6 // Digital pin

#define COUNT(array) sizeof(array) / sizeof(array[0])

#define BEAT 864000L // 1 beat == 0.864 seconds

#ifdef MATRIX
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS, CS2, CS3);
#endif

char screen[] = "******";
unsigned long centidays = 0L;
unsigned long time = micros();

void draw(char c, int offset) {
    if (screen[offset] != c) {
        screen[offset] = c;

        for (int x = 0; x < FONT_WIDTH; x++) {
            for (int y = 0; y < FONT_HEIGHT; y++) {
                int i = FONT_CHAR(c) + FONT_WIDTH * y + x;
                int pixel = (FONT[i] == '#');
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
    matrix.begin(HT1632_COMMON_16NMOS);
    matrix.clearScreen();
#endif
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
        unsigned long t = centidays = (centidays < 99999 ? centidays + 1 : 0);
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
    }
}

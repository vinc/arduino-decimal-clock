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
#include "HT1632.h"

#define DATA 2
#define WR   3
#define CS   4
#define CS2  5
#define CS3  6

HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS, CS2, CS3);

unsigned long centidays = 0L;
char screen[] = "******";

void draw(char c, int offset) {
    if (screen[offset] != c) {
        screen[offset] = c;

        for (int x = 0; x < FONT_WIDTH; x++) {
            for (int y = 0; y < FONT_HEIGHT; y++) {
                int i = FONT_CHAR(c) + FONT_WIDTH * y + x;
                int pixel = (FONT[i] == '#');
                matrix.drawPixel(offset * FONT_WIDTH + x, y, pixel);
            }
        }
    }
}

void setup()
{
    matrix.begin(HT1632_COMMON_16NMOS);
    matrix.clearScreen();
}

void loop()
{
    char c;
    int t = centidays = (centidays < 99999 ? centidays + 1 : 0);
    int i = 6;
    while (i --> 0) {
        if (i == 2) {
            c = '.';
        } else {
            c = '0' + (t % 10);
            t = t / 10;
        }
        draw(c, i);
    }
    matrix.writeScreen();
    delay(864);
}

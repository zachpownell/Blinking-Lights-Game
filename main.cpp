/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ThisThread.h"
#include "mbed.h"
#include <string>

DigitalIn buttonA(PB_6);
DigitalIn buttonB(PC_7);
DigitalIn buttonC(PA_9);
DigitalIn buttonD(PA_7);
DigitalIn resetButton(PA_7);

BusOut leds(PA_10, PB_3, PB_5);


void blinkLEDS(int blinkAmount) {

    for (int i=0 ; i<blinkAmount ; i++) {

        ThisThread::sleep_for(500ms);
        leds = 0b0111;
        ThisThread::sleep_for(1000ms);
        leds = 0b0000;

    }

    ThisThread::sleep_for(1000ms);

}


int main() {

    printf("Starting game...\n\n");

    std::string s = "";
    int highscore = 0;
    blinkLEDS(3);

    while (true) {

        // Generate a random number between 0-2 and append it to the our string 's'.
        s += '0' + (rand() % 3);

        // For loop to iterate through each character in our string
        for (int i=0 ; i<s.size() ; i++) {

            switch(s[i] - '0') {
                case 0:
                    leds = 0b0001;
                    break;
                case 1:
                    leds = 0b0010;
                    break;
                case 2:
                    leds = 0b0100;
                    break;
            }

            // Display the corresponding light for half a second, turn off, then continue
            ThisThread::sleep_for(500ms);
            leds = 0b0000;
            ThisThread::sleep_for(300ms);


        }

        int counter = 0;
        printf("\nCorrect Sequence: %s\n\n", s.c_str());

        while (counter != s.size()) {

            if (buttonA == 0) {

                while (buttonA == 0) leds = 0b0001;
                leds = 0b0000;

                if (s[counter] -'0' != 0) break;
                counter ++;

            }
            if (buttonB == 0) {
                while (buttonB == 0) leds = 0b0010;
                leds = 0b0000;

                if (s[counter] -'0' != 1) break;
                counter ++;

            }
            if (buttonC == 0) {
                while (buttonC == 0) leds = 0b0100;
                leds = 0b0000;

                if (s[counter] -'0' != 2) break;
                counter ++;

            }
            if (buttonD == 0) {
                while (buttonD == 0) leds = 0b0111;
                break;
            }


            //ThisThread::sleep_for(200ms);


            

        }

        if (counter == s.size()) {

            printf("Correct! Next round...\nScore: %d\n\n", s.size());
            blinkLEDS(1);

        } else {

            printf("Incorrect! Restarting...\nFinal Score: %d\n\n", s.size()-1);

            if (s.size()-1 > highscore) {
                highscore = s.size()-1;
                printf("NEW HIGH SCORE: %d\n", highscore);
            }

            blinkLEDS(3);
            s = "";
        }

    }
}
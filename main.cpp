#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn up(D3);
DigitalIn down(D6);
DigitalIn confirm(D5);
AnalogOut Aout(PA_4);
AnalogIn Ain(A0);

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

int main()
{
    int freq[3] = {300, 500, 720};
    int now = 3; // current frequency index
    int flag = 0; // enter the selection mode
    int flag2 = 0; // enter the confirm mode
    int value = 300; // frequency after confirm
    float value2 = 0.00;
    float period = 1/300;
    int sample = 100;
    float ADCdata[200];
    int x = 0; // index of sample points
    int stop = 0;
    float waittime = 0.0;

    up.mode(PullNone);
    down.mode(PullNone);
    confirm.mode(PullNone);
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.color(WHITE);
    uLCD.printf("\n   300\n");
    uLCD.printf("\n   500\n");
    uLCD.printf("\n   720");
    
    while(!flag2){    
        if(up) {
            now++; flag = 1;
        }
        else if(down) {
            now--; 
            if(now <= 0) now += 3;
            flag = 1;
        }
        else if (flag & confirm) {
            value = freq[now % 3];
            value2 = float(value);
            printf("%f\r\n", value2);
            flag2 = 1;
            flag = 0;
            x = 0;
        }
        uLCD.locate(0,(now % 3) * 2 + 1);
        uLCD.printf("->");
        for (int m = 0; m < 11; m++) {
            for (int n = 0; n < 2; n++) 
                if (m != (now % 3) * 2 + 1) {
                    uLCD.locate(n, m);
                    uLCD.printf(" ");
                }
        }
    }
    period = 1.00/value;
//    switch(now % 3) {
//        case 0: waittime = period*10000 - 14.6; break;
//        case 1: waittime = period*10000 - 15.0; break;
//        case 2: waittime = period*10000 - 14.8; break;
//        default: waittime = 0;
//    }
    waittime = period*10000 - 14.6;
//        printf("waittime = %f\n" , waittime);
    while(1) {
        for (float j = 1.0f; j >= 0.0f; j -= 0.01f) {
            Aout = j;
            wait_us(waittime);
            if(x < 2*sample) {
                ADCdata[x] = Ain;
                x++;
            }
//            else x = 0;
//            ThisThread::sleep_for(1000ms/sample);
//        }
//        for (int i = 0; i < sample; i++){
//            ThisThread::sleep_for(100ms);
        }
        if(!stop && x == 200) {
            for (int y = 0; y < 2*sample; y++)
                printf("%f\r\n", ADCdata[y]);
            stop = 1;
        }
//        ThisThread::sleep_for(2s);
    }
}



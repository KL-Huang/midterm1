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
    float select[4] = {1.0/8.0, 1.0/4.0, 1.0/2.0, 1.0};
 //   int freq[3] = {300, 500, 720};
    int now = 0; // current frequency index
//    int flag = 0; // enter the selection mode
    int flag2 = 0; // enter the confirm mode
    float value = 1.0/8.0; // frequency after confirm
    float period = 0.24;
    int sample = 240;
    float ADCdata[200];
    int x = 0; // index of sample points
    int stop = 0;
    float waittime = 0.0;

    up.mode(PullNone);
    down.mode(PullNone);
    confirm.mode(PullNone);
 /*   uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.color(WHITE);
    uLCD.printf("\n   300\n");
    uLCD.printf("\n   500\n");
    uLCD.printf("\n   720");
*/
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.color(WHITE);
    uLCD.printf("\n   %.3f\n", select[now]);
    
    while(!flag2){    
        
//            value2 = float(value);
        if(up) {
            if(now != 3) now++; 
//            flag = 1;
            uLCD.locate(0, 0);
            uLCD.text_width(2);
            uLCD.text_height(2);
            uLCD.color(WHITE);
            uLCD.printf("\n   %.3f\n", select[now]);
        }
        else if(down) {
            if(now != 0) now--;
//            flag = 1;
            uLCD.locate(0, 0);
            uLCD.text_width(2);
            uLCD.text_height(2);
            uLCD.color(WHITE);
            uLCD.printf("\n   %.3f\n", select[now]);
        }
        else if (confirm) {
/*            uLCD.text_width(2);
            uLCD.text_height(2);
            uLCD.color(WHITE);
            uLCD.printf("\n   %f\n", select[now]);
*/
            value = select[now];
//            value2 = float(value);
            printf("%.3f\r\n", value);
            flag2 = 1;
//            flag = 0;
            x = 0;
        }
/*        uLCD.locate(0,(now % 3) * 2 + 1);
        uLCD.printf("->");
        for (int m = 0; m < 11; m++) {
            for (int n = 0; n < 2; n++) 
                if (m != (now % 3) * 2 + 1) {
                    uLCD.locate(n, m);
                    uLCD.printf(" ");
                }
        }
*/
    }
    period = 1.0/(80.0*value);
    waittime = 0.08*value*1000000*value;
    int temp = 240 - int(80.0 * value);
//        printf("waittime = %f\n" , waittime);
   printf("%f\n", period);
    while(1) {
        for (float j = 0.0; j <= 1.0; j += period) {
            Aout = j;
            wait_us(waittime);
            if(x < 2*sample) {
                ADCdata[x] = Ain;
                x++;
            }
            printf("test %d\n", x);
        }
        for (;(x % 240) < temp;) {
            printf("%d\n", temp);
            Aout = 1.0;
            wait_us(waittime);
            if(x < 2*sample) {
                ADCdata[x] = Ain;
                x++;
            }
        }
        for (float j = 1.0; j <= 0.0; j -= period) {
            Aout = j;
            wait_us(waittime);
            if(x < 2*sample) {
                ADCdata[x] = Ain;
                x++;
            }
        }

        if(!stop && x == 2*sample) {
            for (int y = 0; y < 2*sample; y++)
                printf("%f\r\n", ADCdata[y]);
            stop = 1;
        }
//        ThisThread::sleep_for(2s);
    }
}



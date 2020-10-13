// #include <conio.h>
// #include "graphics.h"
// #include <time.h>
// #include <dos.h>
// #include <string.h>

// int main() {
//     int gd = DETECT, gm;
//     int midx, midy;
//     long current_time;
//     char timeStr[256];
//     // Driver = installuserdriver ( "PCX", NULL);
//     char path_to_driver = 'D:\\ystanovki\\gcc\\BGI\\BGI'; //D:\\ystanovki\\gcc\\BGI\\BGI
//     initgraph(&gd, &gm, &path_to_driver); //C:\\TC\\BGI

//     /* mid pixel in horizontal and vertical axis */
//     midx = getmaxx() / 2;
//     midy = getmaxy() / 2;

//     while (!kbhit()) {
//         cleardevice();
//     //     setcolor(WHITE);
//     //     setfillstyle(SOLID_FILL, WHITE);
//     //     rectangle(midx - 250, midy - 40, midx + 250, midy + 40);
//     //     floodfill(midx, midy, WHITE);
//     //     /* Get Current epoch time in seconds */
//     //     current_time = time(NULL);
//     //     /* store the date and time in string */
//     //     strcpy(timeStr, ctime(&current_time));
//     //     setcolor(RED);
//     //     settextjustify(CENTER_TEXT, CENTER_TEXT);
//     //     settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);

//     //     moveto(midx, midy);
//     //     /* print current time */
//     //     outtext(timeStr);
//     //     /* Add delay of 1000 milliseconds(1 second) */
//     //     delay(1000);
//     }

//     getch();
//     closegraph();
//     return 0;
// }



#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <string.h>
#include <iostream>
#include <ctime>

using namespace std;

int main(){
    //---------- Инициализация графики ----------//
    int gdriver = DETECT, gmode, errorcode;
    char ggg = 'i';
    initgraph(&gdriver, &gmode, &ggg);
    //---------- Конец инициализации -----------//

    setfillstyle(SOLID_FILL,GREEN);
    setcolor(GREEN);
    rectangle(50,50,50+400,50+300);
    floodfill(51,51,GREEN);

    setfillstyle(SOLID_FILL,RED);
    setcolor(RED);
    circle(250,200,100); //круг
    floodfill(240,200,RED);

    //---------- Завершение работы ------------//
    getch();
    closegraph();
    cout<<"hi hi"<<endl;
    return 0;
}

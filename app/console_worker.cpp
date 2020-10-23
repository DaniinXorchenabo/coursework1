#pragma once
#include "console_worker.h"
#include <iostream>
// #define _WIN32_WINNT 0x0500
#include<windows.h>
#include<windowsx.h>

#include <wincon.h>
using namespace std;


ConsoleWorker::ConsoleWorker(){
    MessageBox(0, "Hello ^^^ world", "WinAPI is simple",0);
    // cout << "Hello world!" << endl;
    // готовимся и настравиваемся на рисование
    HWND hwnd=GetConsoleWindow();
    HDC hdc=GetDC(hwnd);
    RECT rt;
    GetClientRect(hwnd, &rt);

    // HPEN p1,p2=CreatePen(PS_SOLID,1,RGB(255,0,0)); // Создаем красное перо толщиной 1, перо  это то чем рисуем контур фигур
    // HBRUSH b1,b2=CreateSolidBrush(RGB(0,255,0)); // Создаем зеленую кисть, кисть это то чем закрашивается фигура
    // p1=(HPEN)SelectObject(hdc,p2);  // Заносим красное перо в контекст рисования
    // b1=(HBRUSH)SelectObject(hdc,b2);    // Заносим кисть в контекст рисования
 
    // рисуем: примеры рисования фигур
    // Ellipse(hdc,10,10,100,100);  // рисуем эллипс (он вписан в прямоугольник заданный координатами)
    // MoveToEx(hdc,100,100,NULL); //переносим точку  начала рисования в новое место иначе линия будет рисоваться от элипса.
    // LineTo(hdc,200,200); // рисуем линию
    // Rectangle(hdc,210,210,300,350);// рисуем прямоугольник
    // RoundRect(hdc,210,110,300,180,10,10);// прямоугольник со скруглёнными краями( последние две цифры это размеры эллипса скругляющего края)
    // TextOutA(hdc,100,150,"Heloo text",10); // Пишем строчку текста в заданных координатах (последняя цифра это количество отображаемых букв)
    // SetPixel(hdc,130,120,RGB(0,255,0)); // вот как зажечь пиксел например для рисования функций

}
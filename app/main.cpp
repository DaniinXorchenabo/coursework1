#include <iostream>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <wincon.h>
using namespace std;


long WINAPI mainProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
//Тут вот будем обрабатывать сообщения.
   switch(message)
  {
  case WM_CLOSE:
         {
          PostQuitMessage(0);
         };break;
  }
  return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	HWND hMain=CreateWindowEx(0,WC_DIALOG,"Hello world",WS_VISIBLE | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,200,200,0,0,0,0);
	SetWindowLong(hMain,DWLP_DLGPROC,(long)mainProc);
    while(GetMessage(&msg,0,0,0)!=0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

/*
HWND CreateWindowEx(      
    DWORD dwExStyle,
    LPCTSTR lpClassName,
    LPCTSTR lpWindowName,
    DWORD dwStyle,
    int x,
    int y,
    int nWidth,
    int nHeight,
    HWND hWndParent,
    HMENU hMenu, 
    HINSTANCE hInstance,
    LPVOID lpParam   
);
BOOL GetMessage(
    LPMSG lpMsg,
    HWND hWnd,
    UINT wMsgFilterMin,
    UINT wMsgFilterMax
);

int main()
{
    // MessageBox(0, "Hello ^^^ world", "WinAPI is simple",0);
    // HWND hMain=CreateWindowEx(0,WC_DIALOG,"Hello world",WS_VISIBLE | WS_SYSMENU, 500,500,200,200,0,0,0,0);
    // WinMain()
    // cout << "Hello world!" << endl;
    // готовимся и настравиваемся на рисование
    HWND hwnd=GetConsoleWindow();
    HDC hdc=GetDC(hwnd);
    HPEN p1,p2=CreatePen(PS_SOLID,1,RGB(255,0,0)); // Создаем красное перо толщиной 1, перо  это то чем рисуем контур фигур
    HBRUSH b1,b2=CreateSolidBrush(RGB(0,255,0)); // Создаем зеленую кисть, кисть это то чем закрашивается фигура
    p1=(HPEN)SelectObject(hdc,p2);  // Заносим красное перо в контекст рисования
    b1=(HBRUSH)SelectObject(hdc,b2);    // Заносим кисть в контекст рисования
 
    // рисуем: примеры рисования фигур
    Ellipse(hdc,10,10,100,100);  // рисуем эллипс (он вписан в прямоугольник заданный координатами)
    MoveToEx(hdc,100,100,NULL); //переносим точку  начала рисования в новое место иначе линия будет рисоваться от элипса.
    LineTo(hdc,200,200); // рисуем линию
    Rectangle(hdc,210,210,300,350);// рисуем прямоугольник
    RoundRect(hdc,210,110,300,180,10,10);// прямоугольник со скруглёнными краями( последние две цифры это размеры эллипса скругляющего края)
    TextOutA(hdc,100,150,"Heloo text",10); // Пишем строчку текста в заданных координатах (последняя цифра это количество отображаемых букв)
    SetPixel(hdc,130,120,RGB(0,255,0)); // вот как зажечь пиксел например для рисования функций
    while(true){}
    return 0;
}

*/
/*
#include <iostream>
// #pragma once
#include "point.h"
#include "figure.h"
#include "console_worker.h"
#include <list>
#include <vector>
#include <iterator>


using namespace std;

int main()
{
    Point point1(1, 2);
    Figure test_figure(list<Point>{Point(1,2)});
    std::cout << "Hi!" << std::endl;
    std::cout << test_figure.return_32() << std::endl;
    std::cout << point1.get_x() << " " << point1.get_y()<< std::endl;
    ConsoleWorker con1;
    while (true){

    }
    return 0;
}*/
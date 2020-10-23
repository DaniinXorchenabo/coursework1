#include <iostream>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <wincon.h>
using namespace std;

//Класс нашего приложения
class CApp
{
public:
  //Функция запуска нашего приложения
  //содержит в себе цикл сообщений
  void Run()
  {
    MSG msg;
    while(GetMessage(&msg,0,0,0)!=0)
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }    
  }
};

//* This source code was highlighted with Source Code Highlighter.
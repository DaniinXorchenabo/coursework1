#include <iostream>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <wincon.h>
#include <winuser.h>
using namespace std;
#include <map>
#include <iterator>
#define GWL_USERDATA (-21)

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

//Класс простого окна
class CWnd
{
  public:
    //Тип указателя на функцию
    typedef LRESULT (CWnd::*FuncPointer)(LPARAM,WPARAM);

    //Структура указателя на функцию-обработчик
    struct POINTER
    {
      CWnd* wnd;//Указатель на класс, которому принадлежит обработчик
      FuncPointer func;
    };

    static map<UINT,POINTER> _msgmap;//Карта сообщений

    //Функкция добавления сообщения в карту
    //Приводит указатель на функцию-член класса T к указателю на функцию-член CWnd
    template<typename T>
    static bool AddMessage(UINT message,CWnd* wnd,LRESULT (T::*funcpointer)(LPARAM,WPARAM))
    {
      if(!wnd || !funcpointer) return false;

      POINTER msg;
      msg.wnd=wnd;
      msg.func=reinterpret_cast<FuncPointer>(funcpointer);

      _msgmap.insert(pair<UINT,POINTER>(message,msg));

      return true;
    }

    HWND _hwnd;//Хендл нашего окна

    //Функция создания окна
    bool Create(HWND parent,//Родительское окно, если 0 - то главное окно
                LPCWSTR text,//Заголовок окна
                DWORD exstyle, 
                DWORD style,//Стили окна
                int x, int y, int w, int h,//Размеры и положение
                UINT id//Идентификатор окна
      )
    {
      //Регистрируем класс окна
      WNDCLASSEX wndc;
      // const wchar_t strrrr [] = L"MyWnd";
      LPCSTR fff = "MyWnd";
      wndc.lpszClassName = fff;
      wndc.cbSize=sizeof(WNDCLASSEX);
      wndc.lpfnWndProc=WNDPROC(_WndProc);//Оконная процедура
      wndc.cbClsExtra=0;
      wndc.cbWndExtra=0;
      wndc.hbrBackground=HBRUSH(COLOR_WINDOW);//Цвет фона окна
      wndc.hInstance=GetModuleHandle(0);//Хендл приложения
      wndc.hCursor=LoadCursor(0,IDC_ARROW);//Загружаем старндартный курсор
      wndc.style=CS_HREDRAW|CS_VREDRAW;
      wndc.hIcon=0;
      wndc.hIconSm=0;
      wndc.lpszMenuName=0;
      RegisterClassEx(&wndc);
      LPCSTR fff1 = "MyWnd";
      //Создаем само окно
      LPCSTR text11 = "window title";
      _hwnd=CreateWindowEx(exstyle, fff1, text11,
                          style|WS_CLIPCHILDREN,  //Стиль WS_CLIPCHILDREN нужен для того, чтобы дочерние контролы не мигали при перерисовке
                          x,y,w,h,parent,HMENU(id),
                          GetModuleHandle(0),
                          this  //Передаем в оконную функцию указатель на класс нашего окна
      );

      if(!_hwnd) return false;
      return true;
      }
    
  protected:
    //Оконная функция
    //функция в которую поступают сообщения для обработки
    static LRESULT CALLBACK _WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
    {  
      CWnd *wnd=0;
      //Сообщения WM_NCCREATE приходит до WM_CREATE
      //т.е при создании окна
      if(message==WM_NCCREATE)
      {
        //Получаем указатель на экземпляр нашего окна, который мы передали в функцию CreateWindowEx
        wnd=(CWnd*)LPCREATESTRUCT(lparam)->lpCreateParams;
        //И сохраняем в поле GWL_USERDATA
        SetWindowLong(hwnd, GWL_USERDATA, (LONG)(LPCREATESTRUCT(lparam)->lpCreateParams) );
        wnd->_hwnd=hwnd;      
      }
      //Теперь получаем указатель на наш экземлпяр окна, но уже из поля GWL_USERDATA
      wnd=(CWnd*)GetWindowLong(hwnd,GWL_USERDATA);
      if(wnd)
      {
        //Ищем сообщение в карте
        map<UINT,POINTER>::iterator it;
        it=wnd->_msgmap.find(message);

        //Если сообщение не найдено, то обрабатываем его по умолчанию
        if(it==wnd->_msgmap.end()) return DefWindowProc(hwnd,message,wparam,lparam);
        else
        {
          POINTER msg=it->second;        
          //Вызываем функцию обработчик        
          LRESULT result=(msg.wnd->*msg.func)(lparam,wparam);
          if(result) return result;
        }
      }
      return DefWindowProc(hwnd,message,wparam,lparam);
    }


};

  //Наследуем класс нового окна от CWnd
class CMyWnd: public CWnd
{
public:
  CMyWnd()
  {
    //Добавляем обработчики сообщений WM_CREATE и WM_DESTROY
    AddMessage(WM_CREATE,this,&CMyWnd::OnCreate);
    AddMessage(WM_DESTROY,this,&CMyWnd::OnDestroy);
  }
  LRESULT OnCreate(LPARAM lparam,WPARAM wparam)
  {
    MessageBox(0, "HelloHabr!", "  ", 0);
    return 0;
  }
  
  LRESULT OnDestroy(LPARAM lparam,WPARAM wparam)
  {
    PostQuitMessage(0);
    return 0;
  }
};

int APIENTRY WinMain(HINSTANCE hinst,HINSTANCE prev,LPSTR cmd,int showcmd)
{
  //Создаем наше окно
  CMyWnd *wnd=new CMyWnd;
  wnd->Create(0,L"HelloHabr!",0,WS_OVERLAPPEDWINDOW|WS_VISIBLE,300,300,500,400,0);

  //Запускаем приложение
  CApp *app=new CApp;
  app->Run();
  return 0;
}
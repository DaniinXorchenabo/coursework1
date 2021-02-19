
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

// определение типа для указателя на функцию, которая возвращает void
typedef void (*VoidReturnFunc)();
typedef int (*intReturnFunc)(int);
//typedef void (*VoidReturnFunc)();

int main()
{
//https://proginfo.ru/dll/
   HINSTANCE a = LoadLibrary("my_library.dll");

   VoidReturnFunc myFunc;
   intReturnFunc init_console, print_class;

   init_console = (intReturnFunc) GetProcAddress(a, "create_obj");
   print_class = (intReturnFunc) GetProcAddress(a, "print_class");

   int my_obj = init_console(5694);
   print_class(my_obj);
//   std::cout << ans << std::endl;
   getch();
   return 0;
}


//#include <iostream>
//#include "python_header_test.h"
//#pragma comment(lib, "libmy_library.lib")
//
//int main() {
//    my_python_print();
//    return 0;
//}

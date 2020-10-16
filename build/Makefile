CC=g++
build_materials = ./build/materials/
start_path = -c -Wall
app_dir = ./app/
done_dir = ./done/

all: main

main: main.o figure.o point.o
	
	$(CC) -o $(done_dir)main.exe $(build_materials)main.o $(build_materials)figure.o $(build_materials)point.o
	$(done_dir)main.exe

main.o:
	$(CC) -c $(app_dir)main.cpp -o $(build_materials)main.o

figure.o:

	$(CC) -c $(app_dir)figure.cpp -o $(build_materials)figure.o

point.o:

	$(CC) -c $(app_dir)point.cpp -o $(build_materials)point.o

clean:
	rm -rf $(build_materials)*.o main
# D:\ystanovki\gcc\library\graphics\lib\libgdi32.a D:\ystanovki\gcc\library\graphics\lib\libcomdlg32.a D:\ystanovki\gcc\library\graphics\lib\libuuid.a  D:\ystanovki\gcc\library\graphics\lib\liboleaut32.a  D:\ystanovki\gcc\library\graphics\lib\libole32 .a
# D:\ystanovki\gcc\library\graphics\lib\libgdi32.a
# D:\ystanovki\gcc\library\graphics\lib\libcomdlg32.a
# D:\ystanovki\gcc\library\graphics\lib\libuuid.a
# D:\ystanovki\gcc\library\graphics\lib\liboleaut32.a
# D:\ystanovki\gcc\library\graphics\lib\libole32 .a


# -LD:/ystanovki/gcc/library/graphics/lib -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32    

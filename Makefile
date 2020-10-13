STATIC_LIBS = lib/libbgi.a

all: test_file

test_file: test_file.o
	g++ test_file.o -o test_file
	
	
test_file.o:
	g++ ./app/testing.cpp -o test_file.o  -ID:\ystanovki\gcc\library\graphics\include D:\ystanovki\gcc\library\graphics\lib\libbgi.a
# D:\ystanovki\gcc\library\graphics\lib\libgdi32.a D:\ystanovki\gcc\library\graphics\lib\libcomdlg32.a D:\ystanovki\gcc\library\graphics\lib\libuuid.a  D:\ystanovki\gcc\library\graphics\lib\liboleaut32.a  D:\ystanovki\gcc\library\graphics\lib\libole32 .a
# D:\ystanovki\gcc\library\graphics\lib\libgdi32.a
# D:\ystanovki\gcc\library\graphics\lib\libcomdlg32.a
# D:\ystanovki\gcc\library\graphics\lib\libuuid.a
# D:\ystanovki\gcc\library\graphics\lib\liboleaut32.a
# D:\ystanovki\gcc\library\graphics\lib\libole32 .a


# -LD:/ystanovki/gcc/library/graphics/lib -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32    

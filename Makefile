# Project: CVideolog
# Date:    2017-06-27
# Version: 1.1
# Authors: Deyou Kong <370242479@qq.com>

LDFLAGS = -Wl,-rpath,./ -L./ -lrt $(OPENCV_LINK)
OPENCV_FLAG = `pkg-config opencv --cflags`
OPENCV_LINK = `pkg-config opencv --libs`

Demo.out : Demo.o CVideolog.o
	g++ -o Demo.out Demo.o CVideolog.o $(LDFLAGS)

CVideolog.o : CVideolog.cpp CVideolog.h
	g++ -o CVideolog.o -c CVideolog.cpp -g -Wall --std=c++11 $(OPENCV_FLAG)

Demo.o : Demo.cpp CVideolog.h
	g++ -o Demo.o -c Demo.cpp -g -Wall --std=c++11 $(OPENCV_FLAG)

clean:
	rm -f Demo.out
	rm -f Demo.o CVideolog.o
	rm -f *~

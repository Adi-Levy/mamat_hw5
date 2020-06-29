#Definitions

CXX=g++
CXXFLAGS=-std=c++11 -g -Wall
CXXLINK=g++
LIBS=
OBJS=func.o polynom.o compfunc.o main.o 
RM=rm -f
TARGET = WolfraMamat

$(TARGET): $(OBJS)
	  $(CXXLINK) -o $(TARGET) $(OBJS) $(LIBS)

#Dependencies

func.o: func.cpp func.h
polynom.o: polynom.cpp polynom.h func.h 
compfunc.o: compfunc.cpp compfunc.h polynom.h func.h
main.o: main.cpp func.h polynom.h compfunc.h

#Clean

clean:
	  $(RM) WolfraMamat *.o *.bak *~ "#"* core

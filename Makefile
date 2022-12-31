CXX=g++
CXXFLAGS=-std=c++14
OBJS=main.o Child.o Scheduler.o FIFO.o RR.o MLQ.o MLFQ.o CFS.o

ifeq ($(OS), Windows_NT)
	TARGET=2022-os-proj2.exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		TARGET=2022-os-proj2.out
		FOO=-lstdc++fs
	endif
	ifeq ($(UNAME_S), Darwin)
		TARGET=2022-os-proj2
	endif
endif

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(FOO)

main.o : main.h Scheduler.h Child.h main.cpp
Child.o : Child.h Child.cpp
Scheduler.o : Scheduler.h FIFO.h RR.h MLQ.h MLFQ.h CFS.h Scheduler.cpp
FIFO.o : FIFO.h FIFO.cpp
RR.o : RR.h RR.cpp
MLQ.o : MLQ.h MLQ.cpp
MLFQ.o : MLFQ.h MLFQ.cpp
CFS.o : CFS.h CFS.cpp

clean :
	rm -f *.o $(TARGET)
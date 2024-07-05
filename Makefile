CXX=g++
LD=g++
CFLAGS=-Wall -pedantic -std=c++20 -Wno-long-long -O2

all: tcp_server.out
tcp_server.out: tcp_server.o main.o
	$(LD) -o tcp_server.out tcp_server.o main.o

tcp_server.o: tcp_server.cpp tcp_server.h
	$(CXX) $(CFLAGS) -c tcp_server.cpp -o tcp_server.o
main.o: main.cpp tcp_server.h
	$(CXX) $(CFLAGS) -c main.cpp -o main.o
clean:
	rm -f tcp_server.out tcp_server.o main.o
run: 
	./tcp_server.out
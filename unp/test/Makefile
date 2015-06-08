test:net.o main.o
	g++ -o test net.o main.o
net.o:
	g++ -g -c ../net.cpp
main.o:
	g++ -g -c main.cpp

clean:
	rm -rf test main.o net.o

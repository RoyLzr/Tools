test:net.o main.o client.o server.o
	g++ -o test net.o main.o
	g++ -o client net.o client.o
	g++ -o server net.o server.o
net.o:
	g++ -g -c ../net.cpp
main.o:
	g++ -g -c main.cpp
client.o:
	g++ -g -c client.cpp
server.o:
	g++ -g -c server.cpp

clean:
	rm -rf test main.o net.o client server
	rm -rf client.o server.o

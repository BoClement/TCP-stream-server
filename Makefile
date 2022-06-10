CC = g++
CFLAGS = -Wall -g

all: client_stream server_stream -lpthread

client_stream: mon_client.o socket.h
	$(CC) $(CFLAGS) -o $@ $^

server_stream: mon_server.o socket.h utils/serialib.h utils/serialib.o -lpthread
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf client_stream
	rm -rf server_stream

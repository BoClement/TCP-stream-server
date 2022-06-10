# Server Client TCP - serial stream

The TCP server read the serial stream on the ttyACM0 port and dispatch the information to the client when connected.

# Requirements

1. Linux
2. USB connection on /dev/ttyACM0 (or change in the code)

# Compilation

1. Compile the server.cpp file first and then the client.cpp file.
```bash
make
```
2. Run the server and then the client
```bash
./server_stream
```
```bash
./client_stream
```

# Limitations

Un seul client accepté mais je peux regarder le multi threading pour plusieurs. 
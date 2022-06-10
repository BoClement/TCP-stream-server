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

# MAJ
1. THe stream can be converted into log (and hence rinex) with the rtklib.demo lib. First launch the server and then do :
```bash
sudo ./str2str -in tcpcli://127.0.0.1:5000 -out /output_directery/log_tcp.ubx
```

2. Several clients may connect the same server thanks to threading




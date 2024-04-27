TCP Socket
==========

Server Side:
------------
- socket(): create a socket (an OS resource or file descriptor)
- bind()  : name the socket (local sockets have file name.  network sockets have port number)
- listen(): create a queue for incoming requests (client connects)
- accept(): a new socket is created (for the specific connecting client)
- read()/write(): communicate using the socket

Client Side:
------------
- socket() : (same as above)
- connect(): establish a connection with the server
- read()/write(): commuicate using the socket

---

UDP Socket
==========

Server Side:
------------
- socket(): create a socket (an OS resource or file descriptor)
- bind()  : name the socket (local sockets have file name.  network sockets have port number)
- recvfrom()/sendto(): communicate with the socket

Client Side
-----------
- socket(): (same as above)
- recvfrom()/sendto(): communicate with the socket

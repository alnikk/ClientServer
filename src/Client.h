/*
 * Client.h
 *
 *  Created on: 20 Jan 2014
 *      Author: nicolas
 */

#ifndef CLIENT_H_
#define CLIENT_H_



#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <cstring>
#include <iostream>
#include <string>
#include <netdb.h>
#include <stdlib.h>
#include "Log.h"
using namespace std;


//Target host details:
#define PORT "2361"
#define HOST "192.168.1.10"

class Client {



private :

	Log log;
	int fd_sock;
	struct sockaddr_in addr;
	int status;
	struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
	struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
	void Init();
public :

	Client();
	Client(char* address, char* port);
   ~Client();
   int Connect();
   int InitHostInfo(char *address, char* port);
};


#endif /* CLIENT_H_ */

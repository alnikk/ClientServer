/*
 * Client.cpp
 *
 *  Created on: 20 Jan 2014
 *      Author: nicolas
 */

#include "Client.h"

Client::Client(){
init();
}

Client::Client(string address, int port){
		init();
		initHostInfo(address, port);


}

int Client::initHostInfo(string address, int port){//

char const * p = to_string(port).c_str();
	status = getaddrinfo(address.c_str() , p, &host_info, &host_info_list);
		 if(status != 0){
			log.write("Client : Failed to get Hosts Info",Log::WARN);

			return status;
		 }

		log.write("Client is ready to connect to the server",Log::DBG);

		return status;
}

int Client::connection(){

	fd_sock = socket(host_info_list->ai_family,
			host_info_list->ai_socktype,
			host_info_list->ai_protocol);

		 if (fd_sock == -1)
			 log.write("Client : Failed creating the socket",Log::ERR);

		 status = connect(fd_sock, host_info_list->ai_addr, host_info_list->ai_addrlen);

		 if (status == -1)
			 log.write("Client : Connection Error : Failed to connect to Host",Log::ERR);

		 return status;
}
void Client::run(){

string msg, rcv;
	connection();

	for(;;){
		cout << "Client : type a command to send"<<endl;
		cin >> msg;
		cout<<"Message to be sent "<<msg<<" length "<<msg.length()<<endl;
		sendCmd(msg);
		cout<<"Client : waiting for an answer .."<<endl;
		rcv = receive();
		cout<<"Client [RCV] : "<<rcv<<endl;
	}
}

int Client::sendCmd(string cmd){

	if(send(fd_sock,cmd.c_str(),cmd.length(),0)==-1){
			log.write("Client : Error when sending message",Log::ERR);
			return -1;
	}

	return 0;
}

string Client::receive(){

	char buff[256];

	if(recv(fd_sock,buff,256,0)==-1){
			log.write("Client : Error when receiving message",Log::ERR);
			return "";
	}

	return (string)buff;
}
void Client::init(){
		fd_sock = -1;
		status = -1;
		memset(&host_info, 0, sizeof host_info);
		host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
		host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
}

Client::~Client()
{

}

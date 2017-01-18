/************************************************************
* File description: TCP implementation.						*
* the class inherit from socket. 							*
* methods of tcp socket type								*
************************************************************/

#include "Tcp.h"

/***********************************************************************
* function name: Tcp												   *
* The Input: Boolean, true - if server, false if client	and port number*
* The output: none										               *
* The Function operation: creating new Tcp. initialize if server and   *
* port_num by the input												   *
***********************************************************************/
Tcp::Tcp(bool isServers, int port_num) {
	this->descriptorCommunicateClient = 0;
	this->port_number = port_num;
	this->isServer = isServers;

}

/***********************************************************************
* function name: ~Tcp												   *
* The Input: none													   *
* The output: none										               *
* The Function operation: default destructor					       *
***********************************************************************/
Tcp::~Tcp() {
	// TODO Auto-generated destructor stub
    while(!this->clientSocks.empty()){
        this->clientSocks.pop_back();
    }
}

/***********************************************************************
* function name: initialize											   *
* The Input: none              										   *
* The output: int number representing the return status		           *
* The Function operation: initialize the Socket object by getting	   *
* socket descriptor. bind and accept for servers or connect for clients*
***********************************************************************/
int Tcp::initialize() {
	//getting a socket descriptor and check if legal
	this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketDescriptor < 0) {
		//return an error represent error at this method
		return ERROR_SOCKET;
	}
	//if server
	if (this->isServer) {
		//initialize the struct
		struct sockaddr_in sin;
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(this->port_number);
		//bind
		if (bind(this->socketDescriptor,
				(struct sockaddr *) &sin, sizeof(sin)) < 0) {
			//return an error represent error at this method
			return ERROR_BIND;
		}
		//listen
		if (listen(this->socketDescriptor, this->backLog) < 0) {
			//return an error represent error at this method
			return ERROR_LISTEN;
		}
		//accept
		/*
		struct sockaddr_in client_sin;
		unsigned int addr_len = sizeof(client_sin);
		this->descriptorCommunicateClient = accept(this->socketDescriptor,
				(struct sockaddr *) &client_sin, &addr_len);
		if (this->descriptorCommunicateClient < 0) {
			//return an error represent error at this method
			return ERROR_ACCEPT;
		}
		 */
	//if client
	} else {
		struct sockaddr_in sin;
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = inet_addr((this->ip_address).c_str());
		sin.sin_port = htons(this->port_number);
		if (connect(this->socketDescriptor,
				(struct sockaddr *) &sin, sizeof(sin)) < 0) {
			//return an error represent error at this method
			return ERROR_CONNECT;
		}
	}
	//return correct if there were no problem
	return CORRECT;
}


int Tcp::acceptClient(){
        struct sockaddr client_sin;
		unsigned int addr_len = sizeof(client_sin);
		this->descriptorCommunicateClient = accept(this->socketDescriptor,
				(struct sockaddr *) &client_sin, &addr_len);
		if (this->descriptorCommunicateClient < 0) {
			//return an error represent error at this method
			return ERROR_ACCEPT;
		}
		this->clientSocks.push_back(this->descriptorCommunicateClient);
}
/***********************************************************************
* function name: sendData											   *
* The Input: string data to send									   *
* The output: int number representing the return status		           *
* The Function operation: sending the required data, using his length  *
* and the socket descroptor											   *
***********************************************************************/
int Tcp::sendData(string data, int index) {
	int data_len = data.length();
	const char * datas = data.c_str();
    int sent_bytes;
    if (this->isServer) {
		try {
        sent_bytes = send(this->clientSocks[index], datas, data_len, 0);
		} catch (...){
			cout << "send recv" << endl;
			return ERROR_RECIVE;
		}
    } else {
		try {
        sent_bytes = send(this->socketDescriptor, datas, data_len, 0);
		} catch (...){
			cout << "send recv" << endl;
			return ERROR_RECIVE;
		}
    }
	if (sent_bytes < 0) {
		//return an error represent error at this method
		return ERROR_SEND;
	}
	//return correct if there were no problem
	return CORRECT;
}

/***********************************************************************
* function name: recive	`											   *
* The Input: none										               *
* The output: int number representing the return status	               *
* The Function operation: getting data from the other socket to,	   *
* enter it to the buffer and print the data							   *
***********************************************************************/
int Tcp::reciveData(char* buffer, int size, int index) {
    int read_bytes;

		if (isServer) {
			try {
			read_bytes = recv(this->clientSocks[index], buffer, size, 0);
			} catch (...){
				cout << "cant recv" << endl;
				return ERROR_RECIVE;
			}
		} else {
			try {
			read_bytes = recv(this->socketDescriptor, buffer, size, 0);
			} catch (...){
				cout << "cant recv" << endl;
				return ERROR_RECIVE;
			}
		}

	//checking the errors
	if (read_bytes == 0) {
		return CONNECTION_CLOSED;
	}
	else if (read_bytes < 0) {
		//return an error represent error at this method
		return ERROR_RECIVE;
	} else {
		//prinrting the massege
//		cout<<buffer<<endl;
	}
	//return correct if there were no problem
	return read_bytes;
}

int Tcp::getClientSock(int i) {
    return this->clientSocks[i];
}
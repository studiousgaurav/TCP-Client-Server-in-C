#include <stdio.h> //Has standard input and output library providing simple and efficient buffered stream IO interface.
#include <sys/types.h> //Defines the data type of socket address structure in unsigned long.
#include <sys/socket.h> //The socket functions can be defined as taking pointers to the generic socket address structure called sockaddr. 
#include <netinet/in.h> //Defines the IPv4 socket address structure commonly called Internet socket address structure called sockaddr_in.
#include <unistd.h> //posix std for open system interface

int main(int argc, char* argv[])
{
int s = socket(AF_INET, SOCK_STREAM, 0); //TCP socket is created 
	struct sockaddr_in sadd; //to store server address
	sadd.sin_family = AF_INET; //Internet IP protocol
sadd.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY is used when you don't need to bind a socket to a specific IP.
	sadd.sin_port = htons(1999); //htons() function converts the port number 		into a Big Endian short integer.
	socklen_t slen = sizeof(sadd); //size of address
	bind(s, (struct sockaddr*) &sadd, slen); //Bind function assigns a local protocol address to the socket
	printf("Server connected!\n");
	listen(s, 1); //Listen function specifies the maximum number of connections that kernel should queue for this socket
	struct sockaddr_in cadd; //store client address

	socklen_t clen = sizeof(cadd); // client address length

	int a = accept(s, (struct sockaddr*) &cadd, &clen); 

	printf("Client connected!\n");

	while (1)
	{
		char b[1024];
		recv(a, b, sizeof(b), 0);
		printf("Message: %s", b);
	}

	close(s);
}

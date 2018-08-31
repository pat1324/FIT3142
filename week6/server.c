#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SOCKETserver "mynewsocket"

int main(void){

  //int flag = 0;//used for turning server off if equal to 1
  char buffer[256];
  int sock, newsock;//@sock, newsock: store the values returned by the socket system call and the accept system call. Used for all future references to these sockets.
  struct sockaddr_un server;//struct containing address of server
  socklen_t address_size;

  int n;//return value for the read() and write() calls. Stores number of characters read/write


  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){//attempt to create socket
		perror("server: socket");
		exit(1);
	}

  memset(&server, 0, sizeof(struct sockaddr_un));//zero's all values in server address
  server.sun_family = AF_UNIX;//both client and server on same machine
  strcpy(server.sun_path, SOCKETserver);//call the socket mynewsocket
  address_size = sizeof(server.sun_family) + strlen(server.sun_path);
  unlink(server.sun_path);//get rid of server name.

  if (bind(sock, (struct sockaddr*) &server, SUN_LEN(&server)) < 0){
		perror("server: bind");
		exit(1);
	}

  if (listen(sock, 5) < 0) {//max number of clients waiting in queue: 5
    perror("server: listen");
    exit(1);
  }

  if ((newsock = accept(sock, (struct sockaddr *) &server, &address_size)) < 0){
    perror("server: accept");
    exit(1);
  }

  while(1){
    memset(&buffer, 0, sizeof(buffer));
    //bzero(buffer, 256);//refresh buffer
    n = read(newsock, buffer, 256);//read from new socket
    if (n <= 0){
      printf("client disconnected\n");
      close(newsock);
      close(sock);
      return 0;
    }
    printf("msg: %s", buffer);

  }
}

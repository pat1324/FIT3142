#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SOCKETNAME "mynewsocket"

int main(int argc, char *argv[]){
	char buffer[256];
	int n, sock, len;
	struct sockaddr_un name;

	//FILE *f = fopen(argv[1], "r");//open file for reading

	if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
		perror("server: socket");
		exit(1);
	}

	memset(&name, 0, sizeof(struct sockaddr_un));
	name.sun_family = AF_UNIX;
	strcpy(name.sun_path, SOCKETNAME);
	len = sizeof(name.sun_family) + strlen(name.sun_path);

	if (connect(sock, (struct sockaddr *) &name, SUN_LEN(&name)) < 0) {
		perror("client: connect");
		exit(1);
	}

  while(1){
    printf("Enter a message\n");
    fgets(buffer, sizeof(buffer), stdin);
    send(sock, buffer, sizeof(buffer), 0);//send
  }
	close(sock);
	exit(0);
}

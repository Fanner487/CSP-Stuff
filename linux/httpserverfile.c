#include "unp.h"
#include "string.h"


int main(int argc, char **argv) {

	int listenfd, connfd, n; // Socket Ids; one for listening and one for the connected socket.
	struct sockaddr_in servaddr; // Address structure to hold this server's address.
	char buff[MAXLINE], recvline[MAXLINE], cmd[16], path[64], vers[16], hostHeading[16], hostResult[20];
	char path1[64] = ".";
	FILE * hFile;
	int char_in, count = 0;

	if (argc != 2) {
		err_quit("Usage: <Program Name><Port No.>\n");
	}


	// Create a socket.
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr)); // Zero and fill in server address structure.
	servaddr.sin_family 		= AF_INET;
	servaddr.sin_addr.s_addr 	= htonl(INADDR_ANY); // Connect to any local ip address.
	servaddr.sin_port 		= htons(atoi(argv[1])); // Daytime server port number;

	// Connects the socket to an external interface.
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	// Changes the socket to a " Passive listening" socket
	Listen(listenfd, LISTENQ);



	for ( ; ; ) {
		// Accept next connection request.
		connfd = Accept(listenfd, (SA *) NULL, NULL);

		// Read in request.
		while((n = read(connfd, recvline, MAXLINE)) > 0) {
                	recvline[n] = 0; // Null terminate.
                	printf("Printing the command\n");
                	if(fputs(recvline, stdout) == EOF) {
                        	err_sys("fputs erorr");
                	}
			if((strstr(recvline, "\r\n\r\n")) != NULL) {
				break;
			}
        }//end while 


		sscanf(recvline,"%s %s %s %s %s", cmd, path, vers, hostHeading, hostResult); //parse command 

		printf("Next Parameter\n%s %s\n", hostHeading, hostResult);
		
		strcat(path1, path);

		if(strcmp(path1, "./") == 0)
		{
			strcpy(path1, "./index.html");
		}

		hFile = fopen(path1, "r");

		if(hFile == NULL)
		{
			hFile = fopen("error.html", "r");
		}

		strcpy(buff, "");
		
		while((char_in = fgetc(hFile)) != EOF)
		{
			buff[count] = char_in;
			count++;
		}

		
		//if(strcmp(path, "/index.html") == 0) 
		//	snprintf(buff, sizeof(buff), "HTTP/1.1 200 OK\r\n\r\n<html><head>Your Request Was Good!</head></html>\r\n");
		//else
		//	snprintf(buff, sizeof(buff), "HTTP/1.1 404 Page Not Found\r\n\r\n<html><head>Your Request Was Bad</head></html>\r\n");
		
		buff[count] = 0;
		// Write data to the client.
		Write(connfd, buff, strlen(buff));
		
		count = 0;
		fclose(hFile);
		strcpy(path1, ".");
		printf("Closing Connection\n");
		Close(connfd);
	}
}
// Note the use of the upper-case letters at the start of the socket primitives names.
// These are wrapper function that include error-checking functionality for each call.
// The actual socket primitives use lower case names.

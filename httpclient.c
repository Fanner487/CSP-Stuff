#include "unp.h"


int main(int argc, char **argv){
	
	char *ptr, **pptr;
	int sockfd, n, counter = 0;
	char recvline[MAXLINE + 1], buff[MAXLINE + 1];
	struct sockaddr_in servaddr;
	struct hostent *hptr;

	if(argc != 3) {
		err_quit("Usage: a.out <IPAddress>>");
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		err_sys("Socket eroror");
	}

	ptr = &argv[1];

	if((htpr = gethostbyname(ptr)) == NULL)
	{
		err_msg("gethostbyname error for host: %s: %s", ptr hstrerror(h_errno));
		continue;
	}
	
	printf("\n\nofficial hostname: %s\n", hptr->h_name);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	memcpy(&servaddr.sin_addr, *pptr, sizeof(*pptr));

	// Daytime server port taken from the command line.
	servaddr.sin_port = htons(atoi(argv[2])); 

	// Convert dotted IP Address to network byte order.
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		err_quit("inet_pton error for %s", argv[1]);
	}

	if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0) {
		err_sys("Connect error");
	}
	
	snprintf(buff, sizeof(buff), "GET /index.html HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", argv[1]); //construct data to return
        Write(sockfd, buff, strlen(buff));

	while((n = read(sockfd, recvline, MAXLINE)) > 0) {
		counter++; // Count the number of loops completed.
		recvline[n] = 0; // Null terminate.

		// Print data (time and date.)
		if(fputs(recvline, stdout) == EOF) {
			err_sys("fputs erorr");
		}
	}

	if(n < 0) {
		err_sys("read error");
	}

	printf("counter = %d\n", counter);
	exit(0);

}

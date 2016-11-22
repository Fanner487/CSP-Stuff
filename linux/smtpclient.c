#include "unp.h"

//209.85.203.27
int main(int argc, char **argv){
	
	
	int sockfd, n, counter = 0;
	char recvline[MAXLINE + 1], buff[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if(argc != 3) {
		err_quit("Usage: a.out <IPAddress>>");
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		err_sys("Socket eroror");
	}

	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;


	// Daytime server port taken from the command line.
	servaddr.sin_port = htons(atoi(argv[2])); 

	// Convert dotted IP Address to network byte order.
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		err_quit("inet_pton error for %s", argv[1]);
	}

	//connect to the server
	if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0) {
		err_sys("Connect error");
	}

	//read
	while((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0; // Null terminate.

		// Print data (time and date.)
		if(fputs(recvline, stdout) == EOF) 
			err_sys("fputs erorr");

		if (strstr(recvline, "\r\n")>0)
			break;	
		
	}

	if(n < 0) {
		err_sys("read error");
	}

	
	snprintf(buff, sizeof(buff), "HELO [147.252.234.34]\r\n"); //construct data to return
        Write(sockfd, buff, strlen(buff));

	while((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0; // Null terminate.

		// Print data (time and date.)
		if(fputs(recvline, stdout) == EOF) 
			err_sys("fputs erorr");

		if (strstr(recvline, "\r\n")>0)
			break;	
		
	}

	if(n < 0) {
		err_sys("read error");
	}

	
	snprintf(buff, sizeof(buff), "MAIL FROM: <theditdisciplinaryboard@dit.ie>\r\n"); //construct data to return
        Write(sockfd, buff, strlen(buff));

        while((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0; // Null terminate.

		// Print data (time and date.)
		if(fputs(recvline, stdout) == EOF) 
			err_sys("fputs erorr");

		if (strstr(recvline, "\r\n")>0)
			break;	
		
	}

	if(n < 0) {
		err_sys("read error");
	}

	snprintf(buff, sizeof(buff), "RCPT TO: <c14341031@mydit.ie>\r\n"); //construct data to return
        Write(sockfd, buff, strlen(buff));

        while((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0; // Null terminate.

		// Print data (time and date.)
		if(fputs(recvline, stdout) == EOF) 
			err_sys("fputs erorr");

		if (strstr(recvline, "\r\n")>0)
			break;	
		
	}

	if(n < 0) {
		err_sys("read error");
	}

	snprintf(buff, sizeof(buff), "DATA\r\n"); //construct data to return
        Write(sockfd, buff, strlen(buff));

        while((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0; // Null terminate.

		// Print data (time and date.)
		if(fputs(recvline, stdout) == EOF) 
			err_sys("fputs erorr");

		if (strstr(recvline, "\r\n")>0)
			break;	
		
	}

	if(n < 0) {
		err_sys("read error");
	}

/*

Hey Katie, the porters gave me a loan of a big fuck off ladder, should work really well with the metal chair? You did bring it didn't you? Anyhoo, I'm in the courtyard with a boom box basting out my entrance music, Killing in the Name of (Rage). I've recorded over some of the lyrics, so now it's "Fuck you Katie, I won't do what you tell me"!! got one ready for you too, my little pony alright? Bring it!!!
*/


	snprintf(buff, sizeof(buff), "From: theditdisciplinaryboard@dit.ie\r\nTo: c14341031@mydit.ie\r\nSubject: Disciplinary Board Meeting\r\n\r\nDear Mr. Murphy,\n\nIt has come to our attention that during the past semester you have been engaging in discriminatory acts of racism. Please note this is not tolerated in this college and is a direct violation of the DIT Student Charter, and we take these matters very seriously. We have been informed of this by your fellow student, Haashim Bari. Knowing this, we have decided to hold a meeting between yourself and Haashim to discuss the allegations.\n\nYou filthy, filthy racist\n\nWith love,\nPaul xoxo\r\n\r\n.\r\n"); //construct data to return
        Write(sockfd, buff, strlen(buff));

        while((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0; // Null terminate.

		// Print data (time and date.)
		if(fputs(recvline, stdout) == EOF) 
			err_sys("fputs erorr");
		if (strstr(recvline, "\r\n")>0)
			break;	
		
	}

	if(n < 0) {
		err_sys("read error");
	}


	

	snprintf(buff, sizeof(buff), "QUIT\r\n"); //construct data to return
        Write(sockfd, buff, strlen(buff));

        while((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0; // Null terminate.

		// Print data (time and date.)
		if(fputs(recvline, stdout) == EOF) 
			err_sys("fputs erorr");
		if (strstr(recvline, "\r\n")>0)
			break;	
		
	}

	if(n < 0) {
		err_sys("read error");
	}






	exit(0);

}

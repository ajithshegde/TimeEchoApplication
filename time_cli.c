#include	"unp.h"

int
main(int argc, char **argv)
{	
//	for( ; ; ){
//	printf("%s \n",argv[1]);
//	sleep(5); 
	int					sockfd, n;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;
	int pf;
	char buf[100],last[100];
	strcpy(buf,"Time displayed");
	strcpy(last,"Time Child terminating");
	pf = atoi(argv[2]);
	if (argc < 3)
		err_quit("usage: a.out <IPaddress>");
	//sleep(5);
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");
//	printf("Sockfd = %d\n",sockfd);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(14086);	
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");
	for( ; ; ){
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	

		if (fputs(recvline, stdout) == EOF){
			write(pf,last,strlen(last)+1);
			err_sys("fputs error");}
		write(pf,buf,strlen(buf)+1);
	}
		 write(pf,last,strlen(last)+1);
	}
	if (n < 0)
		err_sys("read error");

	exit(0);

}

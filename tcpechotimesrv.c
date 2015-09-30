#include "unpthread.h"
#include	"unp.h"
#include	<time.h>

void* time_exe(){

	int                        listenfd, connfd;
	struct sockaddr_in      servaddr;
	char                            buff[MAXLINE];
	time_t                          ticks;
	int i=15;
	int det;
	printf("Time Thread created\n");

	det=pthread_detach(pthread_self());	
	printf("Time Thread detached %d\n",det);
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR,(char*)&i,sizeof(int));	

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(14086);        /* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);


	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		for( ; ; ){
			ticks = time(NULL);
			snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
			if(write(connfd, buff, strlen(buff)) < 0){
				//fprintf(stdout,"%s","Error in client side");
				break;
			}
			sleep(5);
		}
		Close(connfd);




	}
	//printf("Error in client side\n");



	return (NULL);

}

void* echo_exe(){

	int                        listenfd_e, connfd_e;
	struct sockaddr_in      servaddr_e;
	char                            buff_e[MAXLINE];

	int j=15;
	int dete,n;
	printf("Echo Thread created\n");

	dete=pthread_detach(pthread_self());
	printf("Echo Thread detached %d\n",dete);
	listenfd_e = Socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(listenfd_e, SOL_SOCKET,SO_REUSEADDR,(char*)&j,sizeof(int));

	bzero(&servaddr_e, sizeof(servaddr_e));
	servaddr_e.sin_family      = AF_INET;
	servaddr_e.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr_e.sin_port        = htons(14087);        

	Bind(listenfd_e, (SA *) &servaddr_e, sizeof(servaddr_e));

	Listen(listenfd_e, LISTENQ);
	
	for( ; ;){

	connfd_e = Accept(listenfd_e,(SA*) NULL, NULL);
	
	if( (n = readline(connfd_e,buff_e,MAXLINE) == 0){
		return ;

}
}
	return (NULL);
} 

	int
main(int argc, char **argv)
{
	pthread_t thread_time,thread_echo;
	//pthread_attr_t time_attr;
	int tt,te;

	//tc = pthread_attr_init(&time_attr);
	tt = pthread_create(&thread_time, NULL,time_exe, NULL);
	te = pthread_create(&thread_echo, NULL,echo_exe, NULL);
	//printf("tc = %d\n",tc);	
	pthread_exit(NULL);

	//time_exe();


}

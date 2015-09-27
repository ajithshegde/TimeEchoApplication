#include	"unp.h"

int
main(int argc, char **argv)
{
	struct hostent *ha;
	struct in_addr addr_4;

 	char str[INET_ADDRSTRLEN];
//	const char *addr1;

	if (argc != 2)
		err_quit("usage: a.out <host_name>");
	if(inet_pton(AF_INET, argv[1], &addr_4)<= 0){
//	err_quit("Invalid IP");
	  if ((ha = gethostbyname(argv[1])) == NULL) {  
                err_quit("Invalid host name or IP address");
                return 2;
          }
	else{
		// addr1 = inet_ntop(ha->h_addrtype,ha->h_addr_list[0],str,sizeof(str));
printf("Address is %s \n",inet_ntop(ha->h_addrtype,ha->h_addr_list[0],str,sizeof(str)) );


            }
	
	}
	else{
		if((ha = gethostbyaddr(&addr_4,sizeof(addr_4),AF_INET)) == NULL){
		herror("Enter valid IP address");
		return 2;
	     }
		else{
		printf("The host name is %s \n",ha->h_name);

}
	
	}

			
	exit(0);
}
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include "csptr/smart_ptr.h"

typedef struct sockaddr_in sockaddr_in;


void closed_socket(void *ptr, void * meta){
    int file_descriptor = *((int*)(ptr));
    if(0 == close(file_descriptor)){
        printf("Socket %d has closed!!!\nStatus code = %d\n", file_descriptor ,errno);
    } else
    {
         perror("Socket closing ERROR!!!\n");
    }
}

int main(void)
{
    smart int *socket_df = unique_ptr(int,socket(AF_LOCAL, SOCK_STREAM, 0),closed_socket);
    int yes = 1;
    if(*socket_df == -1)
        perror("Socken don't created!");

    if (setsockopt(*socket_df, SOL_SOCKET,SO_REUSEADDR, &yes, sizeof(int)) == -1)
        perror("Setting socket option SO_REUSEADDR");
        //exit(1);

    smart sockaddr_in *host_addr = unique_ptr(sockaddr_in,{
        .sin_family = AF_LOCAL,
        .sin_port = htons(7890),
        .sin_addr.s_addr = 0
    });
    memset(host_addr->sin_zero, '\0', 8);

    printf("%d\n",*host_addr->sin_zero);
    /**
    memset(&host_addr, 0, sizeof(host_addr));
    host_addr->sin_family = AF_LOCAL;
    host_addr->sin_port = htons(7890);
    host_addr->sin_addr.s_addr = 0;
    */

    //free(host_addr);

    
	return 0;
}

#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h> 
#include <netinet/ip.h>
#include <netinet/udp.h>

#define SERVER_PORT 2000
#define IPV6 "fd15:4ba5:5a2b:1008:1bf0:f748:3884:6b52"

int main()
{
    int listen_sock;
    listen_sock = socket(AF_INET6,SOCK_DGRAM,0);
    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(opt));
    setsockopt(listen_sock, SOL_SOCKET, SO_RCVBUF, &opt, sizeof(opt));
    sockaddr_in6 server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(SERVER_PORT);
    inet_pton(AF_INET6, IPV6, &server_addr.sin6_addr);
    if(bind(listen_sock,(sockaddr*)&server_addr,sizeof(sockaddr_in6))<0)
    {
        perror("fail to bind");
        exit(-1);
    }

    sockaddr_in6 client_addr;
    socklen_t len = sizeof(sockaddr_in6);
    int socket;
    char buff[1024];
    printf("new client connect");
    {
        while(1)
        {
            recvfrom(listen_sock,buff,sizeof(buff),0,(sockaddr*)&client_addr,&len);
            printf("recv data from client:%s",buff);
        }
    }
}

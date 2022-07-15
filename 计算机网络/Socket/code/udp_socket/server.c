/*
 * @Author: Zhaojc
 * @Date: 2022-07-11 10:27:30
 * @LastEditTime: 2022-07-15 14:25:08
 * @Descripttion: UDP Socket Server
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    // 创建套接字
    int serv_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(serv_sock < 0)
	{
			printf("Socket fail\n");
			return 0;
	}

    // 给套接字绑定IP地址和端口地址
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(9999);  //端口
    int ret = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(ret < 0)
	{
			printf("bind fail\n");
			return 0;
	}

	while(1)
	{
		char buf[1024] = {0};
		struct sockaddr_in client_addr;
		int client_size = sizeof(client_addr);
		ret = recvfrom(serv_sock, buf, 1023, 0, (struct sockaddr*)&client_addr, &client_size);
		if(ret != -1)
		{
			printf("%s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			printf("Message: %s\n", buf);
			sendto(serv_sock, "Helle, i am server!", 1023, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
			close(serv_sock);
			return 0;
		}
	}
    return 0;
}
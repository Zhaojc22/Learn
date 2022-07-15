/*
 * @Author: Zhaojc
 * @Date: 2022-07-11 10:58:40
 * @LastEditTime: 2022-07-15 14:07:33
 * @Descripttion: TCP Socket Server
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    // 创建主套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serv_sock < 0)
    {
        printf("Socket Create Failed!\n");
        return 0;
    }
    // 绑定服务器本身的地址和端口
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(9421);
    int ret = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(ret < 0)
	{
		printf("Bind Failed\n");
		return 0;
	}

    // 绑定成功后，让套接字处于监听模式
    ret = listen(serv_sock, 20);
	if(ret < 0)
	{
		printf("ret fail\n");
		return 0;
	}

    // 创建一个新的套接字来存储连接的设备
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &client_addr_size);
	if(client_sock < 0)
	{
		printf("accept fail\n");
		return 0;
	}
	printf("accept success: %s:%d, and new_socket_addr is %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), client_sock);

    // 接收数据
	char buf[1024] = {0};
	ssize_t recv_size = recv(client_sock, buf, sizeof(buf)-1, 0);
	if(recv_size < 0)
	{
    	printf("recv failed");
    }
    printf("accrpt data is : %s\n", buf);
    
    // 回应客户端
	memset(buf,'\0',sizeof(buf));
    sprintf(buf,"hello client,i am server,i am %s:%d", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
    ssize_t send_ret = send(client_sock,buf,strlen(buf),0); 
    if(send_ret < 0)
    {
        printf("send failed\n");
    }

    // 关闭服务端套接字
    close(serv_sock);
    return 0;
}

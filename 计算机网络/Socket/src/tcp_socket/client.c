/*
 * @Author: Zhaojc
 * @Date: 2022-07-11 10:58:32
 * @LastEditTime: 2022-07-15 13:57:56
 * @Descripttion: TCP Sockt Client
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
    // 创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0)
    {
        printf("TCP socket failed\n");
        return 0;
    }
    // 绑定目的服务器地址和端口
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(9421);  //端口
    int ret = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret < 0)
    {
        printf("connnect failed\n");
        return 0;
    }

	// 发送消息
	char buf[1024] = {0};
	sprintf(buf,"hello server,i am client");
	ssize_t send_ret = send(sock,buf,strlen(buf),0); //发送
	if(send_ret < 0)
	{

		printf("Senf failed\n");
	}

	// 接收响应
	memset(buf, '\0', sizeof(buf));
	ssize_t recv_size = recv(sock, buf, sizeof(buf)-1, 0);
	if(recv_size < 0)
	{

		printf("Recv failed\n");
	}
	else
	{

		printf("Message from server: %s\n", buf);
	}

	// 关闭客户端套接字
	close(sock);

    return 0;
}
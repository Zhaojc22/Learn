/*
 * @Author: Zhaojc
 * @Date: 2022-07-11 10:27:37
 * @LastEditTime: 2022-07-15 14:03:42
 * @Descripttion: UDP Socket Client
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    //创建套接字,设置连接为UDP
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        printf("Socket Create Failed!\n");
        return 0;
    }
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(9999);  //端口
    int ret = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret < 0)
    {
        printf("Connect Failed!\n");
        return 0;
    }

    // 给服务端发消息
    char buf[1024];
    sprintf(buf,"Hello, i am client");
    ssize_t send_ret = send(sock,buf,strlen(buf),0); //发送
	if(send_ret < 0)
	{

		printf("Senf failed\n");
	}

    // 接收返回消息
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

    //关闭套接字
    close(sock);

    return 0;
}
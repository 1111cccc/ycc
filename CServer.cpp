#include<iostream>
#include<thread>
#include <unistd.h>
#include<arpa/inet.h>

using namespace std;

int main()
{
    //1、创建监听的套接字
    //socket()
    //第一个参数，通信模式：常用这三个（IPV4、IPV6、本地）（AF_INET、AF_INET6、AF_LOCAL）
    //第二个参数，通信类型：常用这两个（流式、暴式）（SOCK_STREAM、SOCK_DGRAM）
    //第三个参数，指定上述协议：选择流式，0表示TCP；选暴式，0表示UDP（一般为0）
    //成功返回套接字符，失败返回-1
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd ==-1)//判断创建是否成功
    {
        perror("socket");
        return -1;
    }
    //2、绑定本地的IP port
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);        //可以绑定本地任意IP
    //bind
    //绑定用于监听的套接字和本地IP端口，结构体中放IP和端口，最后一个参数是前面结构体内存大小
    //调用成功返回0，失败返回-1
    int ret = bind(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if(ret ==-1)                                     //判断绑定是否成功
    {
        perror("bind");
        return -1;
    }
    //3、设置监听
    ret = listen(fd, 128);                         //128为最大监听数
     if(ret ==-1)                                          //判断监听是否成功
    {
        perror("listen");
        return -1;
    }
    //4、阻塞并等待客户端连接
    struct sockaddr_in caddr;
    socklen_t addrlen = sizeof(caddr);
    
    //第二个数据，指明客户端方ip、和端口信息
    //第三个参数是指针，描述的是前面结构体指针指向的数据大小，然后修改这块内存的值
    //调用成功返回用于通信的文件描述符，失败返回-1
    //没有客户端连接的时候会阻塞
    //一个accept只能连接一个客户端
    int cfd = accept(fd, (struct sockaddr *)&caddr, &addrlen);
     if(cfd ==-1)                                          //判断监听是否成功
    {
        perror("accept");
        return -1;
    }
    //连接建立成功，通讯
    while(1)
    {
        //接受数据
        char buff[1024];

        //接受的数据，accept()函数的返回值
        //存到指向的有效内存
        //内存容量
        //标志位，一般为0
        //返回值大于0，实际接受的字节数；等于0，断开连接；小于0，接收失败
        int t = recv(cfd, buff, sizeof(buff), 0);
        cout << "客户端："<<buff << endl;
        //发回收到的数据
        send(cfd, buff, t, 0);
        cout << "服务器：" << buff << endl;
        sleep(1);
        
        
    }
    close(fd);
    close(cfd);
    return 0;
}

//客户端
//connect()
//同accept参数

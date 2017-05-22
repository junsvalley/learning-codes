
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h> //互联网地址族
#include <arpa/inet.h>
#include <netdb.h>

#include <ctype.h> //toupper （小写转化为大写）

int port =8000;

/*服务端*/
int main(int argc, char** argv) {

    struct sockaddr_in sin;//struct sockaddr和struct sockaddr_in这两个结构体用来处理网络通信的地址。
    struct sockaddr_in pin;
    int sock_descriptor;//  套接口描述字
    int temp_sock_descriptor;
    int address_size;
    char buf[16384];// 缓冲区大小

    int i,len;

    /*
     *int socket(int domain, int type, int protocol);
     * PF_INET, AF_INET： Ipv4网络协议
     * PF_INET6, AF_INET6： Ipv6网络协议。
     * type参数的作用是设置通信的协议类型，可能的取值如下所示：
　　      SOCK_STREAM： 提供面向连接的稳定数据传输，即TCP协议。
　　      OOB： 在所有数据传送前必须使用connect()来建立连接状态。
　      　SOCK_DGRAM： 使用不连续不可靠的数据包连接。
　　      SOCK_SEQPACKET： 提供连续可靠的数据包连接。
　      　SOCK_RAW： 提供原始网络协议存取。
　      　SOCK_RDM： 提供可靠的数据包连接。
　　      SOCK_PACKET： 与网络驱动程序直接通信。
     */
    //socket函数，向系统申请一个通信端口
    sock_descriptor=socket(AF_INET,SOCK_STREAM,0);//IPV4 TCP协议
    if(sock_descriptor== -1)//申请失败
    {
        perror("call to socket");
        exit(1);
    }

    bzero(&sin,sizeof(sin));// 初始化 然后是设置套接字
    sin.sin_family = AF_INET;//协议族，在socket编程中只能是AF_INET(TCP/IP协议族)
    sin.sin_addr.s_addr=INADDR_ANY;//sin_addr存储IP地址,使用in_addr这个数据结构
                                  //s_addr按照网络字节顺序存储IP地址
                                   //in_addr32位的IPv4地址
    sin.sin_port=htons(port);//存储端口号

      //将套接字（sin） 跟端口（sock_descriptor）链接
    if(bind(sock_descriptor,(struct sockaddr *)&sin,sizeof(sin)) ==-1)
    {
        perror("call to bind");
        exit(1);
    }
    /*int PASCAL FAR listen( SOCKET s, int backlog);
　　     S：用于标识一个已捆绑未连接套接口的描述字。
　　     backlog：等待连接队列的最大长度。
     * listen()仅适用于支持连接的套接口，如SOCK_STREAM类型的。
     */
    if(listen(sock_descriptor,20) == -1) //在端口sock_descriptor监听
    {
        perror("call to listen");
        exit(1);
    }

    printf("accepting connections \n");

    while(1)
    {   //用来监听的端口sock_descriptor
        temp_sock_descriptor = accept(sock_descriptor,(struct sockaddr *)&pin, &address_size);
        if(temp_sock_descriptor== -1)
        {
           perror("call to accept");
           exit(1);
        }

        /*int PASCAL FAR recv( SOCKET s, char FAR* buf, int len, int flags);
　　        s：一个标识已连接套接口的描述字。
　　        buf：用于接收数据的缓冲区。
　　        len：缓冲区长度。
　　        flags：指定调用方式。
         */

        if(recv(temp_sock_descriptor,buf,16384,0) ==-1)
        {
            perror("call to recv");
            exit(1);
        }

        printf("received from client:%s\n",buf);

        len =strlen(buf);
        for(i=0;i<len;i++)
        {
            buf[i]= toupper(buf[i]);//将小写字母转化为大写字母
        }
        /*int PASCAL FAR send( SOCKET s, const char FAR* buf, int len, int flags);
　　        s：一个用于标识已连接套接口的描述字。
　　        buf：包含待发送数据的缓冲区。
　　        len：缓冲区中数据的长度。
　　        flags：调用执行方式。*/
        
        /*send()   基于链接的发送 TCP
         *sendto() 基于无链接到   UDP
         */
        
        if(send(temp_sock_descriptor,buf,len,0) == -1)
        {
            perror("call to send");
            exit(1);
        }

        close(temp_sock_descriptor);

    }

    return (EXIT_SUCCESS);
}


客户端：

#include <stdio.h>
#include <stdlib.h>

#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
/*客户端*/
char *host_name ="127.0.0.1";//需要搜寻服务端IP地址
int port = 8000;

/*argc: 整数,用来统计你运行程序时送给main函数的命令行参数的个数
 * argv: 字符串数组，用来存放指向你的字符串参数的指针数组，每一个元素指向一个参数
　　argv[0] 指向程序运行的全路径名
　　argv[1] 指向在DOS命令行中执行程序名后的第一个字符串
　　argv[2] 指向执行程序名后的第二个字符串
   */
int main(int argc, char** argv) {
    char buf[8192];
    char message[256];
    int socket_descriptor;
    struct sockaddr_in pin;//处理网络通信的地址
    /*
     * hostent记录主机的信息，包括主机名、别名、地址类型、地址长度和地址列表
     * struct hostent {
　　       char *h_name;地址的正式名称
　　       char **h_aliases;空字节-地址的预备名称的指针
　　       int h_addrtype;地址类型; 通常是AF_INET。
　       　int h_length;地址的比特长度。
　       　char **h_addr_list;零字节-主机网络地址指针。网络字节顺序。
　　    };
　　   #define h_addr h_addr_list[0] //h_addr_list中的第一地址
     */
    struct hostent *server_host_name;

    char *str = "A default test string";

    if(argc<2)//运行程序时送给main函数到命令行参数个数
    {
        printf("Usage:test \"Any test string\"\n");
        printf("we will send a default test string. \n");
    }
    else
    {
        str =argv[1];
    }
    /*
     * gethostbyname()返回对应于给定主机名的包含主机名字和地址信息的
     * hostent结构指针。结构的声明与gethostaddr()中一致。*/
    if((server_host_name = gethostbyname(host_name))==0)
    {
        perror("Error resolving local host \n");
        exit(1);
    }

    bzero(&pin,sizeof(pin));
    pin.sin_family =AF_INET;
                          //htonl()将主机的无符号长整形数转换成网络字节顺序
    pin.sin_addr.s_addr=htonl(INADDR_ANY);//s_addr按照网络字节顺序存储IP地址
                      //in_addr 32位的IPv4地址  h_addr_list中的第一地址
    pin.sin_addr.s_addr=((struct in_addr *)(server_host_name->h_addr))->s_addr;// 跟书上不一样 必须是h_addr

    pin.sin_port=htons(port);
    /*申请一个通信端口*/
    if((socket_descriptor =socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("Error opening socket \n");
        exit(1);
    }
     //pin 定义跟服务端连接的 IP 端口
    if(connect(socket_descriptor,(void *)&pin,sizeof(pin))==-1)
    {
        perror("Error connecting to socket \n"); ////
        exit(1);
    }
    printf("Sending message %s to server \n",str);

    if(send(socket_descriptor,str,strlen(str),0) == -1)
    {
        perror("Error in send\n");
        exit(1);
    }

    printf("..sent message.. wait for response...\n");

    if(recv(socket_descriptor,buf,8192,0) == -1)
    {
        perror("Error in receiving response from server \n");
        exit(1);
    }

    printf("\n Response from server:\n\n%s\n",buf);

    close(socket_descriptor);

    return (EXIT_SUCCESS);
}

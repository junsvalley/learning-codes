
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h> //��������ַ��
#include <arpa/inet.h>
#include <netdb.h>

#include <ctype.h> //toupper ��Сдת��Ϊ��д��

int port =8000;

/*�����*/
int main(int argc, char** argv) {

    struct sockaddr_in sin;//struct sockaddr��struct sockaddr_in�������ṹ��������������ͨ�ŵĵ�ַ��
    struct sockaddr_in pin;
    int sock_descriptor;//  �׽ӿ�������
    int temp_sock_descriptor;
    int address_size;
    char buf[16384];// ��������С

    int i,len;

    /*
     *int socket(int domain, int type, int protocol);
     * PF_INET, AF_INET�� Ipv4����Э��
     * PF_INET6, AF_INET6�� Ipv6����Э�顣
     * type����������������ͨ�ŵ�Э�����ͣ����ܵ�ȡֵ������ʾ��
����      SOCK_STREAM�� �ṩ�������ӵ��ȶ����ݴ��䣬��TCPЭ�顣
����      OOB�� ���������ݴ���ǰ����ʹ��connect()����������״̬��
��      ��SOCK_DGRAM�� ʹ�ò��������ɿ������ݰ����ӡ�
����      SOCK_SEQPACKET�� �ṩ�����ɿ������ݰ����ӡ�
��      ��SOCK_RAW�� �ṩԭʼ����Э���ȡ��
��      ��SOCK_RDM�� �ṩ�ɿ������ݰ����ӡ�
����      SOCK_PACKET�� ��������������ֱ��ͨ�š�
     */
    //socket��������ϵͳ����һ��ͨ�Ŷ˿�
    sock_descriptor=socket(AF_INET,SOCK_STREAM,0);//IPV4 TCPЭ��
    if(sock_descriptor== -1)//����ʧ��
    {
        perror("call to socket");
        exit(1);
    }

    bzero(&sin,sizeof(sin));// ��ʼ�� Ȼ���������׽���
    sin.sin_family = AF_INET;//Э���壬��socket�����ֻ����AF_INET(TCP/IPЭ����)
    sin.sin_addr.s_addr=INADDR_ANY;//sin_addr�洢IP��ַ,ʹ��in_addr������ݽṹ
                                  //s_addr���������ֽ�˳��洢IP��ַ
                                   //in_addr32λ��IPv4��ַ
    sin.sin_port=htons(port);//�洢�˿ں�

      //���׽��֣�sin�� ���˿ڣ�sock_descriptor������
    if(bind(sock_descriptor,(struct sockaddr *)&sin,sizeof(sin)) ==-1)
    {
        perror("call to bind");
        exit(1);
    }
    /*int PASCAL FAR listen( SOCKET s, int backlog);
����     S�����ڱ�ʶһ��������δ�����׽ӿڵ������֡�
����     backlog���ȴ����Ӷ��е���󳤶ȡ�
     * listen()��������֧�����ӵ��׽ӿڣ���SOCK_STREAM���͵ġ�
     */
    if(listen(sock_descriptor,20) == -1) //�ڶ˿�sock_descriptor����
    {
        perror("call to listen");
        exit(1);
    }

    printf("accepting connections \n");

    while(1)
    {   //���������Ķ˿�sock_descriptor
        temp_sock_descriptor = accept(sock_descriptor,(struct sockaddr *)&pin, &address_size);
        if(temp_sock_descriptor== -1)
        {
           perror("call to accept");
           exit(1);
        }

        /*int PASCAL FAR recv( SOCKET s, char FAR* buf, int len, int flags);
����        s��һ����ʶ�������׽ӿڵ������֡�
����        buf�����ڽ������ݵĻ�������
����        len�����������ȡ�
����        flags��ָ�����÷�ʽ��
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
            buf[i]= toupper(buf[i]);//��Сд��ĸת��Ϊ��д��ĸ
        }
        /*int PASCAL FAR send( SOCKET s, const char FAR* buf, int len, int flags);
����        s��һ�����ڱ�ʶ�������׽ӿڵ������֡�
����        buf���������������ݵĻ�������
����        len�������������ݵĳ��ȡ�
����        flags������ִ�з�ʽ��*/
        
        /*send()   �������ӵķ��� TCP
         *sendto() ���������ӵ�   UDP
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


�ͻ��ˣ�

#include <stdio.h>
#include <stdlib.h>

#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
/*�ͻ���*/
char *host_name ="127.0.0.1";//��Ҫ��Ѱ�����IP��ַ
int port = 8000;

/*argc: ����,����ͳ�������г���ʱ�͸�main�����������в����ĸ���
 * argv: �ַ������飬�������ָ������ַ���������ָ�����飬ÿһ��Ԫ��ָ��һ������
����argv[0] ָ��������е�ȫ·����
����argv[1] ָ����DOS��������ִ�г�������ĵ�һ���ַ���
����argv[2] ָ��ִ�г�������ĵڶ����ַ���
   */
int main(int argc, char** argv) {
    char buf[8192];
    char message[256];
    int socket_descriptor;
    struct sockaddr_in pin;//��������ͨ�ŵĵ�ַ
    /*
     * hostent��¼��������Ϣ����������������������ַ���͡���ַ���Ⱥ͵�ַ�б�
     * struct hostent {
����       char *h_name;��ַ����ʽ����
����       char **h_aliases;���ֽ�-��ַ��Ԥ�����Ƶ�ָ��
����       int h_addrtype;��ַ����; ͨ����AF_INET��
��       ��int h_length;��ַ�ı��س��ȡ�
��       ��char **h_addr_list;���ֽ�-���������ַָ�롣�����ֽ�˳��
����    };
����   #define h_addr h_addr_list[0] //h_addr_list�еĵ�һ��ַ
     */
    struct hostent *server_host_name;

    char *str = "A default test string";

    if(argc<2)//���г���ʱ�͸�main�����������в�������
    {
        printf("Usage:test \"Any test string\"\n");
        printf("we will send a default test string. \n");
    }
    else
    {
        str =argv[1];
    }
    /*
     * gethostbyname()���ض�Ӧ�ڸ����������İ����������ֺ͵�ַ��Ϣ��
     * hostent�ṹָ�롣�ṹ��������gethostaddr()��һ�¡�*/
    if((server_host_name = gethostbyname(host_name))==0)
    {
        perror("Error resolving local host \n");
        exit(1);
    }

    bzero(&pin,sizeof(pin));
    pin.sin_family =AF_INET;
                          //htonl()���������޷��ų�������ת���������ֽ�˳��
    pin.sin_addr.s_addr=htonl(INADDR_ANY);//s_addr���������ֽ�˳��洢IP��ַ
                      //in_addr 32λ��IPv4��ַ  h_addr_list�еĵ�һ��ַ
    pin.sin_addr.s_addr=((struct in_addr *)(server_host_name->h_addr))->s_addr;// �����ϲ�һ�� ������h_addr

    pin.sin_port=htons(port);
    /*����һ��ͨ�Ŷ˿�*/
    if((socket_descriptor =socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("Error opening socket \n");
        exit(1);
    }
     //pin �������������ӵ� IP �˿�
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

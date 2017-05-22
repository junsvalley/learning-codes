#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct isa_msg{
    int isa_id;
    char isa_name[64];
    int data;
};

struct quemsg{
    long msgtype;
    struct isa_msg isa;
};

#define ISA_TYPE 0xF0F0

int main()
{
    struct quemsg mmsg; 
    mmsg.msgtype = ISA_TYPE;
    struct isa_msg *isa_data = &mmsg.isa; 

    key_t k = ftok("/home/gufeng/codes/process/msgqueue", 'a');
    int msgid = msgget(k, IPC_CREAT | IPC_NOWAIT | 0666);
    if(msgid<0) fprintf(stderr, "msgget failure!!!\n");

    printf("key is %d message id is %d\n", k, msgid);

    char buf[100]={0};
    int idx=0;
    while(1)
    {
	switch(idx % 3)
	{
	    case 0:
                memset(isa_data, 0, sizeof(struct isa_msg));
		fputs("isa id<int> = ", stdout);
		fgets(buf, 100, stdin);
		isa_data->isa_id = atoi(buf); 
                break;
	    case 1:
		fputs("isa name<string> = ", stdout);
		fgets(buf, 100, stdin);
                strcpy(isa_data->isa_name, buf);
                break;
	    case 2:
		fputs("isa data<int> = ", stdout);
		fgets(buf, 100, stdin);
		isa_data->data = atoi(buf); 
                msgsnd(msgid, (void*)&mmsg, sizeof(struct isa_msg), IPC_NOWAIT);
                break;
            default:
                break;
	}
        idx++;
    }

    msgctl(msgid, IPC_RMID, NULL); //delete the msg queue
    return 0;
}



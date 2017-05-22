#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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
    key_t k = ftok("/home/gufeng/codes/process/msgqueue", 'a');
    int msgid = msgget(k, IPC_CREAT | IPC_NOWAIT | 0666);
    if(msgid<0) fprintf(stderr, "msgget failure!!!\n");

    printf("key is %d message id is %d\n", k, msgid);

    char buf[100]={0};
    int idx=0;
    while(1)
    {
        if(msgrcv(msgid, (void*)&mmsg, sizeof(struct isa_msg), ISA_TYPE, MSG_NOERROR)<0) {
            fprintf(stderr, "ERROR %s\n", strerror(errno));
        } else {
            printf("received isa msg: \n  - id=%d\n  - name=%s  - data=%d\n",
                mmsg.isa.isa_id, mmsg.isa.isa_name, mmsg.isa.data);
        }
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}



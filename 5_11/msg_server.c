#include<stdio.h>
#include<unistd.h>
#include<sys/msg.h>

#define MSQKEY 51234

struct msgbuf{
    long mtype; // 메시지 타입: 0 이상의 정수값
    char mtext[BUFSIZ]; // 메시지내용: 1바이트 이상의 문자열
};

int main(int argc, char **argv){

    key_t key;
    int n, msqid;
    struct msgbuf mb;

    key = MSQKEY;

    if((msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666)) < 0){
        perror("msgget()");
        return -1;
    }

    // 메시지 큐에서 데이터를 가져온다.
    while((n = msgrcv(msqid, &mb, sizeof(mb), 0, 0)) >0){
        switch(mb.mtype){
            // 메시지 타입이 1이면 화면에 가져온 데이터를 출력한다.
            case 1:
                write(1, mb.mtext,n);
                break;
            // 메시지 타입이 2이면 메시지 큐의 채널을 삭제한다.
            case 2:
                if(msgctl(msqid, IPC_RMID, (struct msqid_ds *) 0)<0){ //이거 왜 이렇게 쓴거지? (struct msqid_ds *) 0 왜 이렇게 NULL을 넣는걸까
                    perror("msgctl()"); 
                    return -1;
                }
                break;
        }
    }

    return 0;
}
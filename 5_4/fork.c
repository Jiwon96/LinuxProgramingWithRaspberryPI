#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
static int g_var = 1;
char str[] = "PID";

int main(int argc, char ** argv){

    int var; // 지역변수는 스택
    pid_t pid;
    var =92;    

    if((pid=fork()) < 0){
        perror("[ERROR]:fork()");
    }else if(pid==0){ // 자식프로세스면
        g_var++;
        var++;
        printf("Parent %s from Child Process(%d): %d\n", str, getpid(), getppid());
    }else{ //부모프로세스이면
        printf("Child %s from Parent Process(%d): %d\n",str,getpid(), pid);
        sleep(1);
    }

    printf("pid =%d, Global var = %d, var = %d\n", getpid(), g_var, var);

    return 0;
}
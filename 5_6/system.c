#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>

int system(const char *cmd){ //문자열 상수
    pid_t pid;
    int status;

    if((pid = fork()) <0){ //fork 에러 시
        status = -1;
    }else if(pid == 0){ //자식
        execl("/bin/sh", "sh", "-c", cmd, (char *)0);
        _exit(127);
    }else{ // 부모
        while(waitpid(pid, &status, 0)<0){
            if(errno != EINTR){ // waitpid() 함수에서 EINTR이 아닌 경우 처리 ?
                status =-1;
                break;
            }
        }
    }
    return status;
}

int main(int argc, char **argv, char **envp){
    while (*envp)
    {
        printf("%s \n", *envp++);
    }
    system("who");
    system("nocommand");
    system("cal");
    return 0;
}
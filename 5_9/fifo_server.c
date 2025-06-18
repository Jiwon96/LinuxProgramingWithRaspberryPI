#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#define FIFOFILE "fifo"

int main(int argc, char **argv){
    int n, fd;
    char buf[BUFSIZ]; // bufsiz는 stdio에 정의되어있음

    unlink(FIFOFILE); // 기존의 FIFO 파일 삭제

    if(mkfifo(FIFOFILE, 0666)<0){ // FIFO 파일 생성
        perror("mkfifo()");
        return -1;
    }

    if((fd=open(FIFOFILE, O_RDONLY)) <0){ // FIFO 오픈
        perror("open()");
        return -1;
    }

    while((n = read(fd, buf, sizeof(buf))) > 0){
        printf("%s", buf);
    }

    close(fd);
    return 0;
}
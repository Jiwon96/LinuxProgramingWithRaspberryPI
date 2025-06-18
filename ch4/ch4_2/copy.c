#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/stat.h> // open 함수
#include<sys/types.h> //open 함수

int main(int argc, char **argv){
    int n, in, out;
    char buf[1024];
    if(argc <3){
        write(2, "Usage: copy file1 file2\n", 25); // 표준 출력(기본은 모니터에 연결됨)
        return -1;
    }
    // 복사 원본이 되는 파일을 읽기 모드로 연다
    if((in = open(argv[1], O_RDONLY))<0){
        perror(argv[1]);
        return -1;
    }

    if((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0){
        perror(argv[2]);
        return -1;
    }

    // 원본 파일을 읽어서 
    while((n=read(in, buf, sizeof(buf))) >0){
        write(out, buf, n);
    }
    close(out);
    close(in);

    return 0;
}

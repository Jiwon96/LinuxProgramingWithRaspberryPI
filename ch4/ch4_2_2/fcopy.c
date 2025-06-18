#include<stdio.h>

int main(int argc, char **argv){
    int n;
    FILE *in, *out;
    char buf[BUFSIZ];

    if(argc != 3){
        fprintf(stderr, "Usage: fcopy file1 file2\n");
        return -1;
    }

    if((in = fopen(argv[1], "r")) == NULL){
        perror(argv[1]);
        return -1;
    }


    // 복사할 결과 파일을 쓰기 모드로 연다.
    if((out = fopen(argv[2], "w")) == NULL){
        perror(argv[2]);
        return -1;
    }

    // 원본 파일에서 파일 내용을 읽어서 복사할 파일에 쓴다.
    while((n = fread(buf, sizeof(char), BUFSIZ, in))>0){
        fwrite(buf, sizeof(char), n, out);
    }
    fclose(out);
    fclose(in);

    return 0;
}
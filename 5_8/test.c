#include <stdio.h>
#include <unistd.h>

int main() {
    int pfd[2];
    pipe(pfd);
    
    printf("dup2 호출 전: 터미널에 출력\n");
    
    dup2(pfd[1], 1);  // 표준출력을 파이프로 리다이렉션
    
    printf("dup2 호출 후: 이 메시지는 터미널에 안 보임!\n");
    // 이 printf 출력은 파이프 버퍼로 들어감
    
    return 0;
}
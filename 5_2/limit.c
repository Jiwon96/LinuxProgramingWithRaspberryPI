#include <sys/time.h>
#include<sys/resource.h>
#include<stdio.h>

int main(){

    struct rlimit rlim;

    getrlimit(RLIMIT_NPROC, &rlim);
    printf("max user processes : %lu / %lu\n",
        rlim.rlim_cur, rlim.rlim_max
    );

    getrlimit(RLIMIT_NOFILE, &rlim);
    printf("file size: %lu / %lu \n", rlim.rlim_cur, rlim.rlim_max);


    // 메모리 설정 가져오기
    getrlimit(RLIMIT_RSS, &rlim);
    printf("max memory size : %lu, %lu\n", rlim.rlim_cur, rlim.rlim_max);

    // 초 단위 CPU 시간
    getrlimit(RLIMIT_CPU, &rlim);
    if(rlim.rlim_cur == RLIM_INFINITY){ // 무한 사용 가능이면
        printf("cpu time : UNLIMIT\n");
    }

    return 0;
}
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h> // terminal io interfaces, terminal: monitor, keyboard or etc. => devices

int kbhit(){
    struct termios oldt, newt;
    int ch, oldf;

    tcgetattr(0, &oldt); // 현재 터미널에서 표준 입력에 대한 설정된 정보를 가져온다.
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // 정규모드(줄단위 입력)비활성화-> 문자단위로 즉시 입력 처리 | 입력된 문자를 화면에 표시하지 않음.
    tcsetattr(0, TCSANOW, &newt); // 새로운 값으로 터미널 설정
    oldf = fcntl(0, F_GETFL, 0);
    
    fcntl(0, F_SETFL, oldf | O_NONBLOCK); // NON Blocking 모드로 바꿈.
    ch=getchar();

    tcsetattr(0, TCSANOW, &oldt); // change attributes immediately
    fcntl(0, F_SETFL, oldf);
    if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int main(int argc, char **argv){
    int i=0;
    for(int i=0; ; i++){
        if(kbhit()){
            switch(getchar()){
                case 'q':
                    goto END;
                    break;
            }
        }
        printf("%20d\t\t\r", i);
        usleep(100);
    }
    END:
    printf("Good Bye!! \n");
    return 0;
}
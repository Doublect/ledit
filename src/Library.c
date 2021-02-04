#include<unistd.h> //STDOUt_FILENO, write

//Defined in features.h (<- unistd.h)
//#define __USE_POSIX199309
//#define _POSIX_C_SOURCE 199309L

//#ifdef WIN32
//#include <windows.h>
//#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
//#else
//#include <unistd.h> // for usleep
//#endif

//https://stackoverflow.com/a/28827188
void msleep(int milliseconds){ // cross-platform sleep function
//#ifdef WIN32
//    Sleep(milliseconds);
//#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
//#else
//    if (milliseconds >= 1000)
//      sleep(milliseconds / 1000);
//    usleep((milliseconds % 1000) * 1000);
//#endif
}


//Print null-terminated string
void strprint(char * str){
    for(; *str; str++){
        write(STDOUT_FILENO, str, 1);
    }
}

int isNumber(char c){
    if(c >= '0' && c <= '9'){
        return 0;
    }
    return 1;
}

//Limited to size 10, because of int
int strtoint(char *str){
    int ans = 0;
    for(int i = 0; i < 10 && *str; str++, i++){
        if(isNumber(*str) == 0){
            ans *= 10;
            ans += *str - '0';
        }
    }
    return ans;
}

//Returns the number of digits in an int
int intsize(int x){
    if(x < 0) x *= -1;

    if(x < 10) return 1;
    if(x < 100) return 2;
    if(x < 1000) return 3;
    if(x < 10000) return 4;
    if(x < 100000) return 5;
    if(x < 1000000) return 6;
    if(x < 10000000) return 7;
    if(x < 100000000) return 8;
    if(x < 1000000000) return 9;

    return 10;
}


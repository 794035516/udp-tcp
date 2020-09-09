#ifndef CONSOLE_ERROR_CPP
#define CONSOLE_ERROR_CPP


#include<iostream>
#include<thread>
#include<cstring>

namespace CONSOLE_ERROR{

    #define SELF_ADDR "127.0.0.1"
    #define MAXSIZE 1024

    void error_print(int num,const char* str){
        if(num < 0){
            perror(str);
            exit(-1);
        }
    }

}


#endif

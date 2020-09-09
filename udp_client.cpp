#ifndef UDP_CLIENT_CPP
#define UDP_CLIENT_CPP
#pragma once

#include<cstdio>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<error.h>
#include<cstdlib>
#include<cstring>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<thread>
#include"udp_server.cpp"
#include"console_error.cpp"

namespace UDP_CLIENT{

    #define MAXSIZE 1024
    #define ADDR "127.0.0.1"
    static int times = 0;

    int _tmain(){
        int sock_fd = socket(AF_INET,SOCK_DGRAM,0);
        int on = 1;
        CONSOLE_ERROR::error_print(sock_fd,"udp client socket error");
        int set_sock_fd_addrreuse = setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
        CONSOLE_ERROR::error_print(set_sock_fd_addrreuse,"udp client set reuse addr error");
        char send_buf[MAXSIZE] = "hey,i am udp client,who are you";
        int send_len = strlen(send_buf);
        snprintf(send_buf + send_len,sizeof(send_buf)," ,times :%d",++times);
        char recv_buf[MAXSIZE];
        memset(recv_buf,0,sizeof(recv_buf));
        struct sockaddr_in addr_serv;
        addr_serv.sin_port = htons(UDP_SERVER::port);
        addr_serv.sin_addr.s_addr = inet_addr(ADDR);
        addr_serv.sin_family = AF_INET;

        int send_to_num = sendto(sock_fd,send_buf,sizeof(send_buf),0,(struct sockaddr*)&addr_serv,sizeof(addr_serv));
        CONSOLE_ERROR::error_print(send_to_num,"udp client send error");
        std::cout<<"udp client send :"<<send_buf<<std::endl;
        int len = sizeof(addr_serv);
        int recv_from_num = recvfrom(sock_fd,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&addr_serv,(socklen_t*)&len);
        CONSOLE_ERROR::error_print(recv_from_num,"udp client recv error");
        std::cout<<"udp client recv :"<<recv_buf<<std::endl;
        return 0;
    }

    void thread_run(){
        std::thread t1(_tmain);
        if(!t1.joinable()){
            std::cout<<"udp client thread can not join"<<std::endl;
            exit(-1);
        }else{
            t1.join();
        }

    }
}

#endif


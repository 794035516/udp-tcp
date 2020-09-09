#ifndef TCP_CLIENT_CPP
#define TCP_CLIENT_CPP
#pragma once

#include<iostream>
#include<cstdio>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<error.h>
#include"tcp_server.cpp"
#include"console_error.cpp"

namespace TCP_CLENT{
#define ADDR "127.0.0.1"
#define MAXSIZE 1024
static int times = 0;

    void _tmain(){
        int sock_fd = socket(AF_INET,SOCK_STREAM,0);
        CONSOLE_ERROR::error_print(sock_fd,"tcp client socket error");
        int on = 1;
        int setsockoptnum = setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
        CONSOLE_ERROR::error_print(setsockoptnum,"tcp client reuse addr error");
        struct sockaddr_in addr_serv;
        memset(&addr_serv,0,sizeof(addr_serv));
        addr_serv.sin_family = AF_INET;
        addr_serv.sin_addr.s_addr = inet_addr(ADDR);
        addr_serv.sin_port = htons(TCP_SERVER::port);
        int sock_conn = connect(sock_fd,(struct sockaddr*)&addr_serv,sizeof(addr_serv));
        CONSOLE_ERROR::error_print(sock_conn,"tcp client connect error");
        char send_buf[MAXSIZE] = "hey,i am tcp client,who are you";
        char recv_buf[MAXSIZE];
        memset(recv_buf,0,sizeof(recv_buf));
        int send_num = send(sock_fd,send_buf,sizeof(send_buf),0);
        CONSOLE_ERROR::error_print(send_num,"tcp client send error");
        std::cout<<"tcp client send: "<<send_buf<<std::endl;
        int recv_num = recv(sock_fd,recv_buf,sizeof(recv_buf),0);
        snprintf(recv_buf + strlen(recv_buf),sizeof(recv_buf),", times:%d",times);
        CONSOLE_ERROR::error_print(recv_num,"tcp client recv error");
        std::cout<<"tcp client recv: "<<recv_buf<<std::endl;
        close(sock_fd);
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

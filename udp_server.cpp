#ifndef UDP_SERVER_CPP
#define UDP_SERVER_CPP
#pragma once

#include<cstdio>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<error.h>
#include<cstring>
#include<cstdlib>
#include<unistd.h>
#include<thread>
#include"console_error.cpp"

namespace UDP_SERVER{
    static int port = 6001;

    int _tmain(){
        int sock_fd = socket(AF_INET,SOCK_DGRAM,0);
        if(sock_fd < 0){
            perror("udp server socket error");
            exit(-1);
        }
        struct sockaddr_in addr_serv;
        addr_serv.sin_family = AF_INET;
        addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
        addr_serv.sin_port = htons(port);
        int on = 1;
        int set_reuse_num = setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
        CONSOLE_ERROR::error_print(set_reuse_num,"udp server reuse addr error");
        int sock_bind = bind(sock_fd,(struct sockaddr*)&addr_serv,sizeof(addr_serv));
        CONSOLE_ERROR::error_print(sock_bind,"udp server bind error");
        struct sockaddr_in addr_client;
        char send_buf[100] = "i am server";
        char recv_buf[100];
        std::cout<<"udp server wait..."<<std::endl;
        while(1){
            memset(&addr_client,0,sizeof(addr_client));
            memset(recv_buf,0,sizeof(recv_buf));
            int len = sizeof(addr_client);
            int recv_from_num = recvfrom(sock_fd,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&addr_client,(socklen_t*)(&len));
            CONSOLE_ERROR::error_print(recv_from_num,"udp server recvfrom error");
            int send_to_num = sendto(sock_fd,send_buf,sizeof(send_buf),0,(struct sockaddr*)&addr_client,len);
            CONSOLE_ERROR::error_print(send_to_num,"udp server sendto error");
        }
        close(sock_fd);
        return 0;
    }

    void thread_run(){
        std::thread t1(_tmain);
        if(!t1.joinable()){
            std::cout<<"udp server thread can not join"<<std::endl;
            exit(-1);
        }else{
            t1.detach();
        }
    }
}

#endif

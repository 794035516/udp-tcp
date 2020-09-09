#ifndef TCP_SERVER_CPP
#define TCP_SERVER_CPP

#include<iostream>
#include<cstdio>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<error.h>
#include<cstring>
#include"console_error.cpp"
namespace TCP_SERVER{

#define MAXSIZE 1024
static int port = 3001;

    void _tmain(){
        int sock_fd = socket(AF_INET,SOCK_STREAM,0);
        std::string s = "tcp server socket error";
        CONSOLE_ERROR::error_print(sock_fd,s.c_str());
        int on = 1;
        int set_sock_opt_num = setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
        CONSOLE_ERROR::error_print(set_sock_opt_num,"tcp server addr reuse error");
        struct sockaddr_in addr_serv;
        memset(&addr_serv,0,sizeof(addr_serv));
        addr_serv.sin_family = AF_INET;
        addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
        addr_serv.sin_port = htons(++port);
        int sock_bind = bind(sock_fd,(struct sockaddr*)&addr_serv,sizeof(addr_serv));
        CONSOLE_ERROR::error_print(sock_bind,"tcp server bind error");
        int sock_listen = listen(sock_fd,10);
        CONSOLE_ERROR::error_print(sock_listen,"tcp server listen error");
        std::cout<<"tcp server wait---"<<std::endl;
        char recv_buf[MAXSIZE];
        char send_buf[MAXSIZE] = "hey,i am tcp server,who are you";
        while(1){
            struct sockaddr_in addr_client;
            memset(recv_buf,0,sizeof(recv_buf));
            memset(&addr_client,0,sizeof(addr_client));
            int len = sizeof(addr_client);
            int sock_accept = accept(sock_fd,(struct sockaddr*)&addr_client,(socklen_t*)&len);
            CONSOLE_ERROR::error_print(sock_accept,"tcp server accept error");
            int recv_num = recv(sock_accept,recv_buf,sizeof(recv_buf),0);
            CONSOLE_ERROR::error_print(recv_num,"tcp server recv error");
            int send_num = send(sock_accept,send_buf,sizeof(send_buf),0);
            CONSOLE_ERROR::error_print(send_num,"tcp server send error");
            close(sock_accept);
        }
        close(sock_fd);
        return;
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

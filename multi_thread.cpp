#ifndef MULTI_THREAD_CPP
#define MULTI_THREAD_CPP
#pragma once

#include<iostream>
#include<cstdio>
#include<thread>
#include<mutex>
#include"console_error.cpp"

namespace MULTI_THREAD{

    unsigned long num = 0;

    void thread_run(unsigned long* num){
        std::mutex mtx;
        mtx.lock();
        for(int i = 0;i < 1000000;i++){
            (*num)++;
        }
        mtx.unlock();
        std::cout<<*num<<std::endl;
    }

    int _tmain(){
        std::thread t1(thread_run,&num);
        std::thread t2(thread_run,&num);
        std::thread t3(thread_run,&num);
        std::thread t4(thread_run,&num);
        if(!t1.joinable()){
            std::cout<<"t1 can not join"<<std::endl;
        }else{
            t1.join();
        }
        if(!t2.joinable()){
            std::cout<<"t2 can not join"<<std::endl;
        }else{
            t2.join();
        }
        if(!t3.joinable()){
            std::cout<<"t3 can not join"<<std::endl;
        }else{
            t3.join();
        }
        if(!t4.joinable()){
            std::cout<<"t4 can not join"<<std::endl;
        }else{
            t4.join();
        }
    return 0;
    }

}

#endif

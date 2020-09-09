#ifndef MEMPOOL_MY_CPP
#define MEMPOOL_MY_CPP
#pragma once

#include<iostream>
#include"mempool_my.h"
#include<cstdio>
#include<cstdio>
namespace MEM_POOL{

class object{

private:
    int data;

public:
    object(int m_data):data(m_data){}

    int getData(){
        return data;
    }

    void setData(int m_data){
        data = m_data;
    }

    void* operator new(size_t num);
    void operator delete(void* block);
    ~object(){}
};



mempool<sizeof(object)>object_pool;

void* object::operator new(size_t num){
    std::cout<<"new"<<std::endl;
    void* p = object_pool.allocate();
    std::cout<<p<<" -- "<<std::endl;
    return p;
}

void object::operator delete(void* block){
    object_pool.deallocate(block);
}

int _tmain(){
    perror("mempool begin");
    object* a = new object(1);
    std::cout<<a<<" -a "<<a->getData()<<std::endl;
    object* b = new object(2);
    std::cout<<b<<" -b "<<std::endl;
    delete b;
    perror("delete one block");
    object* c = new object(3);
    std::cout<<c<<" -c "<<std::endl;
    object* d = new object(4);
    std::cout<<d<<" -d "<<std::endl;
    std::cout<<sizeof(object)<<" -- "<<sizeof(int)<<sizeof(int*)<<sizeof(object_pool)<<std::endl;

    return 0;
}
}
#endif

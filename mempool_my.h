#ifndef MEMPOOL_MY_H
#define MEMPOOL_MY_H

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<mutex>
#include<cstring>

template<size_t BLOCKNUM>
class mempool{

private:
    struct free_block{
        free_block* next;
        free_block():next(nullptr){}
    };
    free_block* free_block_tail;

    struct mem_block{
        free_block block[BLOCKNUM];
        mem_block* next;
        mem_block* prev;
        mem_block():next(nullptr),prev(nullptr){
            memset(block,0,sizeof(block));
        }
    };
    mem_block* mem_block_tail;

    std::mutex mtx;

public:
    mempool():free_block_tail(nullptr),mem_block_tail(nullptr){}

    ~mempool(){
        while(mem_block_tail != nullptr){
            std::cout<<"~ :"<<mem_block_tail<<std::endl;
            mem_block* p = mem_block_tail;
            delete mem_block_tail;
            mem_block_tail = p->prev;
        }
    }

    void* allocate(){
        std::lock_guard<std::mutex>lk(mtx);
        if(!free_block_tail){
            std::cout<<"new mem_block"<<std::endl;
            mem_block* new_mem = new mem_block;
            for(size_t i = 1;i < BLOCKNUM;i++){
                new_mem->block[i - 1].next = &(new_mem->block[i]);
            }
            //初始化的时候已经对最后一个的next，和第一个的prev置空
            free_block_tail = &(new_mem->block[0]);
            if(!mem_block_tail){
                mem_block_tail = new_mem;
            }else{
                mem_block_tail->next = new_mem;
                new_mem->prev = mem_block_tail;
                mem_block_tail = new_mem;
            }
        }
        void* use_block = free_block_tail;
        free_block_tail = free_block_tail->next;
        return use_block;

    }

    void deallocate(void* block){
        free_block* unuse_block = static_cast<free_block*>(block);
        unuse_block->next = free_block_tail;
        free_block_tail = unuse_block;
        return;
    }

};

#endif // MEMPOOL_MY_H

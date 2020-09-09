#include <iostream>
#include"udp_client.cpp"
#include"udp_server.cpp"
#include"tcp_server.cpp"
#include"tcp_client.cpp"
#include"mempool_my.cpp"
#include"multi_thread.cpp"
using namespace std;

int prompt(){
    cout<<"-------------------------"<<endl;
    cout<<"1.multi_thread&rock"<<endl;
    cout<<"2.udp"<<endl;
    cout<<"3.tcp"<<endl;
    cout<<"4.memory chunk"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<endl<<"请输入你的选择"<<endl;
    int num;
    cin>>num;
    return num;
}

int main()
{
    bool flag = true;
    while(1 && flag){
        int num = prompt();
        switch(num){
            case 1:
                MULTI_THREAD::_tmain();
                break;
            case 2:
                UDP_SERVER::thread_run();
                UDP_CLIENT::thread_run();
                break;
            case 3:
                TCP_SERVER::thread_run();
                TCP_CLENT::thread_run();
                break;
            case 4:
                MEM_POOL::_tmain();
                flag = false;
                break;
        }
    }
    return 0;
}

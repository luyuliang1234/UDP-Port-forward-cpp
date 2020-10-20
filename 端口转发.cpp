#include <thread>  
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
SOCKET locala,localb;
WSADATA wsaData;
sockaddr_in localaddrA, localaddrB, clienta, clientb, temp;
char bufa[1500],bufb[1500];
int sizea = sizeof(localaddrA);
int set_addr()
{
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    locala = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    localb = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    localaddrA.sin_family = AF_INET;
    localaddrA.sin_port = htons(23455);
    localaddrA.sin_addr.s_addr = htonl(INADDR_ANY);
    localaddrB.sin_family = AF_INET;
    localaddrB.sin_port = htons(12345);
    localaddrB.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(locala, (SOCKADDR*)&localaddrA, sizeof(localaddrA));
    bind(localb, (SOCKADDR*)&localaddrB, sizeof(localaddrB));
    recvfrom(locala, bufa, 1024, 0, (SOCKADDR*)&clienta, &sizea);
    cout << "A已经上线";
    recvfrom(localb, bufb, 1024, 0, (SOCKADDR*)&clientb, &sizea);
    cout << "B已经上线";
    return 0;
}
int ab() {
    while (1)
    memset(bufa, 0, sendto(localb, bufa, recv(locala, bufa, 1500, 0), 0, (SOCKADDR*)&clientb, sizea));

}
int main()
{
    set_addr();
    thread t(ab);
    while (1)
    memset(bufb, 0, sendto(locala, bufb, recv(localb, bufb, 1500, 0), 0, (SOCKADDR*)&clienta, sizea));

}
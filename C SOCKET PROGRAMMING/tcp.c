#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <fcntl.h>
#include <time.h>
#include <arpa/inet.h>
#include <signal.h>

#define PORT        7000
#define SIZE_BUF    48
#define CNT_POLL    1
#define TIMEOUT     5000

#define EXIT(msg)   do { perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct
{
    char sStr[36];
} Packet;

int main()
{
    struct sockaddr_in  tBindAddr, tAcptAddr;
    struct pollfd       tPollFds[CNT_POLL];
    Packet              tPacket;
    socklen_t           nAddrLen = sizeof(tAcptAddr);
    int                 nSockFd, nAcptSockFd;
    int                 nRtn;
    int                 nConnectionCnt = 1;
    const char         *sStr[] = { "Apple",  "LG",      "Telsa",  "Discord", "Google", 
                                   "Amazon", "Twitter", "SpaceX", "Samsung", "Hyundai", };
    int                 nIdx;
     
    if ((nSockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        EXIT("socket");
    }
    
    tBindAddr.sin_family        = AF_INET;
    tBindAddr.sin_addr.s_addr   = INADDR_ANY;
    tBindAddr.sin_port          = htons(PORT);
    
    if (bind(nSockFd, (struct sockaddr *) &tBindAddr, sizeof(tBindAddr)) < 0)
    {
        EXIT("bind");
    }
    
    if (listen(nSockFd, 0) < 0)
    {
        EXIT("listen");
    }
    
    int flags = fcntl(nSockFd, F_GETFL, 0);
    fcntl(nSockFd, F_SETFL, flags | O_NONBLOCK);
    
    tPollFds[0].fd      = nSockFd;
    tPollFds[0].events  = POLLIN;

    srand(time(NULL));
    
    int index = 0;
    while (1)
    {
        nRtn = poll(tPollFds, CNT_POLL, TIMEOUT);
        
        if (nRtn == -1)
        {
            printf("aaaa\n");
            sleep(1);
            EXIT("poll");
        }
        else if (nRtn == 0)
        {
            printf("TIMEOUT\n");
        }
        else
        {
            if (tPollFds[0].revents & POLLHUP)
            {
                printf("123\n");
                close(nAcptSockFd);
                --nConnectionCnt;
            }
            else if (tPollFds[0].revents & POLLIN)
            {
                tPollFds[0].revents = 0;
                
                if ((nAcptSockFd = accept(nSockFd, (struct sockaddr *) &tAcptAddr, &nAddrLen)) < 0)
                {
                    EXIT("accpet");
                }
                
                if (nConnectionCnt >= 2)
                {
                    printf("Connection is full\n");
                    close(nAcptSockFd);
                    continue;
                }
                
                ++nConnectionCnt;
                
                printf("Connected\n");
                
                while (1)
                {
                    nIdx = rand() % 10;
                    memset(tPacket.sStr, 0x00, sizeof(tPacket));
                    strcpy(tPacket.sStr, sStr[nIdx]);
                    
                    printf("%d(%d) : %s(%s)\n", index, nIdx, tPacket.sStr, sStr[nIdx]);
                    
                    

                    if (tPacket.sStr == NULL)
                        continue;
                        
                    if (tPacket.sStr[0] == 0x00)
                        continue;
                    printf("a0\n"); 
                    if (send(nAcptSockFd, &tPacket, sizeof(tPacket), 0) == 0)
                    {
                        --nConnectionCnt;
                        printf("3333\n");
                        break;
                    }
                    printf("a1\n"); 
                    sleep(1); 
                    //send(nAcptSockFd, &tPacket, sizeof(tPacket), 0);
                    recv(nAcptSockFd, &tPacket, sizeof(tPacket), 0);
                    printf("%d(%d) : %s(%s)\n", index, nIdx, tPacket.sStr, sStr[nIdx]);
                    
                    //printf("%d : %s\n", index, tPacket.sStr);
                    
                    /*
                    if (!strcmp(sStr[nIdx], tPacket.sStr))
                    {
                        printf("%s\n", tPacket.sStr);
                        
                        close(nAcptSockFd);
                        --nConnectionCnt;
                        break;
                    }
                    */
                    
                    //usleep(1000);
                    index++;
                }
            }
        }
    }
    
    printf("4444\n");
    

    close(nAcptSockFd);
    close(nSockFd);
    
    return 0;
}

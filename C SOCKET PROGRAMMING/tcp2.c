#include <time.h>
#include <poll.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT        7000
#define TIMEOUT     5000
#define SIZE_BUF    48
#define CNT_POLL    2

#define RTN_ERROR       -1
#define RTN_SUCCESS      0
#define RTN_TIMEOUT      0 

#define EXIT(msg)   do { perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct
{
    char sStr[SIZE_BUF];
} Packet;

const char *sStr[] = { "Apple",  "LG",      "Telsa",  "Discord", "Google", 
                       "Amazon", "Twitter", "SpaceX", "Samsung", "Hyundai", };
struct pollfd        tPollFds[CNT_POLL];
int                  nSockFd, nAcptSockFd;
int                  nRtn;

int main();
int fn_ListenTCPSocket();
int fn_Accept();
int fn_SendPacket();

void sigpipe_handler(int signum) {
    int i;
    for (i = 3; i != 10; ++i)
        close(i);
}

int main()
{      
    nSockFd = fn_ListenTCPSocket();
    
    srand(time(NULL));
    
    signal(SIGPIPE, sigpipe_handler);
    
    nRtn = fn_Accept();
    
    return 0;
}

int fn_ListenTCPSocket()
{
    struct sockaddr_in  tSockaddr;
    int                 nSockFd;
    
    if ((nSockFd = socket(AF_INET, SOCK_STREAM, 0)) == RTN_ERROR)
        return RTN_ERROR;
        
    memset((struct sockaddr_in *) &tSockaddr, 0x00, sizeof(tSockaddr));
    tSockaddr.sin_family        = AF_INET;
    tSockaddr.sin_addr.s_addr   = INADDR_ANY;
    tSockaddr.sin_port          = htons(PORT);
    
    if (bind(nSockFd, (struct sockaddr *) &tSockaddr, sizeof(tSockaddr)) < 0)
        return RTN_ERROR;
        
    if (listen(nSockFd, 0) < 0)
        return RTN_ERROR;
        
    return (nSockFd);
}

int fn_Accept()
{
    struct sockaddr_in  tAcptAddr;
    socklen_t           nAddrLen = sizeof(tAcptAddr);
    
    while (1)
    {
        if ((nAcptSockFd = accept(nSockFd, (struct sockaddr *) &tAcptAddr, &nAddrLen)) == RTN_ERROR)
            break;
            
        tPollFds[0].fd      = nAcptSockFd;
        tPollFds[0].events  = POLLOUT;
            
        fn_SendPacket();
    }
    
    return RTN_ERROR;
}

int fn_SendPacket()
{
    Packet  tPacket;
    int     iIdx;
       
    while (1)
    {
        nRtn = poll(tPollFds, CNT_POLL, TIMEOUT);
        
        if      (nRtn == RTN_ERROR)     return RTN_ERROR;
        else if (nRtn == RTN_TIMEOUT)   printf("TIMEOUT\n");
        else
        {
            if (tPollFds[0].revents & POLLHUP)
            {
                tPollFds[0].revents = 0;
                return RTN_ERROR;
            }
            
            tPollFds[1].revents = 0;
        
            iIdx = rand() % 10;
            
            memset((Packet *) &tPacket, 0x00, sizeof(tPacket));
            strcpy(tPacket.sStr, sStr[iIdx]);
            
            if (send(nAcptSockFd, &tPacket, sizeof(tPacket), 0) == -1)
                return RTN_ERROR;
                
            printf("%s\n", tPacket.sStr);
        }
    }
}

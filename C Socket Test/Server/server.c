#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <poll.h>
#include <fcntl.h>

#define PORT        7000
#define SIZE_BUF    1024
#define CNT_POLL    1
#define TIMEOUT     5000

#define FIFO_PATH   "../fifo"

#define EXIT(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main()
{
    struct sockaddr_in  tBindAddr, tAcptAddr;
    struct pollfd       tPollFd[CNT_POLL];
    socklen_t           nAddrLen;
    char                sBuf[SIZE_BUF];
    int                 nSockFd, nAcptSockFd;
    int                 nFile, nFifo;
    int                 nBufLen;
    int                 nRet;
    
    if ((nSockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        EXIT("socket()");
    }
    
    tBindAddr.sin_family        = AF_INET;
    tBindAddr.sin_addr.s_addr   = INADDR_ANY;
    tBindAddr.sin_port          = htons(PORT);
    
    if (bind(nSockFd, (struct sockaddr *) &tBindAddr, sizeof(tBindAddr)) < 0)
    {
        EXIT("bind()");
    }
    
    if (listen(nSockFd, 0) < 0)
    {
        EXIT("listen()");
    }
    
    nAddrLen = sizeof(tAcptAddr);
    
    if ((nAcptSockFd = accept(nSockFd, (struct sockaddr *) &tAcptAddr, &nAddrLen)) < 0)
    {
        EXIT("accept()");
    }
    
    tPollFd[0].fd       = nAcptSockFd;
    tPollFd[0].events   = POLLIN;
    
    if ((nFile = open("text.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
    {
        EXIT("open()");
    }
    
    mkfifo(FIFO_PATH, 0666);
    
    if ((nFifo = open(FIFO_PATH, O_WRONLY)) == -1)
    {
        EXIT("open()");
    }
    
    while (1)
    {
        nRet = poll(tPollFd, CNT_POLL, TIMEOUT);
        
        if (nRet == -1)
        {
            EXIT("poll()");
        }
        else if (nRet == 0)
        {
            printf("Timeout\n");
        }
        else
        {
            if (tPollFd[0].revents & POLLIN)
            {
                memset((void *) sBuf, 0x00, sizeof(sBuf));
                
                if ((nBufLen = recv(nAcptSockFd, sBuf, sizeof(sBuf), 0)) < 0)
                {
                    EXIT("recv()");
                }
                
                if (nBufLen == 0)
                {
                    printf("Client disconnected\n");
                    break;
                }
                
                if (write(nFile, sBuf, nBufLen) != nBufLen)
                {
                    EXIT("write()");
                }
                
                if (write(nFifo, "1", 1) != 1)
                {
                    EXIT("write()");
                }
            }
        }
    }
    
    close(nFile);
    close(nFifo);
    close(nAcptSockFd);
    close(nSockFd);
    
    return 0;
}

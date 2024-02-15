#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define     PORT        7000
#define     SIZE_BUF    1024
#define     ADDRESS     "127.0.01"
#define     FILE_NAME   "test.txt"

#define     EXIT(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main()
{
    char                sBuf[SIZE_BUF];
    struct sockaddr_in  tAddr;
    FILE*               pFile;
    size_t              nReadBytes;
    int                 nSockFd;
    
    int                 nIdx = 0;
    
    if ((nSockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        EXIT("socket()");
    }
    
    tAddr.sin_family = AF_INET;
    tAddr.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, ADDRESS, &tAddr.sin_addr) <= 0)
    {
        EXIT("inet_pton()");
    }
    
    if (connect(nSockFd, (struct sockaddr *) &tAddr, sizeof(tAddr)) < 0)
    {
        EXIT("connect()");
    }
    
    if ((pFile = fopen(FILE_NAME, "r")) == NULL)
    {
        EXIT("fopen()");
    }
    
    while (fgets(sBuf, SIZE_BUF, pFile) != NULL)
    {
        if (send(nSockFd, sBuf, strlen(sBuf), 0) != strlen(sBuf))
        {
            EXIT("send()");
        }
        
        printf("%d : %s", ++nIdx, sBuf);
        sleep(2);
    }
    
    fclose(pFile);
    close(nSockFd);
    
    return 0;
}

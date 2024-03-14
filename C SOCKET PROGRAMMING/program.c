#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/mman.h>

#define CNT_POLL            1
#define BUF_SIZE            36
#define SHM_SIZE            1024
#define TIMEOUT             5000
#define PORT                7000
#define SHM_KEY             0xD0000000
#define SEM_KEY             0xE0000000
#define FIFO_PATH           "fifo"
#define ADDRESS             "127.0.0.1"
#define SEQ_FILE_NAME       "write_sequence.txt"

#define EXIT(msg)   do { perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct
{
    char sStr[BUF_SIZE];
} Packet;

struct sembuf g_tWaitOp = { 0,  1,  0 };
struct sembuf g_tPostOp = { 0, -1,  0 };

void sem_wait(int p_nSemId)
{
    semop(p_nSemId, &g_tWaitOp, 1);
}

void sem_post(int p_nSemId)
{
    semop(p_nSemId, &g_tPostOp, 1);
}

int main()
{
    const char *sStr[] = { "Apple",  "LG",      "Telsa",  "Discord", "Google", 
                           "Amazon", "Twitter", "SpaceX", "Samsung", "Hyundai", };
    long               *plSeq, *plFifo;
    int                 nSeqFile;
    int                 nFileFlag = O_RDWR;
    int                 i;
    long                nValue;
    int                 nShmId;
    char               *psShm;
    Packet              tPacket;
    struct stat         tStat;
    struct pollfd       tPollFds[CNT_POLL];
    struct sockaddr_in  tAddr;
    int                 nSockFd;
    int                 nRtn;
    int                 nSemId;
    int                 nFifo;
    int                 nDataCnt=0;
    
    if ((nSockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        EXIT("scoekt");
    }
    
    tAddr.sin_family    = AF_INET;
    tAddr.sin_port      = htons(PORT);
    
    if (inet_pton(AF_INET, ADDRESS, &tAddr.sin_addr) <= 0)
    {
        EXIT("inet_pton");
    }
    
    if (connect(nSockFd, (struct sockaddr *) &tAddr, sizeof(tAddr)) < 0)
    {
        EXIT("connect");
    }
    
    printf("Connected\n");
    
    mkfifo(FIFO_PATH, 0666);
    
    if ((nFifo = open(FIFO_PATH, O_RDWR)) == -1)
    {
        EXIT("open");
    }
    
    if ((nSemId = semget(SEM_KEY, 1, IPC_CREAT | 0666)) < 0)
    {
        EXIT("semget");
    }
    
    if (semctl(nSemId, 0, SETVAL, 1) == -1)
    {
        EXIT("semctl");
    }
    
    if ((nShmId = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        EXIT("shmget");
    }
    
    if ((psShm = shmat(nShmId, NULL, 0)) == (char *) -1)
    {
        EXIT("shmat");
    }
    
    if (access(SEQ_FILE_NAME, F_OK) == -1)
    {
        printf("File does not exists\n");
        printf("Create the file\n");
        nFileFlag |= O_CREAT;
    }
    
    if ((nSeqFile = open(SEQ_FILE_NAME, nFileFlag, 0666)) == -1)
    {
        EXIT("open");
    }
    
    printf("File has opened\n");
    
    if (fstat(nSeqFile, &tStat) == -1)
    {
        EXIT("fstat");
    }
    
    if (tStat.st_size == 0)
    {
        if (ftruncate(nSeqFile, sizeof(*plSeq)) == -1)
        {
            EXIT("ftruncate");
        }
    }
    
    /*
    if (write(nFifo, "0L", 2) == -1)
    {
        EXIT("write");
    }
    */
    
    if ((plSeq = (long *) mmap(NULL, sizeof(*plSeq), PROT_READ | PROT_WRITE, MAP_SHARED, nSeqFile, 0)) == MAP_FAILED)
    {
        EXIT("mmap");
    }
    
    /*
    if ((plFifo = (long *) mmap(NULL, sizeof(*plFifo), PROT_READ | PROT_WRITE, MAP_SHARED, nFifo, 0)) == MAP_FAILED)
    {
        EXIT("mmap");
    }
    */
    
    tPollFds[0].fd      = nSockFd;
    tPollFds[0].events  = POLLIN;
    
    printf("%ld\n", *plSeq);
    
    int index = 0;
    while (1)
    {
        /*
        if (index == 10)
            break;
        */
        nRtn = poll(tPollFds, CNT_POLL, TIMEOUT);
        
        if (nRtn == -1)
        {
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
                printf("Closed\n");
                break;
            }
            else if (tPollFds[0].revents & POLLIN)
            {
                tPollFds[0].revents = 0;
                
                memset((void *) &tPacket, 0x00, sizeof(tPacket));
                
                
                if (recv(nSockFd, &tPacket, sizeof(tPacket), 0) == 0)
                {
                    break;
                }
                send(nSockFd, &tPacket, sizeof(tPacket), 0);
                
                sem_wait(nSemId);
                memcpy(psShm + sizeof(tPacket) * (*plSeq % BUF_SIZE), &tPacket, sizeof(tPacket));
                sem_post(nSemId);
                
                printf("(%d) %ld : %s\n", ++nDataCnt, *plSeq, psShm + sizeof(tPacket) * (*plSeq % BUF_SIZE));
                ++(*plSeq);
                usleep(3000); 
                if (write(nFifo, "1", 1) == -1)
                {
                    EXIT("write");
                }
              
            }
        }
        
        ++index;
       //usleep(1000);
    }
    /*
    for (i = 0; i != sizeof(sStr) / sizeof(sStr[0]); ++i)
    {
        memset((void *) &tPacket, 0x00, sizeof(tPacket));
        strcpy(tPacket.sStr, sStr[i]);
        memcpy(psShm + sizeof(tPacket) * i, &tPacket, sizeof(tPacket));
    }
    */
    
    /*
    for (i = 0; i != sizeof(sStr) / sizeof(sStr[0]); ++i)
    {
        printf("%d : %s\n", i, psShm + i * sizeof(tPacket));
    }
    */
    
    if (close(nSeqFile) == -1)
    {
        EXIT("close");
    }
    
    if (munmap(plSeq, sizeof(plSeq)) == -1)
    {
        EXIT("munmap");
    }
    
    close(nSockFd);
    
    return 0;
}

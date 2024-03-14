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
#define BUF_SIZE            48
#define SHM_SIZE            1024
#define TIMEOUT             5000
#define PORT                7001
#define SHM_KEY             0xD0000000
#define SEM_KEY             0xE0000000
#define FIFO_PATH           "fifo"
#define WRITE_SEQ_FILE_NAME "write_sequence.txt"
#define READ_SEQ_FILE_NAME  "read_sequence.txt"

#define EXIT(msg)   perror(msg); exit(EXIT_FAILURE);

typedef struct
{
    char sStr[BUF_SIZE];
} Packet;

struct sembuf g_tWaitOp = { 0,  1, 0 };
struct sembuf g_tPostOp = { 0, -1, 0 };

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
    long           *plWriteSeq, *plReadSeq;
    int             nWriteSeqFile, nReadSeqFile;
    int             nShmId;
    char           *psShm;
    Packet          tPacket;
    struct pollfd   tPollFds[CNT_POLL];
    int             nRtn;
    int             nFifo;
    long            lSeqCnt;
    char            sFifoBuf[2];
    struct stat     tStat;
    
    if ((nFifo = open(FIFO_PATH, O_RDWR)) == -1)
    {
        EXIT("open");
    }
    
    if ((nShmId = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        EXIT("shmget");
    }
    
    if ((psShm = shmat(nShmId, NULL, 0)) == (char *) -1)
    {
        EXIT("shmat");
    }
    
    if ((nWriteSeqFile = open(WRITE_SEQ_FILE_NAME, O_RDWR | O_CREAT, 0666)) == -1)
    {
        EXIT("open");
    }
    
    if ((plWriteSeq = (long *) mmap(NULL, sizeof(*plWriteSeq), PROT_READ | PROT_WRITE, MAP_SHARED, nWriteSeqFile, 0)) == MAP_FAILED)
    {
        EXIT("mmap");
    }
    
    if ((nReadSeqFile = open(READ_SEQ_FILE_NAME, O_RDWR | O_CREAT, 0666)) == -1)
    {
        EXIT("open");
    }
    
    if (fstat(nReadSeqFile, &tStat) == -1)
    {
        EXIT("fstat");
    }
    
    if (tStat.st_size == 0)
    {
        if (ftruncate(nReadSeqFile, sizeof(*plReadSeq)) == -1)
        {
            EXIT("ftruncate");
        }
    }
    
    if ((plReadSeq = (long *) mmap(NULL, sizeof(*plReadSeq), PROT_READ | PROT_WRITE, MAP_SHARED, nReadSeqFile, 0)) == MAP_FAILED)
    {
        EXIT("mmap");
    }
    
    tPollFds[0].fd      = nFifo;
    tPollFds[0].events  = POLLIN;
    
    while (1)
    {
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
            if (tPollFds[0].revents & POLLIN)
            {
                lSeqCnt = *plWriteSeq;
                for (; *plReadSeq != lSeqCnt; ++(*plReadSeq))
                {
                    printf("%ld : %s\n", *plReadSeq, psShm + sizeof(tPacket) * (*plReadSeq % BUF_SIZE));
                }
                read(nFifo, sFifoBuf, sizeof(sFifoBuf)); 
            }
        }
    }
    
    if (close(nWriteSeqFile) == -1)
    {
        EXIT("close");
    }
    
    if (close(nReadSeqFile) == -1)
    {
        EXIT("close");
    }
    
    if (munmap(plWriteSeq, sizeof(plWriteSeq)) == -1)
    {
        EXIT("munmap");
    }
    
    if (munmap(plReadSeq, sizeof(plReadSeq)) == -1)
    {
        EXIT("munmap");
    }
    
    return 0;
}

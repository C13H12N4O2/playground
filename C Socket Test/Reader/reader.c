#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define     BUF_SIZE    1024
#define     FIFO_PATH   "../fifo"

#define     EXIT(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main()
{
    char    sBuf[BUF_SIZE];
    int     nFile;
    int     nStatus;
    
    mkfifo(FIFO_PATH, 0666);
    
    if ((nFile = open(FIFO_PATH, O_RDONLY)) == -1)
    {
        EXIT("open()");
    }
    
   while (1)
    {
        memset((void *) sBuf, 0x00, sizeof(sBuf));
        
        if ((nStatus = read(nFile, sBuf, sizeof(sBuf))) == -1)
        {
            EXIT("read()");
        }
        else if (nStatus == 0)
        {
            printf("EOL\n");
            break;
        }
        else 
        {
            printf("%s\n", sBuf);
        }
    }
    
    close(nFile);
    
    return 0;
}

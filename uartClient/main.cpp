
/**************client.c***************/
#include<stdio.h>
#include <stdlib.h> //exit()
#include <strings.h>//bzero()
#include <unistd.h> //close()
#include<sys/types.h>
#include<fcntl.h>
#include<termios.h>
#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyUSB0"
int main()
{
    int fd,res;
    struct termios oldtio,newtio;
    char buf[256];
    printf("start ...\n");
    fd=open(MODEMDEVICE,O_RDWR | O_NOCTTY);
    if(fd<0)
    {
      perror(MODEMDEVICE);
      exit(1);
    }
    printf("open...\n");
    tcgetattr(fd,&oldtio);
    bzero(&newtio,sizeof(newtio));
    newtio.c_cflag=BAUDRATE | CS8 | CLOCAL | CREAD;
    newtio.c_iflag=IGNPAR;
    newtio.c_oflag=0;
    newtio.c_lflag=ICANON;
    tcflush(fd,TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);
    printf("reading...\n");
    while(1)
    {
       res=read(fd,buf,255);
       buf[res]=0;//char buf[ ],'\0' = 0;
       printf("res=%d vuf=%s\n",res,buf);
       if(buf[0]=='*') break;
    }
       printf("close...\n");
       close(fd);
       tcsetattr(fd,TCSANOW,&oldtio);
       return 0;
}

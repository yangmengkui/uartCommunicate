#include<stdio.h>
#include <stdlib.h> //exit()
#include <strings.h>//bzero()
#include <unistd.h> //close()
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>
#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyUSB0"
#define STOP '@'
int main(){
   int fd,res;
   struct termios oldtio,newtio;
   char ch,s1[20];
   printf("start...\n");
   fd=open(MODEMDEVICE,O_RDWR | O_NOCTTY);
   if(fd<0)
   {
      perror(MODEMDEVICE);
      exit(1);
   }
   printf("open...\n");
   tcgetattr(fd,&oldtio);
   bzero(&newtio,sizeof(newtio));
   newtio.c_cflag=BAUDRATE|CS8|CLOCAL|CREAD;
   newtio.c_iflag=IGNPAR;
   newtio.c_oflag=0;
   newtio.c_lflag=ICANON;
   tcflush(fd,TCIFLUSH);
   tcsetattr(fd,TCSANOW,&newtio);
   printf("writing...\n");
   while(1)
   {
      while((ch=getchar())!='@')
        {
           s1[0]=ch;
           res=write(fd,s1,1);
        }
        s1[0]=ch;
        s1[1]='\n';
        res=write(fd,s1,2);
        break;
   }
   printf("close...\n");
   close(fd);
   tcsetattr(fd,TCSANOW,&oldtio);
   return 0;
}


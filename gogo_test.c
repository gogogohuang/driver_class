#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "cdata_ioctl.h"

/*define*/
#define NAME "driver_test"


int main(int argc, char const* argv[])
{
    int     fd, i=0;
    char    pix[4]={0x00, 0xff, 0x00, 0xff};
    char    *fb;  
    int     size = 0 ;
    char    name[LEN_OF_NAME+1];
    char    buf[LEN_OF_NAME];
    int     num;
    pid_t   child;
 
  //  child = fork();

    fd = open("/dev/cdata", O_RDWR);
    if(fd < 0){
        printf("open Fail \n");
        return -1;
    }else{
        printf("open success\n");
    }
    /*if(child){*/
        /*goto parent;*/
    /*}*/

/*child:*/
    /*ioctl(fd, IOCTL_SetName, "c");*/
    /*ioctl(fd, IOCTL_SetName, "h");*/
    /*ioctl(fd, IOCTL_SetName, "i");*/
    /*ioctl(fd, IOCTL_SetName, "l");*/
    /*ioctl(fd, IOCTL_SetName, "d");*/
    /*usleep(100);*/
    /*ioctl(fd, IOCTL_SetName, "h");*/
    /*ioctl(fd, IOCTL_SyncName, buf);*/
    /*printf("buf_child = %s \n", buf);*/

    /*goto done;*/

//parent:
    /*if((size = write( fd, buf, 10 )) < 0){*/
                /*printf("no data \n");*/
    /*}*/
    write(fd, "hello1", 6) ;
    printf("111\n");
    write(fd, "hello2", 6) ;
    printf("111\n");
    ioctl(fd, IOCTL_SyncName, buf);
    printf("buf_parent = %s \n", buf);
    
    //goto done;

//done:
    close(fd);
    return 0;
    /*printf("enter function code \n");*/
    /*scanf("%d",&num);*/
    
    /*switch (num) {*/
        /*case 0:*/
            /*printf("read \n");*/
            /*lseek(fd, 0 , SEEK_SET);*/
            /*if((size = read(fd, buf, 10)) < 0){*/
                /*printf("no data \n");*/
            /*}*/
            /*break;*/
        /*case 1:*/
            /*printf("write \n");*/
            /*if((size = write( fd, buf, 10 )) < 0){*/
                /*printf("no data \n");*/
            /*}*/
            /*break;*/
        /*case 2:*/
            /*printf("IOCTL_WRITE\n");*/
            /*ioctl(fd, IOCTL_WRITE, num);*/
            /*break; */
        /*case 3:*/
            /*printf("IOCTL_SetName\n");*/
            /*printf("plz enter dev name \n");*/
            /*scanf("%s", name);*/
            /*ioctl(fd, IOCTL_SetName, name);*/
            /*break;*/
        /*default:*/
            /*printf("no function \n");*/
            /*break;*/
    /*}*/
   
    /*close(fd);*/
    /*return 0;*/
}

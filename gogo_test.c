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
 
    //child = fork();

    fd = open("/dev/cdata", O_RDWR);
    if(fd < 0){
        CDATA_DEBUG_PRINT("open Fail \n");
        return -1;
    }else{
        CDATA_DEBUG_PRINT("open success\n");
    }
    /*if(child){*/
        /*goto parent;*/
    /*}*/

/*child:*/

   /*printf("buf_child = %s \n", buf);*/
    /*CDATA_DEBUG_PRINT("child end\n");*/
    /*goto done;*/

//parent:
    
    /*while(1){*/
        printf(" write data \n");
        write(fd, "hello1", 6) ;
        write(fd, "hello1", 6) ;
        write(fd, "hello1", 6) ;
 
 
        /*}*/
    ioctl(fd, IOCTL_SyncName, buf);
    CDATA_DEBUG_PRINT("buf_parent = %s \r\n", buf);
    
    goto done;

done:
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

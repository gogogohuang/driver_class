#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "cdata_ioctl.h"
#include "cdata_def.h"

/*define*/
#define NAME "driver_test"


int main(int argc, char const* argv[])
{
    int     fd, i=0;
    char    pix[4]={0x00, 0xff, 0x00, 0xff};
    char    *fb;  
    int     size = 0 ;
    char    name[LEN_OF_NAME+1];
    int     num=123;
    /*pid_t   child;*/

    /*child = fork();*/

    fd = open("/dev/cdata", O_RDWR);
    
    if(fd < 0){
        printf("open Fail \n");
        return -1;
    }else{
        printf("open success\n");
    }
    //fb = (char *)mmap(0, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd ,0);
    /*lseek(fd, 0 , SEEK_SET);*/
    /*if((size = read(fd, buf, 10)) < 0){*/
        /*printf("no data \n");*/
    /*}*/
    /*if((size = write( fd, buf, 10 )) < 0)*/
    /*{*/
         /*printf("wirte \n");*/
 
    /*}*/
    /*ioctl(fd, IOCTL_WRITE, num);*/
    /*printf("num = %d \n", num);*/
    
    /*printf("plz enter dev name \n");*/
    /*scanf("%s", name);*/
    /*printf("NAME = %s \n", name);*/
    sprintf(name,"%s",NAME);
    ioctl(fd, IOCTL_SetName, name);
    close(fd);
    return 0;
}

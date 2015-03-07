#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "cdata_ioctl.h"


int main(int argc, char const* argv[])
{
    int fd, i=0;
    char pix[4]={0x00, 0xff, 0x00, 0xff};
    char *fb;  
    int size = 0 ;
    char buf[11];
    int num=123;

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
        /*printf("no data \n"); */
    /*}*/
    ioctl(fd, IOCTL_WRITE, num);

    close(fd);
    return 0;
}

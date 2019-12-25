#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char** argv){
char buf[64];
int n,fd;
fd=open(argv[1],O_RDWR);
n=write(fd,argv[2], strlen(argv[2]));
read(fd,buf,n);
printf("buf=%s",buf);
close(fd);
}

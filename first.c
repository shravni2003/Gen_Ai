
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void child_oper(int id){
    printf("Child %d, PID is %d\n",id,getpid());
    exit(0);
}

int main(){
    int i;
    __pid_t pid;

    for(i=0; i<5; i++){
        pid=fork();


        if(pid<0){
            fprintf(stderr,"Error to create child\n");
            return 1;
        }
        else if(pid==0){
           child_oper(i);
        }
        else{
            printf("PArent created child with pid %d\n",pid);
        }

    }

    for(int i=0; i<5; i++){
        wait(NULL);
    }

    return 0;
}
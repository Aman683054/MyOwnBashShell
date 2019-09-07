#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>


void child(int);


int myshell( char* argv)
{ //printf("yes\n");
  
      char arr1[4096]={};
     

      char *l = strdup(argv);
      char *rslt,*r2, *r3, *r4;
      int flag=0, flag1=1;
      int result;
      char **arg;
      while(  (rslt  = strsep( &l, ";" )  ) != NULL  ){
          //printf("%s\n",rslt);
            
        flag=0;
          
        while( ( r3 = strsep( &rslt,"&&") ) != NULL ){
          
          flag1=1;
          
          if(strcmp(r3,"\0")!=0)  
          
          if(flag ==0){
          
            while( ( r4 = strsep( &r3,"||") ) != NULL ){
              int i=0;
              if(strcmp(r4,"\0")!=0)
              if(flag1==1){
                arg=malloc(sizeof(char *)*256);
              for (int i=0; i<256; i++) {
                arg[i]=malloc(sizeof(char)* 256);
                }
                while( ( r2 = strsep( &r4," ") ) != NULL ){
                  if(strcmp(r2,"\0")!=0){
                  //printf("space strok %s\n",r2);
                  strcpy(arg[i++], r2);
                    }
                }
                arg[i]=NULL;

              
               
                usleep(200000);
                printf("\n");
                if(fork()==0){
                  result=execvp(arg[0] ,arg);
                  if(result==-1){
                    printf("%s: command not found\n",arg[0]);
                  }
                  //printf("exec out%d\n",result );
                  exit(result);
          
                  }
                else{
                int n;
                wait(&n);

                if (WEXITSTATUS(n)==0){
                    flag=0;
                    flag1=0;

                   }
                  else{

                    flag=1;
                    flag1=1;
                  }

                }
    free(arg);
    }
    }
    }
        else{
          break;
        }

         
      }   
        
         
    }
     
    return 0;
}
    
void myAlarmHandler(){

}

int main(int argc, char *argv[]){  
signal(SIGALRM, myAlarmHandler);
  int sd, client, portNumber, status;
  struct sockaddr_in servAdd;      // client socket address
  
 if(argc != 2){
    printf("Call model: %s <Port Number>\n", argv[0]);
    exit(0);
  }
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    fprintf(stderr, "Cannot create socket\n");
    exit(1);
  }
  sd = socket(AF_INET, SOCK_STREAM, 0);
  servAdd.sin_family = AF_INET;
  servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
  sscanf(argv[1], "%d", &portNumber);
  servAdd.sin_port = htons((uint16_t)portNumber);
  
  bind(sd, (struct sockaddr *) &servAdd, sizeof(servAdd));
  listen(sd, 5);

  while(1){
    printf("Waiting for a client to chat with\n");
    client = accept(sd, NULL, NULL);
    printf("Got a client, start chatting\n");
    
    if(!fork())
      child(client);

    close(client);
    waitpid(0, &status, WNOHANG);
  }
}

void child(int sd){
  char message[255];
        int n, pid;


        write(sd, "start chatting", 16);


int fd[2],err[2];
if(pipe(fd)==-1) exit(1);
if(pipe(err)==-1) exit(1);
char alpha;
n=0;
char *cmd ;
  pid=fork();
  if(pid)                         /* reading client messages */
          while(1){
           // printf("yes\n");
            cmd = malloc(256*sizeof(char));

            while(read(sd,&alpha,1) == 1){
      
           if(alpha == '\n'  )
              break;
          else if( alpha != '\0' || alpha != NULL){
              strcpy(&cmd[n],&alpha);
              n++;
              //printf("%d ",alpha );
            }
      
       if(!strcasecmp(cmd, "quit\n")){
         //         kill(pid, SIGTERM);
          exit(0);
       }
     }
       cmd[n]='\0';
       close(fd[0]);
       close(err[0]);
       dup2(fd[1], 1);
       dup2(err[1],2);
       myshell(cmd);
       sleep(1);
       //pause();
       dup2(STDOUT_FILENO,1);
       dup2(STDERR_FILENO,2);
      printf("\n");
       n=0;
       free(cmd);
       
     }
  if(!pid)    {                  /* sending messages to the client  */


     close(fd[1]);
     close(err[1]);
     int pid1=fork();
     if(!pid1){
      char s;
      
       pause();
      while(1){
      if(n=read(err[0],&s, 1)){
       
        //message[n]='\0';
        write(sd, &s, 1);
        
}


}

     }
          
else{

     char c;
     while(1){
      if(n=read(fd[0],&c, 1)){
      
        //message[n]='\0';
        write(sd, &c, 1);
        
}
kill(pid1, SIGALRM);

}

      }
}
}

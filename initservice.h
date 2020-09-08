#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<wait.h>
#include<sys/stat.h>
#include<error.h>
#include<string.h>
#define FILEPATH_MAX 80
char *judgeTempPath = NULL;
char *resworkspace = NULL;
FILE *config_fd = NULL;
char* getdir(){
	char *key = (char *)malloc(10*sizeof(char));
	char *value = (char *)malloc(30*sizeof(char));
	fscanf(config_fd,"%s",key);
	if(strcmp(key,"TEMPPATH") == 0){
		fscanf(config_fd,"%s",value);
		fscanf(config_fd,"%s",value);
		free(key);
		return value;
	}else{
		printf("Unable accept Config");
        return NULL;

    }
}
//
// Created by geray on 2020/9/3.
//

#ifndef JUDGER_FILECOMPARE_H
#define JUDGER_FILECOMPARE_H
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <fcntl.h>
#include <string.h>
#include "exit_code.h"

#define LINE_BUF_MAX_SIZE 200

int buf_compare(char* buf1, char* buf2){
    int i;
    for(i = LINE_BUF_MAX_SIZE-1; buf1[i] != '\n'; --i);
    if(i > 0)
        buf1[i] = '\000';
    for(i = LINE_BUF_MAX_SIZE-1; buf2[i] != '\n'; --i);
    if(i > 0)
        buf2[i] = '\000';
    for(i=0; i<LINE_BUF_MAX_SIZE; ++i){
        if(buf1[i] != buf2[i])
            return 1;
    }
    return 0;
}

int file_compare(const char* outfile_path,const  char* stdfile_path){

    FILE *fd_outfile = fopen(outfile_path, "r");
    FILE *fd_stdfile = fopen(stdfile_path, "r");
    if(fd_outfile == NULL || fd_stdfile == NULL)
        error(ERR_OFE,0,"Open File Error");
    char outfile_buf[LINE_BUF_MAX_SIZE] = {0}, stdfile_buf[LINE_BUF_MAX_SIZE] = {0};
    while(!feof(fd_outfile) && !feof(fd_stdfile)){
        memset(outfile_buf, 0, LINE_BUF_MAX_SIZE);
        memset(stdfile_buf, 0, LINE_BUF_MAX_SIZE);
        fgets(outfile_buf, LINE_BUF_MAX_SIZE -1, fd_outfile);
        fgets(stdfile_buf, LINE_BUF_MAX_SIZE -1, fd_stdfile);
        if(buf_compare(outfile_buf, stdfile_buf)){
            fclose(fd_outfile);
            fclose(fd_stdfile);
            return 0;
        }

    }
    fclose(fd_outfile);
    fclose(fd_stdfile);
    return 1;
}
#endif //JUDGER_FILECOMPARE_H

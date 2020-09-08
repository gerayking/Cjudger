//
// Created by geray on 2020/9/2.
//

#ifndef JUDGER_PARSE_H
#define JUDGER_PARSE_H
#include "result.h"
void clear_env(std::string temDir);
ini_result init_env();
void redirctIO();
run_result  return_result(std::string info,int status,
                          ini_result &iniResult, com_result &comResult);
com_result compile(ini_result &iniResult);
run_result run(run_in &runIn);
void compare();
void print_usage();
void parse_opt(int argc, char * argv[]);
#endif //JUDGER_PARSE_H

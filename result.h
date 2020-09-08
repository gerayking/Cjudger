//
// Created by geray on 2020/9/3.
//

#ifndef JUDGER_RESULT_H
#define JUDGER_RESULT_H
#include<string>
struct optArgs{
    std::string execName;
    std::string pid;
};
struct run_in{
    std::string stdin_file;
    std::string stdout_file;
    std::string stderr_file;
    std::string stdexec_file;
};
struct ini_result{
    std::string temDir;
    std::string outFileTem;
    std::string errFileTem;
    std::string pid;
    std::string exec;
};
struct run_result{
    int exitCode;
    std::string stdAns;
    std::string stdOut;
    std::string errInfo;
    long time;
    int mem;
};
struct com_result{
    std::string execFileTem;
    int isCompiled;
};
struct cmp_result{
    int status;
    std::string info;
};

#endif //JUDGER_RESULT_H

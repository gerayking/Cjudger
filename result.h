//
// Created by geray on 2020/9/3.
//

#ifndef JUDGER_RESULT_H
#define JUDGER_RESULT_H
#include<string>
struct ini_result{
    std::string temDir;
    std::string inFileTem;
    std::string inFileAbs;
    std::string outFileAbs;
    std::string ansFileTem;
    std::string errFileTem;
    std::string inFile;
};
struct run_result{
    int exitCode;
    std::string outFileTem;
    std::string ansFileAbs;
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

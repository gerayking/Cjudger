#include <iostream>
#include "parse.h"
#include "filecompare.h"
#include "result.h"
#include "exit_code.h"
std::string geterr(std::string errFileTem){

}
int main(int argc, char * argv[]) {
//    test();
    cmp_result cmpResult;
    parse_opt(argc,argv);
    ini_result iniResult = init_env();
    com_result comResult = compile(iniResult);
    if(comResult.isCompiled==0){
        printf("CE");
        cmpResult.status=0;
        cmpResult.info = geterr(iniResult.errFileTem);
        // 还没想好怎么处理信息
        return 0;
    }
    run_result runResult = run(iniResult,comResult);
    int isAc;
    if(runResult.exitCode == 0){
        printf("CE\n");
        return 0;
    }else if(runResult.exitCode==EX_RE){
        //RE 返回
    }else if(runResult.exitCode==EX_MLE){
        //MLE 返回
    }else if(runResult.exitCode==EX_TLE){
        //TLE返回
        printf("TLE\n");
    }else {
         printf("time : %ld\n"
                "memory %d\n"
                "status %d\n",runResult.time,runResult.mem,runResult.exitCode);
         isAc = file_compare(runResult.outFileTem.c_str(), runResult.ansFileAbs.c_str());
    }
    if(!isAc){
        //AC 返回
    }else{
        //WA 返回
    }
    clear_env(iniResult.temDir);
    return 0;
}

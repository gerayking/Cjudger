
#include<iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <pwd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ptrace.h>
#include <sys/resource.h>
#include <string>


#include "utils.h"
#include "initservice.h"
#include "exit_code.h"
#include "parse.h"
static const char *optString = "t:m:p:h";
static const struct option longOpts[] = {
	{"time", required_argument, NULL, 't'},
	{"memory", required_argument, NULL, 'm'},
    {"pid",required_argument,NULL,'p'},
	{"help", no_argument, NULL, 'h'},
	{ NULL, no_argument, NULL, 0 }
};

pid_t child_pid;
int timeLimit = 1000,memoryLimit=32768,file_type = 0;
std::string execDir;
std::string pid;
char tmpDirTemplate[]= "/tmp/LJKZ.XXXXXX";
void clear_env(std::string temDir){
    std::string buffer;
    buffer = "rm -rf "+temDir;
    if(system(buffer.c_str()) != 0){
            error(EX_ERROR,0,"DEL TEMP Failed");
    }
}
// out 和 err放在临时目录中
ini_result init_env(){
    // 创建临时文件夹
//	printf("tmpDirTemplate : %s\n",tmpDirTemplate);
	umask(0);
	std::string tmpDirName = mkdtemp(tmpDirTemplate);
//    printf("%s\n",tmpDirName.c_str());// 转移目标文件到临时区
//    std::cout<<"exec "+buffer<<"\n";
	std::string outFileTem = tmpDirName + "/" + pid + ".out";
	std::string errFilename = tmpDirName + "/" + pid + ".err";
	struct passwd *nobody = getpwnam("root");
//	// 给予当前进程权限，直接给root
//    uid_t  parent_uid = getuid();
//	uid_t  parent_gid = getegid();
//	uid_t child_uid = nobody->pw_uid;
//	uid_t child_gid = nobody->pw_gid;
//	chown(tmpDirName.c_str(),child_uid,child_gid);
	chmod(tmpDirName.c_str(),00711);
	// infile Auth
	if(outFileTem.c_str() != NULL){
		int tmpof = open(outFileTem.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 00777);
		close(tmpof);
	}
	if(errFilename.c_str() !=NULL){
	    int tmpof = open(errFilename.c_str(),O_WRONLY|O_CREAT|O_TRUNC,00777);
	    close(tmpof);
	}
	ini_result res;
	res.temDir = tmpDirName;// 临时目录
	res.pid = pid;// pid
	res.errFileTem=errFilename;// UUID.err
	res.outFileTem = outFileTem;// UUID.out
	res.exec = execDir;
	return res;
}
run_result  return_result(std::string info,int status,
                          std::string out_ans,
                          long time,int mem){
    run_result res;
    res.stdOut = out_ans;
    res.errInfo = info;
    res.exitCode = status;
    res.time = time;
    res.mem = mem;
    return res;
}
// 还没有处理编译错误的信息
//com_result compile(ini_result &iniResult){
//	std::string buffer;
//	std::string infilePath = iniResult.temDir+"/"+exec;
//	std::string execFileName = iniResult.temDir+"/"+pid+"_exec";
//    com_result res;
//    if(file_type == 0){
//	    error(EX_ERROR,0,"no language type");
//	}
//	else if(file_type==1){//C Language
//	    buffer = "gcc -O2 -w -static -fmax-errors=3 -std=c11 "+infilePath+" -lm -o "+execFileName + ">"+iniResult.errFileTem;
//	    system(buffer.c_str());
//	    //  compile faild
//        if(access(execFileName.c_str(),0) != 0){
//            res.isCompiled=0;
//            return res;
//	        error(EX_ERROR,0,"Compile faild");
//	    }
//	}else if(file_type == 2){
//        buffer = "g++ -O2 -w -static -fmax-errors=3 -std=c11 "+infilePath+" -lm -o "+execFileName + ">"+iniResult.errFileTem;
//	    system(buffer.c_str());
//        if(access(execFileName.c_str(),0) != 0){
//            res.isCompiled=0;
//            return res;
////	        error(EX_ERROR,0,"Compile faild");
//	    }
//	}
//	res.execFileTem = execFileName;
//	res.isCompiled=1;
//	return res;
//}
/*int get_memory_by_pid(pid_t p)
{
//    printf("%d\n",p);
    FILE *fd = NULL;
    char *file = (char*)malloc(50);
    char *buffer = (char * )malloc(50);
    printf("%d\n",p);
    sprintf(file,"/proc/%d/status",p);
    puts(file);
    fd = fopen(file,"r");
    for(int i=0;i<10;i++){
        fgets(buffer,sizeof(buffer),fd);
        puts(buffer);
    }
    free(file);
    free(buffer);
    fclose(fd);
    return 1;
}*/
/*
 * struct run_in{
    std::string stdin_file: input file
    std::string stdout_file: output file
    std::string sederr_file: err file
    std::string stdexec_file: exec file
};
 *
 * */
run_result run(run_in &runIn){
	int status;
    time_t time_usage = 0;
    int mem_usage = 0;
	child_pid = fork();
	if(child_pid == -1){
	    error(EX_ERROR,0,"fork error");
	}
	// child process
	if(child_pid == 0){
	    int fd_in,fd_out,fd_err;
	    fd_in = open(runIn.stdin_file.c_str(), O_RDONLY);
	    fd_out = open(runIn.stdout_file.c_str(), O_WRONLY);
	    fd_err = open(runIn.stderr_file.c_str(), O_WRONLY);
        if(fd_in==-1 || fd_out == -1 || fd_err == -1){
	        error(EX_ERROR,0,"open file error");
	    }
        dup2(fd_in,STDIN_FILENO);
	    dup2(fd_out,STDOUT_FILENO);
	    dup2(fd_err,STDERR_FILENO);
        if(ptrace(PTRACE_TRACEME,0,NULL,NULL) < 0){
	        error(EX_ERROR,0,"ptrace error");
	    }
        printf("run child process");
        if(execv(runIn.stdexec_file.c_str(), NULL) == -1){
	        error(EX_ERROR,0,"execv error");
	    }
	}else{
	    // parent process
	    struct rusage usage;
	    while(1){
	        wait4(child_pid,&status,WUNTRACED,&usage);
            long tmpmem = usage.ru_minflt * (getpagesize() >> 10);//get_memory_by_pid(child_pid);
            if(tmpmem>mem_usage)mem_usage=tmpmem;
	        time_usage = tv2ms(usage.ru_stime)+tv2ms(usage.ru_utime);
	        if(time_usage>timeLimit){
	            kill(child_pid,SIGKILL);
	            return return_result("TLE", EX_TLE, runIn.stdout_file, time_usage, mem_usage);
	        }
	        if(mem_usage>memoryLimit){
	            kill(child_pid,SIGKILL);
	            return return_result("MLE_NORMAL", EX_MLE, runIn.stdout_file, time_usage, mem_usage);
	        }
	        // 正常退出
            if(WIFEXITED(status)){
                return return_result("Compile and Run end", EX_SUCCESS, runIn.stdout_file, time_usage, mem_usage);
            }else if(WIFSIGNALED(status)){// 信号中断
                if(WTERMSIG(status)==SIGSEGV){
                    if(mem_usage > memoryLimit){
                        return return_result("MLE_SIG", EX_MLE, runIn.stdout_file, time_usage, mem_usage);
                    }
                }
                else if(WTERMSIG(status) == SIGXCPU){
                    if(time_usage > timeLimit){
                        return return_result("TLE_SIG", EX_TLE, runIn.stdout_file, time_usage, mem_usage);
                    }
                }
                else if(WTERMSIG(status) == SIGKILL || WTERMSIG(status) == SIGABRT){
                    if(mem_usage > memoryLimit){
                        return return_result("MLE_SIG", EX_MLE, runIn.stdout_file, time_usage, mem_usage);
                    }
                    else if(time_usage > timeLimit){
                        return return_result("TLE_SIG", EX_TLE, runIn.stdout_file, time_usage, mem_usage);
                    }else
                        return return_result("Runtime Error", EX_RE, runIn.stdout_file, time_usage, mem_usage);
                }else return return_result("Runtime Error", EX_RE, runIn.stdout_file, time_usage, mem_usage);
            }
            ptrace(PTRACE_SYSCALL,child_pid,NULL,NULL);
	    }
	}
	return return_result("Run Error", EX_SUCCESS, runIn.stdout_file, time_usage, mem_usage);
}
void print_usage() {
	printf("Usage: %s [OPTION] PROGRAM \n", program_invocation_name);
	printf("Run and watch the contestant's PROGRAM. (Part of the Eeevee)\n");
	printf(
	    "Options:\n"
		"  -t, --time=TIME_LIMIT          in ms, positive int only (default is 1000)\n"
		"  -m, --memory=MEMORY_LIMIT      in KB, positive int only (default is 131072)\n"
		"  -l, --language=LANGUAGE        0:NONE,1:C,2:CPP\n"
		"      (file name must be identical with the problem description)\n"
        "  -p  --PID=PID                  PROGRAM ID"
		"  -h, --help                     print this help\n"
		"Output:\n"
		"  1.exited: WEXITSTATUS TIME(ms) MEMORY(KB)\n"
		"  2.killed: message\n"
		"Notes: PROGRAM must be compiled statically!\n");
	exit(EX_SUCCESS);
}
void parse_opt(int argc, char *  argv[]) {
	int longIndex = 0, opt = 0;
	opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	while (opt != -1) {
		switch (opt) {
			case 't':
				timeLimit = atoi(optarg);
				if (timeLimit <= 0) error(EX_ERROR, 0,
				  "TIME_LIMIT must be a positive integer.");
				break;
			
			case 'm':
				memoryLimit = atoi(optarg);
				if (memoryLimit <= 0) error(EX_ERROR, 0,
				  "MEMORY_LIMIT must be a positive integer.");
				break;
			
			case 'p':
				if (optarg == 0) error(EX_ERROR, 0, "INPUT_FILE missing.");
                pid = optarg;
				break;
			case 'h':
				print_usage();
				break;
			default:
				error(EX_ERROR, 0, 
				  "Please run 'caretaker --help' for more information.");
				break;
		}
		opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	}
	if (optind == argc) error(EX_ERROR, 0, "PROGRAM not specified.");
	else execDir = argv[optind];
}

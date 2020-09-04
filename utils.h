#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/syscall.h>
char *path_cat(const char *path, char *file) {
	size_t path_len = strlen(path), file_len = strlen(file);
	char *result;
	result = (char *)malloc((path_len + file_len + 2) * sizeof(*path));
	strcpy(result, path);
	result[path_len] = '/';
	strcpy(result + path_len + 1, file);
	//result[path_len + 1 + file_len] = '\0';
	return result;
}
char *path_cat(const char *path, const char *file) {
    size_t path_len = strlen(path), file_len = strlen(file);
    char *result;
    result = (char *)malloc((path_len + file_len + 2) * sizeof(*path));
    strcpy(result, path);
    result[path_len] = '/';
    strcpy(result + path_len + 1, file);
    //result[path_len + 1 + file_len] = '\0';
    return result;
}

int LANG_CV[256] = {0,1,2,3,4,5,8,9,11,12,20,21,59,63,89,158,231,240, SYS_time, SYS_read, SYS_uname, SYS_write, SYS_open,
                    SYS_close, SYS_execve, SYS_access, SYS_brk, SYS_munmap, SYS_mprotect,
                    SYS_mmap, SYS_fstat, SYS_set_thread_area, 252, SYS_arch_prctl, 0 };
int syscall_illegal(int callid){
    int white_list_length = 256;
    for(int i=0; i<white_list_length; ++i){
        if(LANG_CV[i] == callid)
            return 0; //合法
    }
    return 1; //非法
}
inline int tv2ms(struct timeval tv) {
	return (int) (tv.tv_usec / 1000) + tv.tv_sec * 1000;
}

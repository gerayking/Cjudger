
#ifndef JUDGER_UTILS_H
#define JUDGER_UTILS_H
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdio.h>
#include<unistd.h>

#include<sys/syscall.h>

inline int tv2ms(struct timeval tv) {
	return (int) (tv.tv_usec / 1000) + tv.tv_sec * 1000;
}
#endif //JUDGER_UTILS_H

/*
 * common.c
 *
 *  Created on: 2018-1-29
 *      Author: xuyang
 */
#include <stdio.h>
#include <stdarg.h>
#include "common.h"


static void pabort(const char *s)
{
    perror(s);
    abort();
}


/**
 * time farmat,e.g. 1970-01-01 08:07:58.951
 */
void getcurtime(char *dtime, uint32_t len)
{
	uint32_t need_l;
	struct timespec t;
	time_t time_of_day;
	char buffer[DATE_TIME_STR_LEN_MAX] = {0};

	time_of_day = time(NULL);
	clock_gettime (CLOCK_REALTIME, &t);

	strftime(buffer, DATE_TIME_STR_LEN_MAX, "%F %T.", localtime(&time_of_day));
	need_l = strlen(buffer);
	snprintf(&buffer[need_l], DATE_TIME_STR_LEN_MAX, "%ld", t.tv_nsec/1000000);

	if (need_l >= len)
	{
		pabort("getcurtime failed.\n");
		return;
	}

	strncpy(dtime, buffer, len);
}

/**
 * user msg length should be less than 88 bytes
 * e.g. [1970-01-01 09:17:00.887][SCREEN]receive msg,frame_id:0x4006
 */
int print_sys_msg(const char *module, const char *fmt, ...)
{
	int n;
	va_list args;
	char msg[PRINT_MSG_LEN_MAX] = {0};
	char now_tm[DATE_TIME_STR_LEN_MAX] = {0};

	getcurtime(now_tm, DATE_TIME_STR_LEN_MAX);

	va_start(args, fmt);
	n  = sprintf(msg, "[%s][%s]", now_tm, module);
	n += vsnprintf(&msg[n], PRINT_MSG_LEN_MAX, fmt, args);
	va_end(args);

	printf("%s", msg);

	return n;
}

int rel_slogf(const char *fmt, ...)
{
    int         status;
    va_list     arg;

    va_start(arg, fmt);
    status = vfprintf(stderr, fmt, arg);
    status += fprintf(stderr, "\n");
    va_end(arg);
    return status;
}

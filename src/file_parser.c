/*
 * common.c
 *
 *  Created on: 2018-1-29
 *      Author: xuyang
 */
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

#include "common.h"


int file_desc = -1;


int cal_offset(uint32_t signal_id)
{
	uint32_t i;
	uint32_t offset = 0;

	if (signal_id >= MAX_VIP_SIGNALL)
		return -1;

	for	(i = 0; i < signal_id; i++)
	{
		offset += vip_data[i].len;
	}

	return offset;
}


/*
 * create file
 */
int create_fle(char *path, char *name)
{
	int fd;

	char file_path_name[FILE_PATH_NAME_LEN_MAX] = "\0";

	/* use root directory for default*/
	if (!path || (*path=='\0'))
		strcpy(file_path_name, "/tmp");
	else
		strcpy(file_path_name, path);

	strcat(file_path_name, "/");

	if (!name || (*name=='\0'))
		strcat(file_path_name, "cn300.ini");
	else
		strcat(file_path_name, name);

	/* append to the end of an existing file */
	/* write a new file if file doesn't exist */
	/* with full read/write permissions */
	/*fd = open( file_path_name,
			O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );*/

	/* for test */
	if (file_desc != -1)
	{
		close(file_desc);
		remove(file_path_name);
	}

	fd = open(file_path_name, O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );

	return fd;
}


/*
 * global parm:file_desc
 */
int write_data(uint16_t signal_id, void* data, int len)
{
	uint32_t offset;
	off_t	o_value;
	ssize_t	w_value;

	// asert len == vip_data[signal_id].len

	offset = cal_offset(signal_id);

	o_value = lseek(file_desc, offset, SEEK_SET);

	if (o_value != offset)
	{
		printf("lseek sig:%d faild, need(%d), but(%d)\n", offset, o_value);
		return -1;
	}

	w_value = write(file_desc, data, vip_data[signal_id].len);

	if (w_value == -1 || (w_value != vip_data[signal_id].len))
	{
		printf("write sig:%d faild, need(%d), but(%d)\n", vip_data[signal_id].len, w_value);
		return -1;
	}

	return 0;
}

int read_data(uint32_t signal_id, void* buf, int len)
{
	uint32_t offset;
	off_t	o_value;
	ssize_t	r_value;


	offset = cal_offset(signal_id);

	o_value = lseek(file_desc, offset, SEEK_SET);

	if (o_value != offset)
	{
		printf("lseek sig:%d faild, need(%d), but(%d)\n", offset, o_value);
		return -1;
	}

	r_value = read(file_desc, buf, len);

	if (r_value == -1 || (r_value != len))
	{
		printf("read sig:%d faild, need(%d), but(%d)\n", len, r_value);
		return -1;
	}

	return 0;
}

void close_file(int fd)
{
	if(fd != -1)
	{
		close(fd);
	}
}

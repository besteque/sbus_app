/*
 * file_paser.h
 *
 *  Created on: 2018-1-26
 *      Author: xuyang
 */

#ifndef FILE_PASER_H_
#define FILE_PASER_H_

int create_fle(char *path, char *name);
int read_data(uint32_t signal_id, void* buf, int len);
int write_data(uint16_t signal_id, void* data, int len);
void close_file();


#endif /* FILE_PASER_H_ */

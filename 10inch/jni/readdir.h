/*
 * readdir.h
 *
 *  Created on: 2018年12月27日
 *      Author: shentq
 */

#ifndef JNI_READDIR_H_
#define JNI_READDIR_H_

#include "objectType.h"
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <vector>

bool read_dir(string path,stringList &list);
void make_dir(const char *path);
int rm_file(std::string &file_name);
bool is_access(string &path);
bool creat_file(string &fullName,const char *data,size_t size);
unsigned long get_file_size(const char *path);

void dispMemUsage();

#endif /* JNI_READDIR_H_ */

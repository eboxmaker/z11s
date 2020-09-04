/*
 * readdir.h
 *
 *  Created on: 2018年12月27日
 *      Author: shentq
 */

#ifndef JNI_READDIR_H_
#define JNI_READDIR_H_

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include "type.h"

using namespace std;

bool read_dir(string path,stringList &list);
void make_dir(const char *path);
int rm_file(string &file_name);
bool is_access(string &path);
bool creat_file(string &fullName,const char *data,size_t size);
unsigned long get_file_size(const char *path);

#endif /* JNI_READDIR_H_ */

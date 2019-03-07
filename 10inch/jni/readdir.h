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
#include "globalvar.h"
void read_dir();
void make_dir(char *path);
int rm_file(std::string &file_name);
bool is_access(string &path);
bool creat_file(string &fullName,const char *data,size_t size);
class FileOpt
{
	FileOpt();
	virtual ~FileOpt();

	bool is_access();
	bool make_dir(string &path);
	bool rm_dir(string &path);
	stringList read_dir(string &path);

	bool rm_file(string &file_full_name);

};

#endif /* JNI_READDIR_H_ */

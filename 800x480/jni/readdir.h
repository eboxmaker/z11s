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
stringList get_all_ad_full_name();


#endif /* JNI_READDIR_H_ */

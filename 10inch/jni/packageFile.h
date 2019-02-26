/*
 * packageFile.h
 *
 *  Created on: 2018年12月21日
 *      Author: Administrator
 */

#ifndef JNI_PACKAGEFILE_H_
#define JNI_PACKAGEFILE_H_

#include "json/json.h"
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>


std::string GetFileName(char *str);
bool SaveFile(char *str, char* directory);



#endif /* JNI_PACKAGEFILE_H_ */

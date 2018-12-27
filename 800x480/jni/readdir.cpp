/*
 * readdir.cpp
 *
 *  Created on: 2018年12月27日
 *      Author: shentq
 */




#include "readdir.h"
#include "utils/log.h"

void read_dir()
{
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir("/mnt/extsd/"); ///open the dir

    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {

            LOGE("d_type:%d d_name: %s\n", ptr->d_type,ptr->d_name);
    }
    closedir(dir);
    return 0;
}

/*
 * readdir.cpp
 *
 *  Created on: 2018年12月27日
 *      Author: shentq
 */




#include "readdir.h"
#include "utils/log.h"
#include <sys/stat.h>
#include <string.h>
//#include <sys/types.h>
//#include <stdio.h>
//#include <stdlib.h>

using namespace std;
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


stringList get_all_ad_full_name()
{
	stringList list;

    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(AD_DIR); ///open the dir

    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {
        string fullNmae = AD_DIR;


    	if(ptr->d_type == 8)
    	{
    		fullNmae += ptr->d_name;
    		list.push_back(fullNmae.c_str());
    	}

    //	LOGE("d_type:%d d_name: %s\n", ptr->d_type,ptr->d_name);
    }
    closedir(dir);
    return list;
}
void make_dir(char *path)
{
	if (access(path, F_OK) < 0)
	{
	   int isCreate = mkdir(path,S_IRUSR| S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
	   if( !isCreate )
	   LOGE("create path:%s\n",path);
	   else
		   LOGE("create path failed! error code : %s \n",isCreate,path);
	}
	else
	{
		LOGE("文件夹已存在");
	}

}

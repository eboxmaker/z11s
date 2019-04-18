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
//void read_dir()
//{
//    DIR    *dir;
//    struct    dirent    *ptr;
//    dir = opendir("/mnt/extsd/"); ///open the dir
//
//    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
//    {
//    	LOGE("d_type:%d d_name: %s\n", ptr->d_type,ptr->d_name);
//    }
//    closedir(dir);
//    return 0;
//}

bool read_dir(string path,stringList &list)
{
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(path.c_str()); ///open the dir

    if(dir == NULL)
    	return false;
    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {
    	if(ptr->d_type == 8)//file
    	{
    		list.push_back(ptr->d_name);
    	}else if(ptr->d_type == 10)//link file
    	{

    	}else if(ptr->d_type == 4)//dir
    	{

    	}
    	//LOGE("d_type:%d d_name: %s\n", ptr->d_type,ptr->d_name);
    }
    closedir(dir);
    return true;
}
bool is_access(string &path)
{
	if (access(path.c_str(), F_OK) < 0)
	{
		LOGD("%s.文件不存在",path.c_str());
		return false;
	}
	else
	{
		return true;
	}
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

//recursively delete all the file in the directory.
bool rm_dir(std::string dir_full_path)
{
    DIR* dirp = opendir(dir_full_path.c_str());
    if(!dirp)
    {
        return -1;
    }
    struct dirent *dir;
    struct stat st;
    while((dir = readdir(dirp)) != NULL)
    {
        if(strcmp(dir->d_name,".") == 0
                || strcmp(dir->d_name,"..") == 0)
        {
            continue;
        }
        std::string sub_path = dir_full_path + '/' + dir->d_name;
        if(lstat(sub_path.c_str(),&st) == -1)
        {
            LOGE("rm_dir:lstat ",sub_path.c_str()," error");
            continue;
        }
        if(S_ISDIR(st.st_mode))
        {
            if(rm_dir(sub_path) == -1) // 如果是目录文件，递归删除
            {
                closedir(dirp);
                return -1;
            }
            rmdir(sub_path.c_str());
        }
        else if(S_ISREG(st.st_mode))
        {
            unlink(sub_path.c_str());     // 如果是普通文件，则unlink
        }
        else
        {
        	LOGE("rm_dir:st_mode ",sub_path.c_str()," error");
            continue;
        }
    }
    if(rmdir(dir_full_path.c_str()) == -1)//delete dir itself.
    {
        closedir(dirp);
        return -1;
    }
    closedir(dirp);
    return 0;
}
//删除文件，如果是目录则删除整个目录
int rm_file(std::string &file_name)
{
    std::string file_path = file_name;
    struct stat st;
    if(lstat(file_path.c_str(),&st) == -1)
    {
        return -1;
    }
    if(S_ISREG(st.st_mode))
    {
        if(unlink(file_path.c_str()) == -1)
        {
            return -1;
        }
    }
    else if(S_ISDIR(st.st_mode))
    {
        if(file_name == "." || file_name == "..")
        {
            return -1;
        }
        if(rm_dir(file_path) == -1)//delete all the files in dir.
        {
            return -1;
        }
    }
    return 0;
}

bool creat_file(string &fullName,const char *data,size_t size)
{
	size_t writed;
	FILE *fp = fopen(fullName.c_str(), "w");
	if (fp != NULL)
	{
		 writed = fwrite(data, sizeof(char), size, fp);
		 if(writed != size){
				LOGE("写入文件错误");
				return false;
		 }

	}
	else
	{
		LOGE("打开文件错误");
		return false;
	}
	if (fclose(fp) != 0) {
		LOGE("关闭文件错误");
		return false;
	}
	return true;
}
unsigned long get_file_size(const char *path)
{
	unsigned long filesize = -1;
	FILE *fp;
	fp = fopen(path, "r");
	if(fp == NULL)
		return filesize;
	fseek(fp, 0L, SEEK_END);
	filesize = ftell(fp);
	fclose(fp);
	return filesize;
}
#include <sys/sysinfo.h>

void dispMemUsage()
{
	struct sysinfo systemInfo;
	float memUsage;

    sysinfo(&systemInfo);
    memUsage = (1 - ((float)systemInfo.freeram/(float)systemInfo.totalram))*100;
    LOGO("%0.1f%%(%0.2fM/%0.2fM)",memUsage,systemInfo.freeram/1024.0/1024.0,systemInfo.totalram/1024.0/1024.0);

}

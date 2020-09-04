/*
 * type.h
 *
 *  Created on: 2020年3月19日
 *      Author: Administrator
 */

#ifndef JNI_TYPE_H_
#define JNI_TYPE_H_

#include <string>
#include <vector>
using namespace std;

typedef std::vector<std::string> stringList;
typedef std::vector<int> IntList;
typedef std::vector<uint16_t> uint16List;




//设备信息结构体


//系统更新结网址构体
typedef struct
{
	string url;
	int port;
}HttpInfo_t;



//用户存储json传递过来的图片。
typedef struct
{
	string name;
	long dataLength;
	string data;
}Picture_t;

typedef struct
{
	string name;
	string class_;
	string num;
	string course;
//	string time_start;
//	string time_end;
	Picture_t picture;
}CourseInfo_t;



typedef union
{
    unsigned char byte[4];
    uint16_t halfWord[2];
    float value;
} DataFloat_t;
typedef union
{
    uint8_t byte[2];
    int16_t value;
} Data16_t;
typedef union
{
    uint8_t byte[2];
    uint16_t value;
} DataU16_t;
typedef union
{
    uint8_t byte[4];
    DataU16_t u16[2];
    uint32_t value;
} DataU32_t;
typedef union
{
    uint8_t byte[4];
    Data16_t i16[2];
    uint16_t halfWord[2];
    int32_t value;
} Data32_t;


//限制某个数的下界
template<typename T>
void limitLow(T &num, T limL)
{
    if (num < limL)
    {
        num = limL;
    }
}

//限制某个数的上界
template<typename T>
void limitHigh(T &num, T limH)
{
    if (num > limH)
    {
        num = limH;
    }
}


//限制某个数的上下界
template<typename T>
void limit(T &num, T limL, T limH)
{
    limitLow(num, limL);
    limitHigh(num, limH);
}


#endif /* JNI_TYPE_H_ */

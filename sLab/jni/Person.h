/*
 * Person.h
 *
 *  Created on: 2020年9月2日
 *      Author: shentq
 */

#ifndef JNI_PERSON_H_
#define JNI_PERSON_H_
#include "type.h"
#include "lib/base64.h"
#include "system/Thread.h"

namespace std {


//录入指纹时传递的信息
typedef struct
{
	string 	name;
	string 	id;
	string	level;
	string 	lockCtr;
	stringList fingers;
}PersonInfo_t;
typedef vector<PersonInfo_t> PersonInfoList_t;
extern PersonInfoList_t gPersonList;

class Person : public Thread
{
public:
	Person();
	virtual ~Person();
	void update(PersonInfoList_t &list);

protected:
	virtual bool readyToRun();
	virtual bool threadLoop();


public:
	PersonInfoList_t list_;
};
extern Person gPerson;
} /* namespace std */

#endif /* JNI_PERSON_H_ */

/*
 * Person.h
 *
 *  Created on: 2019年6月22日
 *      Author: shentq
 */

#ifndef JNI_PERSON_H_
#define JNI_PERSON_H_

#include "objectType.h"
#include "lib/base64.h"
#include "lib/finger.h"
#include "utils/log.h"
namespace std {

//录入指纹时传递的信息
typedef struct
{
	string name;
	string id;
	int	   level;
	stringList fingers;
	Picture_t picture;

}PersonAll_t;
//
typedef struct
{
	string 	id;
	string 	name;
	int	   	level;
	uint16List	finger_id;
	string 	picture_name;
}PersonInfo_t;

typedef vector<PersonInfo_t> PersonList;


class Person {
public:
	Person();
	virtual ~Person();

	void add(PersonAll_t &person);
	void delete_uid(string id);
	bool get_person_by_uid(string id,PersonInfo_t *person);
	bool get_person_by_finger_id(uint16_t id,PersonInfo_t *person);
	stringList get_features(string id);
	uint16_t get_total_fingers();
	uint16_t get_total_persons();
	bool is_exist(PersonAll_t &person);
	bool update_person(PersonInfo_t &person);

private:

	int  update_list(PersonAll_t &person);
	PersonList list;

};

} /* namespace std */

#endif /* JNI_PERSON_H_ */

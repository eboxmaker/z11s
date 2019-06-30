/*
 * Person.cpp
 *
 *  Created on: 2019年6月22日
 *      Author: shentq
 */

#include "Person.h"

namespace std {
void copyPersonAllToPersonInfo(PersonTrans_t &p1, PersonInfo_t *p2)
{
	p2->id = p1.id;
	p2->name = p1.name;
	p2->level = p1.level;
	p2->picture_name = p1.picture.name;

}
Person::Person() {
	// TODO 自动生成的构造函数存根

}

Person::~Person() {
	// TODO 自动生成的析构函数存根
}



void Person::add(PersonTrans_t &person){
//		LOGD("执行添加person,finger size:%d",person.fingers.size());
	PersonInfo_t temp;
	temp.id = person.id;
	temp.name = person.name;
	temp.level = person.level;
	temp.picture_name = person.picture.name;
	temp.finger_id.clear();
	for(int i = 0; i < person.fingers.size();i++){
		uint16_t id  = 0;
		if(finger.add_featurs_sync(&id, person.fingers[i]) == true)
			temp.finger_id.push_back(id);
		else
			LOGD("最终添加失败");
	}

	bool is_exist = false;
	for(int i = 0; i < list.size(); i++)
	{
		if(list[i].id == temp.id){
			list[i] = temp;
			is_exist = true;
		}
	}
	if(is_exist == false)
		list.push_back(temp);

	for(int i = 0; i < list.size(); i++)
	{
		LOGD("user id:%s",list[i].id.c_str());
	}

}
void Person::delete_uid(string id){

	vector<PersonInfo_t>::iterator it = list.begin();
    while((it) != list.end()){
    	if((*it).id == id){
    		list.erase(it);
    		break;
    	}
    	else{
    		it++;
    	}
    }
}
bool Person::get_person_by_uid(string id,PersonInfo_t *person){
	vector<PersonInfo_t>::iterator it = list.begin();
    while((it) != list.end()){
    	if((*it).id == id){
    		*person = *it;
    		return true;
    	}
    	else{
    		it++;
    	}
    }
    return false;
}

bool Person::get_person_by_finger_id(uint16_t id,PersonInfo_t *person){
	for(int i = 0; i < list.size(); i++)
	{
		for(int j = 0; j <list[i].finger_id.size(); j++){
			LOGD("person finger id list :%d",list[i].finger_id[j]);
			if(id == list[i].finger_id[j]){
				*person = list[i];
				LOGD("通过指纹(%d)查找到此人:%s",id,person->id.c_str());
				return true;
			}
		}
	}
	LOGD("未通过指纹(%d)查找到此人",id);
	return false;
}

stringList Person::get_features(string id)
{
	PersonInfo_t p;
	stringList f_list;
	char buf[256];

	get_person_by_uid(id,&p);
	for(int i = 0; i < p.finger_id.size(); i++){
		finger.get_id_features(p.finger_id[i],buf);
		f_list.push_back(buf);
	}
}

bool Person::is_exist(PersonTrans_t &person)
{
	vector<PersonInfo_t>::iterator it = list.begin();
    while((it) != list.end()){
    	if((*it).id == person.id){
    		return true;
    	}
    	else{
    		it++;
    	}
    }
    return false;
}
int  Person::update_list(PersonTrans_t &person)
{

}
bool Person::update_one_person(PersonInfo_t &person){
	for(int i = 0; i < list.size(); i++)
	{
		if(person.id == list[i].id){
			list[i] = person;
			LOGD("更新人员列表成功:%s,指纹数量：%d",person.id.c_str(),list[i].finger_id.size());
			return true;
		}
	}
	LOGD("更新人员列表失败:%s",person.id.c_str());
	return false;
}
int Person::size()
{
	return list.size();
}
int Person::size(int level)
{
	int counter = 0;
	for(int i = 0; i < list.size(); i++)
	{
		if(list[i].level == level)
		{
			counter++;
		}
	}
	return counter;
}



} /* namespace std */

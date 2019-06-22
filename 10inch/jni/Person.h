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

}PersonDump_t;
//
typedef struct
{
	string 	id;
	string 	name;
	int	   	level;
	uint16List	finger_id;
	string 	picture_name;
}Person_t;

typedef vector<Person_t> PersonList;


class Person {
public:
	Person();
	virtual ~Person();

	void add(PersonDump_t &person){
		LOGD("执行添加person,finger size:%d",person.fingers.size());
		Person_t temp;
		temp.id = person.id;
		temp.name = person.name;
		temp.level = person.level;
		temp.picture_name = person.picture.name;
		for(int i = 0; i < person.fingers.size();i++){
//			Base64::Encode(data, len, out, 1024)
			string out = "";
			uint16_t id = i+1;
			Base64::Decode(person.fingers[i], &out);
//			LOGD("bas64:%s",person.fingers[i].c_str());
//			for(int j =0;j<out.size();j++)
//				LOGD("%d:%d",j,out.c_str()[j]);

//			if(finger.get_free(1, 100, &id) == true){
				LOGD("id：%d",id);

				if(finger.setIdFeatures(id, out.c_str()) == true)
				{
					LOGD("添加指纹成功");
				}
				else{
					LOGD("添加指纹失败");
				}
				temp.finger_id.push_back(id);
//			}
//			else
//			{
//				LOGD("没有在指纹模块中找到合适得位置");
//			}
		}
		list.push_back(temp);
	}
	void delete_uid(string id){

		vector<Person_t>::iterator it = list.begin();
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

	bool query_uid(string id,Person_t *person){
		vector<Person_t>::iterator it = list.begin();
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
	Person_t query_finger_id(uint16_t id){
//		vector<Person_t>::iterator it = list.begin();
//        while((it) != list.end()){
//        	for()
//        	if((*it).id == id){
//        		return *it;
//        	}
//        	else{
//        		it++;
//        	}
//        }
//		return NULL;
	}

private:

	PersonList list;

};

} /* namespace std */

#endif /* JNI_PERSON_H_ */

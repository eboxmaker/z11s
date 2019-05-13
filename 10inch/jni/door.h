/*
 * door.h
 *
 *  Created on: 2019年4月11日
 *      Author: shentq
 */

#ifndef JNI_DOOR_H_
#define JNI_DOOR_H_

namespace std {

	typedef enum {HighLock,HighOpen,None}LockLogic_t;
	//门锁状态结构体
	typedef enum
	{
		Lock,
		UnLock,
	}doorState_t;

	typedef enum
	{
		Open_Lock,
		Open_Unlock,
		Close_Lock,
		Close_Unlock,
	}doorFullState_t;

	struct MagnetState {
	    enum __Enum {
	        Open = 0,
	        Close ,
	        Unkonw
	    };
	    __Enum _value; // 枚举值

	    MagnetState(int value = 0) : _value((__Enum)value) {}
	    MagnetState& operator=(int value) {
	        this->_value = (__Enum)value;
	        return *this;
	    }
	    operator int() const {
	        return this->_value;
	    }
	};
	struct TongueState {
	    enum __Enum {
	        Lock = 0,
	        Unlock ,
			Unkonw,
	    };
	    __Enum _value; // 枚举值

	    TongueState(int value = 0) : _value((__Enum)value) {}
	    TongueState& operator=(int value) {
	        this->_value = (__Enum)value;
	        return *this;
	    }
	    operator int() const {
	        return this->_value;
	    }
	};
class Door {
public:
	Door();
	virtual ~Door();
	void set(doorState_t state);
	doorState_t get();

	LockLogic_t LockLogic;
	LockLogic_t TongueLogic;
	LockLogic_t MagnetLogic;

private:
	MagnetState getMagnet();
	TongueState getTongue();
	doorFullState_t getFull();


};
extern Door door;

} /* namespace std */

#endif /* JNI_DOOR_H_ */

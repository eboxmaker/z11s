/*
 * enum_def.h
 *
 *  Created on: 2019年5月13日
 *      Author: shentq
 */

#ifndef JNI_ENUM_DEF_H_
#define JNI_ENUM_DEF_H_



#define DECLARE_ENUM(E) \
struct E \
{ \
public: \
    E(int value = 0) : _value((__Enum)value) { \
    } \
    E& operator=(int value) { \
        this->_value = (__Enum)value; \
        return *this; \
    } \
    operator int() const { \
        return this->_value; \
    } \
\
    enum __Enum {

#define END_ENUM() \
    }; \
\
private: \
    __Enum _value; \
};

#endif /* JNI_ENUM_DEF_H_ */

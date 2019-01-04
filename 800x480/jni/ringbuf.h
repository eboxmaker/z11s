/**
  ******************************************************************************
  * @file    color_convert.h
  * @author  shentq
  * @version V1.2
  * @date    2016/08/14
  * @brief
  ******************************************************************************
  * @attention
  *
  * No part of this software may be used for any commercial activities by any form
  * or means, without the prior written consent of shentq. This specification is
  * preliminary and is subject to change at any time without notice. shentq assumes
  * no responsibility for any errors contained herein.
  * <h2><center>&copy; Copyright 2015 shentq. All Rights Reserved.</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RINGBUF_H
#define __RINGBUF_H

#include "stdio.h"
#include "system/mutex.h"
#include "utils/Log.h"

template <class T>
class RingBuf
{


public:
    RingBuf()
    {
        head = 0;
        tail = 0;
        ptr = 0;
    }


    ~RingBuf()
    {
        free(ptr);
    }

    bool begin(uint32_t size)
    {
        ptr = (T *)malloc(size * sizeof(T));
        max = size;
        //        ebox_printf("xx\r\n");
        //        ebox_printf_flush();
        if(ptr != NULL)
            return true;
        else
            return false;

    }
    bool write(T c)
    {
        //        __disable_irq();
        int seek = (head + 1) % max;

        // If the output buffer is full, there's nothing for it other than to
        // wait for the interrupt handler to empty it a bit
        if (seek == tail)
        {
        	ptr = (T *)realloc((void *)ptr, max * sizeof(T) +  1024 * sizeof(T));
        	max += 1024;
        	seek = (head + 1) % max;
        	//LOGE("扩充内存:%d",max);
        }
        ptr[head] = c;
        head = seek;
        //        __enable_irq();
        return true;

    }



    T read(void)
    {
        //        __disable_irq();
        // if the head isn't ahead of the tail, we don't have any characters
        if (head == tail)
        {
            return 0;
        }
        else
        {
            T c = ptr[tail];
            tail = (unsigned int)(tail + 1) % max;
            return c;
        }

    }
    int available()
    {

        //        __disable_irq();
        int len = (int)(max + head - tail) % max;
        //        __enable_irq();

        return len;
    }
    void clear()
    {
        head = 0;
        tail = 0;
        for(int i = 0; i < max; i++)
        {
            ptr[i] = 0;
        }
    }

    bool isfull()
    {
        //        __disable_irq();
        int seek = ((head + 1) % max);
        //        __enable_irq();

        if(seek == tail)
            return true;
        else
            return false;
    }
private:
    volatile int head;
    volatile int tail;
    int max;
    T *ptr;
;
};
typedef RingBuf<uint8_t>    RingBufUint8;
typedef RingBuf<int8_t>     RingBufInt8;
typedef RingBuf<uint16_t>   RingBufUint16;
typedef RingBuf<int16_t>    RingBufInt16;
typedef RingBuf<uint32_t>   RingBufUint32;
typedef RingBuf<int32_t>    RingBufInt32;
typedef RingBuf<long>       RingBufLong;
typedef RingBuf<float>      RingBufFloat;
typedef RingBuf<double>     RingBufDouble;


#endif

/**********************************************************
 * Author        : geqiankun
 * Email         : scugqk@gmail.com
 * Last modified : 2017-12-07 20:15
 * Filename      : singleton.h
 * Description   : 
 * *******************************************************/

//learn from kbe
//class A: public<Singleton> {};
//in cpp: SINGLETON_INIT(A)
#ifndef _SINGLETON_H
#define _SINGLETON_H

#include "util/comm.h"

namespace util{
    
template<typename T>
    class Singleton{
    protected:
        static T* singleton_;
    public:
        Singleton(void) {
            assert(!singleton_);
            singleton_ = static_cast<T*>(this);
//            int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
//            singleton_ = (T*)((int)this + offset);
        }
        ~Singleton(void) {
            assert(singleton_);
            singleton_ = 0;
        }
        static T& getSingleton(void) {
            assert(singleton_);
            return (*singleton_);
        }
        static T* getSingletonPtr(void) {
            return singleton_;
        }
    };

#define SINGLETON_INIT(TYPE)   \
    template<> TYPE* Singleton<TYPE>::singleton_ = 0;

}

#endif

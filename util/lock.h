/**********************************************************
 * Author        : geqiankun
 * Email         : scugqk@gmail.com
 * Last modified : 2017-12-07 20:57
 * Filename      : lock.h
 * Description   : 
 * *******************************************************/

#ifndef _LOCK_H

#include "util/comm.h"
#include "util/noncopyable.h"
#include <pthread.h>

//class A{
//  private: Lock lock_;
//  func(){
//      LockGuard guard(lock_); //实现资源自动控制
//  }
//}
namespace util{

class Lock: noncopyable {
public:
    Lock() {
        pthread_mutex_init(&lock_, NULL);
    }
    ~Lock() {
        pthread_mutex_destroy(&lock_);
    }
    void lock() const {
        pthread_mutex_lock(&lock_);
    }
    void unlock() const {
        pthread_mutex_unlock(&lock_);
    }
    bool trylock() const {
        int ret = pthread_mutex_trylock(&lock_);
        if (0 != ret) {
            return false;
        }
        return true;
    }
private:
    mutable pthread_mutex_t lock_;
};

#ifdef UNIX
class SpinLock: noncopyable {
public:
    SpinLock() {
        pthread_spin_init(&lock_, NULL);
    }
    ~SpinLock() {
        pthread_spin_destroy(&lock_);
    }
    void lock() const {
        pthread_spin_lock(&lock_);
    }
    void unlock() const {
        pthread_spin_unlock(&lock_);
    }
    bool trylock() const {
        int ret = pthread_spin_trylock(&lock_);
        if (0 != ret) {
            return false;
        }
        return true;
    }
private:
    mutable pthread_spinlock_t lock_;
};
#endif

template<typename Type>
class LockGuardImpl : noncopyable {
public:
    explicit LockGuardImpl(Type& lock):lock_(lock),isLocked(true) {
        lock_.lock();
    }
    ~LockGuardImpl() {
        if (isLocked) {
            lock_.unlock();
        }
    }
private:
    Type& lock_;
    bool isLocked;
};

typedef LockGuardImpl<Lock> LockGuard;

}

#endif

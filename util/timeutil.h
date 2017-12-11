/**********************************************************
 * Author        : geqiankun
 * Email         : scugqk@gmail.com
 * Last modified : 2017-12-11 20:55
 * Filename      : timeutil.h
 * Description   : 
 * *******************************************************/

#ifndef _TIMEUTIL_H
#define _TIMEUTIL_H

#include "util/comm.h"
#include <sys/time.h>
#include <string>

namespace util{

std::string timePrint(time_t t, const char* format);

inline std::string timeNow(const char* format) {
    time_t time(NULL);
    return timePrint(time, format);
}

inline uint64 timeStampNow() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

inline uint64 timeStamp(const struct timeval& tv) {
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

inline struct timeval toTimeval(uint64 time) {
    return { t/1000000, t%1000000 };
}

inline uint64 timePassed(uint64 ts) {
    return timeStampNode() - ts;
}

}

#endif

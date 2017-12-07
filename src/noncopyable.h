#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

// copy from boost
namespace util{

namespace noncopyable_{
    class noncopyable{
    protected:
        noncopyable() {}
        ~noncopyable() {}
    private:
        noncopyable( const noncopyable& );
        noncopyable& operator=( const noncopyable& );
    };
}

typedef noncopyable_::noncopyable noncopyable;

}

#endif

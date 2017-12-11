/**********************************************************
 * Author        : geqiankun
 * Email         : scugqk@gmail.com
 * Last modified : 2017-12-11 10:00
 * Filename      : strtools.h
 * Description   : 
 * *******************************************************/

#ifndef _STRTOOLS_H
#define _STRTOOLS_H

#include <string>
#include <vector>

void split(const std::string& str, std::vector<std::string>& v, const std::string& c) {
    std::string::size_type pos1, pos2;
    pos2 = str.find(c);
    pos1 = 0;
    while (std::string::npos != pos2) {
        v.push_back(str.substr(pos1, pos2-pos1));
        pos1 = pos2 + c.size();
        pos2 = str.find(c, pos1);
    }
    if (pos1 != str.length()) {
        v.push_back(str.substr(pos1));
    }
}

#endif

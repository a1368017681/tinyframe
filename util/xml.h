/**********************************************************
 * Author        : geqiankun
 * Email         : scugqk@gmail.com
 * Last modified : 2017-12-08 10:10
 * Filename      : xml.h
 * Description   : 
 * *******************************************************/

#ifndef _XML_H
#define _XML_H

#include "util/comm.h"
#include "strtools.h"
#include <string>
#include <vector>
#include <libxml/tree.h>
#include <libxml/parser.h>

namespace util{

namespace xml{

class XmlNode {
public:
    XmlNode(xmlNodePtr node = NULL): node_(node) {}

    std::string getContent() const {
        if (node_) {
            for (xmlNodePtr it = node_->children; it; it = it->next) {
                if (!xmlStrcmp(it->name, BAD_CAST "text")) {
                    return (const char*)it->content;
                }
            }
        }
        return "";
    }

    XmlNode findNode(const std::string& name) const {
        if (node_) {
            if (0 == xmlStrcmp(node_->name, BAD_CAST name.c_str())) {
                return XmlNode(node_);
            }
            for(auto child = node_->children; child; child = child->next) {
                XmlNode node(child);
                XmlNode ret = findNode(name);
                if (ret.isValid()) {
                    return ret;
                }
            }
        }
        return XmlNode();
    }

    XmlNode findNextSibling(const std::string& name) const {
        if (node_) {
            for (auto sibling = node_->next; sibling; sibling = sibling->next) {
                if (0 == xmlStrcmp(sibling->name, BAD_CAST name.c_str())) {
                    return XmlNode(sibling);
                }
            }
        }
        return XmlNode();
    }

    XmlNode operator[](const std::string& name) const {
        return findNode(name);
    }

    operator bool() {
        return NULL != node_;
    }

    bool isValid() const {
        return NULL != node_;
    }
private:
    xmlNodePtr node_;
};

inline XmlNode getNode(XmlNode node, const std::vector<std::string>& path) {
    for (auto it = path.cbegin(); it != path.cend(); ++it) {
        node = node.findNode(*it);
        if (!node) {
            return XmlNode();
        }
    }
    return node;
}

inline XmlNode getNode(XmlNode node, const std::string& path) {
    std::vector<std::string> v;
    split(path, v, ".");
    return getNode(node, v);
}

inline std::vector<XmlNode> getNodeList(XmlNode root, const std::string& path) {
    std::vector<std::string> v;
    split(path, v, ".");
    XmlNode node = getNode(root, v);
    std::vector<XmlNode> nodes;
    while (node) {
        nodes.push_back(node);
        node = node.findNextSibling(v.back());
    }
    return nodes;
}

class XmlParser {
public:
    XmlParser(const std::string& file_name) {
        doc_ = xmlParseFile(file_name.c_str());
    }

    XmlNode getRoot() const {
        return xmlDocGetRootElement(doc_);
    }

    XmlNode getNode(const std::string& path) const {
        return xml::getNode(getRoot(), path);
    }

    XmlNode getNode(const std::vector<std::string>& path) const {
        return xml::getNode(getRoot(), path);
    }

    std::vector<XmlNode> getNodeList(const std::string& path) const {
        return xml::getNodeList(getRoot(), path);
    }

    std::string getValue(const std::string& path, const char* dflt) {
        XmlNode node = getNode(path);
        std::string content = node ? node.getContent(): "";
        return !content.empty() ? content : dflt;
    }
private:
    xmlDocPtr doc_;
};

}

}

#endif



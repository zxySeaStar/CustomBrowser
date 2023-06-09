#ifndef _XML_NAIVE_PARSER_H_
#define _XML_NAIVE_PARSER_H_
#include <stdint.h>
#include <vector>
#include <string>
class XmlNaiveNode{
public:
        std::string blockTag;
        std::string blockContent;
        std::vector<std::pair<std::string,std::string>> attributeList;
        std::string attribute(std::string _key)
        {
            for(auto &item:attributeList)
            {
                if(item.first == _key)
                {
                    return item.second;
                }
            }
            return std::string();
        }
};

class XmlNaiveParser
{
public:
    enum CharType{
        CharBlockTag = 0x1, // A-Z,a-z,0-9,space,other visable text except "<" ">" "space"
        CharBlockContent = 0x2, // A-Z,a-z,0-9,space,other visable text except "<" ">"
        CharSpace = 0x4, // ' ','\t','\r','\n'
        CharAttribute = 0x8, // A-Z,a-z,0-9 other visable text except """ "="
    };

    const uint8_t _CharTable[256]= {
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x06,0x0B,0x03,0x0B,0x0B,0x0B,0x0B,0x0B, // space, !, ",# ...
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B, // 0,1,2...
        0x0B,0x0B,0x0B,0x0B,0x00,0x03,0x00,0x0B, // <,>

        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B, // @,A,B
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,

        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B, // ',a,b
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,

        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B, // 128+
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
        0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B
    };

    bool LoadBuffer(std::string &_buffer);
    void Test();

    std::vector<XmlNaiveNode> _ChildNodeList;

private:
    bool isChar(uint8_t _char, CharType _type);
};

#endif

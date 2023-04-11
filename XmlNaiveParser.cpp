#include "XmlNaiveParser.h"
#include <iostream>
bool XmlNaiveParser::LoadBuffer(std::string &_buffer)
{
    std::string buffer = _buffer;
    std::vector<XmlNaiveNode> blockList;
    int index = 0;
    int count = buffer.size();
    while(index < count)
    {
        XmlNaiveNode node;
        if(buffer[index]=='<')
        {
            // locate the tag, record all the accurate value: A-Z,a-z,0-9, no space

            //int tempIndex = index+1;
            index++;
            // get the tag name
            while(index < count && isChar(buffer[index], CharType::CharBlockTag))
            {
                node.blockTag.push_back(buffer[index++]);
            }

            // get the attribute
            while(index < count)
            {
                // skip the space
                while(index < count && isChar(buffer[index], CharType::CharSpace))
                {
                    index++;
                }
                // get the termination
                if(index < count && buffer[index]=='>')
                {
                    index++;
                    break;
                }
                else
                {
                    std::string attributeName;
                    std::string attributeValue;
                    while(index < count && isChar(buffer[index], CharType::CharAttribute))
                    {
                        attributeName.push_back(buffer[index++]);
                    }
                    if(index >= count || buffer[index]!='=')
                    {
                        return false;
                    }
                    index++;
                    if(index >= count || buffer[index]!='\"')
                    {
                        return false;
                    }
                    index++;
                    while(index < count && isChar(buffer[index], CharType::CharAttribute))
                    {
                        attributeValue.push_back(buffer[index++]);
                    }
                    if(index >= count || buffer[index]!='"')
                    {
                        return false;
                    }
                    node.attributeList.push_back(std::make_pair(attributeName,attributeValue));
                    index++;
                }
            }

            // get the content until <
            while(index < count && isChar(buffer[index], CharType::CharBlockContent))
            {
                node.blockContent.push_back(buffer[index++]);
            }

            if(index >= count || buffer[index]!='<')
            {
                return false;
            }
            index++;
            if(index >= count || buffer[index]!='/')
            {
                return false;
            }
            index+=1;
            std::string tempTag;
            while(index < count && isChar(buffer[index], CharType::CharBlockTag))
            {
                tempTag.push_back(buffer[index++]);
            }
            if(tempTag!=node.blockTag) // match the blocktag
            {
                return false;
            }
            // skip the space
            while(index < count && isChar(buffer[index],CharType::CharSpace))
            {
                index++;
            }
            if(index >= count || buffer[index]!='>')
            {
                return false;
            }
            index+=1;
        }
        else
        {
            // get all the char: A-Z,a-z,0-9,space,other visable text except "<" ">"
            while(index < count && isChar(buffer[index],CharType::CharBlockContent))
            {
                node.blockContent.push_back(buffer[index++]);
            }
        }

        if(node.blockContent.size()==0 && node.blockTag.size()==0)
        {
            std::cout << "empty" << std::endl;
            return false;
        }
        blockList.push_back(node);
    }
    _ChildNodeList = std::move(blockList);
    return true;
}

void XmlNaiveParser::Test()
{
    std::string data = "123<font color=\"red\" nihao=\"dajiahao\">n@ i/h ao</font >122 A3<font>n@ i/h ao</font >";
    bool isSuccess = LoadBuffer(data);
    std::cout << "result:" << isSuccess << std::endl;
    // display the blockList
    for(auto& item: _ChildNodeList)
    {
        std::cout<< item.blockTag << ":" << item.blockContent << std::endl;
        for(auto & subItem:item.attributeList)
        {
            std::cout << "\t" << subItem.first << ":" << subItem.second << std::endl;
        }
    }
}

bool XmlNaiveParser::isChar(uint8_t _char,  CharType _type)
{
    /* TODO */
    return _CharTable[_char& 0xFF] & _type;
}

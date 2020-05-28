//
//  ConfigMgr.hpp
//  Config Manager
//
//  Created by Danny on 2020/5/28.
//  Copyright © 2020 Danny. All rights reserved.
//

#ifndef ConfigMgr_hpp
#define ConfigMgr_hpp

#include <string>
#include<regex>
#include<map>
#include<fstream>
#include<sstream>
#include<iostream>
#define BUFFER_SIZE 1000

namespace cfg
{
    // each section;
    struct ReadException:public std::exception
    {
        std::string description;
        ReadException(const std::string & desc):description(desc){}
        const char * what()const throw()
        {
            return description.c_str();
        }
    };

    class Config
    {
    public:
        Config()= default;
        Config(const std::string &section_name);
        std::string section;
        std::string& operator[] (const std::string & key);
        std::string& at(const std::string& key);
        void remove(const std::string& key);
        void insert(std::pair<std::string ,std::string> key_val);
        std::string to_string();
    private:
        std::map<std::string ,std::string> configs;
    };

    class ConfigMgr
    {
    public:
        ConfigMgr();
        void read_from_file(const std::string path);
        void save_to_file(const std::string path);
        void insertSection(const std::string & name);
        Config& at(const std::string section ="root");
        Config& operator[](const std::string& key);
        Config root;
    private:
        std::map<std::string , Config> sections;
    };
}

cfg::ConfigMgr::ConfigMgr():root("")
{
    
}
void cfg::ConfigMgr::read_from_file(const std::string path)
{
    std::regex key_value_pattern("^ *([^ \\n=]+[^\\n=]*[^ \\n=]+) *= *([^ \\n=]+[^\\n=]*[^ \\n=]+) *\\n*$");//the pattern of key=val
    std::regex section_pattern("^ *\\[ *([^ \\n\\[\\]]+[^\\n\\[\\]]*[^ \\n\\[\\]]+) *\\] *\\n*$");
    std::auto_ptr<char> buffer(new char[BUFFER_SIZE]);
    std::ifstream stream(path);
    std::string now_section= "root";
    while (true)
    {
        stream.getline(buffer.get(), BUFFER_SIZE);
        if(stream.bad())
            throw ReadException("Exception occurred when reading config file");
        std::smatch result;
        std::string temp = buffer.get();
        if(std::regex_match(temp, result, key_value_pattern))
        {
            this->operator[](now_section)[result[1].str()] = result[2].str();
        }
        if(std::regex_match(temp,result,section_pattern))
        {
            now_section = result[1].str();
        }
        if(stream.eof())
        {
            sections[now_section];
            break;
        }
    }
    std::cout<<root.to_string();
    
    
}
std::string& cfg::Config::operator[] (const std::string & key)
{
    return this->configs[key];
}
std::string& cfg::Config::at(const std::string& key)
{
    return this->configs.at(key);
}
void cfg::Config::remove(const std::string& key)
{
    this->configs.erase(key);
}
void cfg::Config::insert(std::pair<std::string ,std::string> key_val)
{
    this->configs[key_val.first] = key_val.second;
}
std::string cfg::Config::to_string()
{
    std::ostringstream str_stream;
    if(section.length()>0)str_stream << '['<<section<<']'<<std::endl;
    for(auto &x:this->configs)
    {
        str_stream<< x.first
        << "="
        <<x.second
        <<std::endl;
    }
    str_stream<<std::endl;
    return str_stream.str();
}

cfg::Config::Config(const std::string &section_name):section(section_name)
{}
void cfg::ConfigMgr::save_to_file(const std::string path)
{
    std::ofstream stream(path);
    //save root section
    stream<<this->root.to_string();
    for(auto &x:this->sections)
    {
        stream<<x.second.to_string();
    }
}
void cfg::ConfigMgr::insertSection(const std::string & name)
{
    this->sections.insert({name,{name}});
}
cfg::Config& cfg::ConfigMgr::at(const std::string section)
{
    if(section == "root")
        return this->root;
    else return this->sections.at(section);
}

cfg::Config& cfg::ConfigMgr::operator[](const std::string& key)
{
    std::cout<<"[] called"<<std::endl;
    if(key == "root")
        return this->root;
    else return this->sections[key];
}

#endif /* ConfigMgr_hpp */

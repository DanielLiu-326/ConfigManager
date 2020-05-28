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

#endif /* ConfigMgr_hpp */

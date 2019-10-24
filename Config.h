//配置文件读取类
#include <std::string>
#include <iostream>
#include <libconfig.h++>

using namespace libconfig;

class Config{
public:    
    static Config& Instance()
    {
        static Config instance;
        return instance;
    }

    bool loadcfg(std::string& file)
    {
        try
        {
            cfg.readFile(file);
        }
        catch(const FileIOException &fioex)
        {
            std::cerr << "I/O error while reading file." << std::endl;
            return false;
        }
        catch(const ParseException &pex)
        {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                    << " - " << pex.getError() << std::endl;
            return false;
        }        
    }
    template<typename Type>
    void Lookup(const std::string &section, Type& value)
    {
        value = cfg.lookup(section);
    }

    const Setting& Lookup(const std::string &section)
    {
        return cfg.lookup(section);
    }

    const Setting& Lookup(const std::string &section1, const std::string &section2)
    {
        return cfg.lookup(section);
    }

private:    
    Config cfg;
};
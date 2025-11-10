#include "../include/saving.hpp"
#include "../include/tag.hpp"
#include "../include/file.hpp"
#include "../include/library.hpp"

#include <algorithm>
#include <fstream>

static std::string escape(const std::string &input)
{
    std::string out;

    for(char c : input)
    {
        if(c == '\"') // (") vira 
            out += "\\\""; // (\")
        
        else if(c == '\\') // (\) vira
            out += "\\\\"; // (\\)
        else
            out += c;
    }
    return out;
}

void save_library(const library &lib, const std::string &filename)
{
    std::ofstream out(filename);
    if(!out)
        return;
    
    out << "{\n";
    out << "    \"files\": [\n";
    bool firstfile = true;
    for(auto &f : lib.get_files())
    {        
        if(!firstfile)
        {
            out << ",\n";
        }
        out << "    {\n";
        out << "      \"path\": \"";
        out << escape(f->get_path());
        out << "\",\n";
        out << "      \"tags\": [";
        bool firsttag = true;
        for(auto &t : f->get_tags())
        {
            if(!firsttag)
            {
                out << ", ";
            }
            firsttag = false;
            out << "\"";
            out << escape(t->id) << "\"";
        }
        out << "]\n";
        out << "    }";
    }
    out << "\n";
    out << "    ]\n";
    out << "}";
    
    out.flush();
    out.close();
}

void load_library(library &lib, const std::string &filename)
{
    
}
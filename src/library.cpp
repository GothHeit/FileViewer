#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include "../include/file.hpp"
#include "../include/library.hpp"
#include "../include/tag.hpp"

    /// @brief Adds a file to the library.
    /// @param path Path for the file to be added.
    void library::add_file(const std::string &path)
    {
        for(auto &f : this->lib_files)
        {
            if(f->get_path() == path)
            {
                return;
            }
        }
        file* f = new file(path);
        lib_files.push_back(f);
    }

    void library::edit_file(int idx)
    {
        // TODO
    }

    /// @brief Changes the view filter applied to the files in the library.
    /// @param tofind Tag to be added or removed from the filter;
    /// @param add Boolean describing whether the tag should be added(1) or deleted(0) from the filter.
    void library::filter_files(tag* tofind, const bool &add)
    {
        // 1 -> add, 0 -> remove
        if(add)
        {
            if(std::find(seen_tags.begin(), seen_tags.end(), tofind) == seen_tags.end())
                this->seen_tags.push_back(tofind);
            else
                return;
        }

        else
        {
            bool changes = false;
            for (size_t i=0; i<this->seen_tags.size(); ++i)
            {
                if(this->seen_tags[i] == tofind)
                {
                    this->seen_tags.erase(this->seen_tags.begin() + int(i));
                    changes = true;
                    break;
                }
            }
            if(!changes)
                return;
        }

        std::unordered_set<file*> out;

        for(auto& ta : this->seen_tags)
        {
            for(auto &fi : ta->get_files())
            {
                out.insert(fi);
            }
        }
        
        for(auto& ta : this->seen_tags)
        {
            std::unordered_set<file*> temp;
            for(auto &f : out)
            {
                if(f->tagged(ta))
                {
                    temp.insert(f);
                }
            }
            out = temp;
        }


        seen_files.assign(out.begin(), out.end());
    }

    /// @brief edits a tag identifier.
    /// @param t tag to be edited.
    /// @param a the new identifier intended for the tag.
    /// @return a boolean describing a tag with that identifier already exists. 
    bool library::edit_tag(tag* t, const std::string &a)
    {
        for(auto& ta : this->tags)
        {
            if(ta->id == a)
            {
                return 0;
            }
        }
        t->id = a;
        return 1;
    }

    tag* library::create_tag(const std::string &name)
    {
        tag* t = new tag(name);
        tags.push_back(t);
        return t;
    }

    tag* library::retrieve_tag(const std::string &name)
    {
        for(auto& ta : tags)
        {
            if(ta->id == name)
            {
                return ta;
            }
        }
        return this->create_tag(name);
    }

    std::vector<file*> library::get_files() const
    {
        return lib_files;
    }


    void library::show()
    {
        // TODO
    }

    library::~library()
    {
        for (auto f : lib_files)
            delete f;

        for (auto t : tags)
            delete t;
    }
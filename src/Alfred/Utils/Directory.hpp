#pragma once

#include <string>
#include <list>
#include <dirent.h>
#include <system_error>

//TODO remove this

namespace Alfred
{
    namespace Utils
    {
        class Directory
        {

          public:
            explicit Directory(const std::string &path) :
                _path(path)
            {
                _dirPtr = opendir(path.c_str());
            }

            ~DirectoryStream()
            {
                if (_dirPtr)
                    closedir(_dirPtr);
            }

            void loadContent(const std::string &filter = "")
            {
                dirent *cur;

                _files.clear();
                rewinddir(_dirPtr);
                cur = readdir(_dirPtr);
                if (!cur)
                    throw std::system_error();
                do {
                    if (filter != "") {
                        std::string curName(cur->d_name);
                        unsigned long pos = curName.find_last_of(".");

                        if (pos != std::string::npos && curName.substr(pos + 1) == filter)
                            _files.push_front(*cur);
                    } else
                        _files.push_front(*cur);
                } while ((cur = readdir(_dirPtr)));
            }

            bool isEmpty() const
            {
                return _files.empty();
            }

            Directory &operator>>(std::string &out)
            {
                if (_files.empty())
                    throw std::logic_error("Directory stream is empty");
                out = _files.front().d_name;
                _files.pop_front();
                return *this;
            }

          private:
            std::string _path;
            DIR *_dirPtr;
            std::list<dirent> _files;
        };
    }
}


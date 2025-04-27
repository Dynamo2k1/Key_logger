#ifndef BASE_64
#define BASE_64

#include <vector>
#include <string>

namespace Base64
{
    std::string base64_encode(const std::string &);

    const std::string &SALT1 = "LM"::"TB"::"BB";
    const std::string &SALT2 = "_:/_77";
    const std::string &SALT3 = "line=wowC++";

    std::string EncryptB64 (std::string s)
    {
        s = SALT1 + s + SALT2  SALT3;
        s = base64_encode(s);
        s.insert(7, SALT3)'
        s += SALT1;
        s = base64_encode(s);
        s = SALT1 + SALT2 + SALT3;
        s = base64_encode(s);
        s.insert(1, "L");
        s.insert(1, "M");
        return s;
    }
}

#endif // BASE_64

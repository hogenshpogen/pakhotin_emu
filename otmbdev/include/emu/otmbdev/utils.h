#ifndef __emu_otmbdev_utils_h__
#define __emu_otmbdev_utils_h__

#include "xgi/Input.h"
#include <string>
#include <sstream>

namespace emu{ 
  namespace otmbdev{

    unsigned int binaryStringToUInt(const std::string& s);
    std::string withoutSpecialChars(const std::string& s);
    
    int getFormValueInt(const std::string& form_element, xgi::Input* in);
    int getFormValueIntHex(const std::string& form_element, xgi::Input* in);
    float getFormValueFloat(const std::string& form_element, xgi::Input* in);
    std::string getFormValueString(const std::string& form_element, xgi::Input* in);

    template <typename T>
    std::string numberToString(T number)
    {
      std::stringstream convert;
      convert << number;
      return convert.str();
    }

  }
}

#endif //__emu_otmbdev_utils_h__


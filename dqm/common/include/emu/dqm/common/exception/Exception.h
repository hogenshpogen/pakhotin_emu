#ifndef __EmuDQM_Exception_h__
#define __EmuDQM_Exception_h__


#include "xcept/Exception.h"


namespace emu
{
namespace dqm
{
namespace exception
{
/**
 * Exception raised by the EmuDQM packages.
 */
class Exception: public xcept::Exception
{
public:

  Exception(std::string name,
            std::string message,
            std::string module,
            int line,
            std::string function)
      : xcept::Exception(name, message, module, line, function)
  {
  }

  Exception(std::string name,
            std::string message,
            std::string module,
            int line,
            std::string function,
            xcept::Exception & e)
      : xcept::Exception(name, message, module, line, function, e)
  {
  }
};
};
}
}

#endif

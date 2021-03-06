#ifndef _ResultRegisterSerializer_h_
#define _ResultRegisterSerializer_h_

#include <stdint.h>

namespace emu { namespace pc {

class CCB;

/// Maximal width of the result register
const uint32_t TMB_RESULT_REGISTER_WIDTH = 20;
const uint32_t TMB_RR_WIDTH = TMB_RESULT_REGISTER_WIDTH;

/// width of the result register command field
const uint32_t TMB_RESULT_REGISTER_COMMAND_WIDTH = 8;
const uint32_t TMB_RR_COMMAND_WIDTH = TMB_RESULT_REGISTER_COMMAND_WIDTH;

/// width of the result register data field
const uint32_t TMB_RESULT_REGISTER_DATA_WIDTH = 12;
const uint32_t TMB_RR_DATA_WIDTH = TMB_RESULT_REGISTER_DATA_WIDTH;

/// width of the digital serial number
const uint32_t DSN_WIDTH = 64;


/** \class ResultRegisterSerializer
 *
 * Allows serialized reading of the result register of TMB that is being tested through CCB.
 * Reading from a specific TMB is performed through just two bits: alct_cfg_done and tmb_cfg_done
 * which are accessible through CSRA2 & CSRA3 registers of CCB.
 *
 * \author Vadim Khotilovich
 *
 */
class ResultRegisterSerializer
{
public:

  /// initialize with a CCB and TMB slot number
  ResultRegisterSerializer(CCB *ccb, int tmb_slot);

  /// \return the result of serial read of TMB status bits
  uint32_t read(uint32_t length = TMB_RESULT_REGISTER_WIDTH);
  
  /// set verbosoty level (it's set to 0 by default in constructor)
  void setVerbose(int level);

private:

  /// holder of CCB
  CCB * ccb_;

  /// TMB slot
  int tmbSlot_;

  /// verbosity level
  int verbose_;

  /// LUT for the TMB slot # -> sequential index association
  static int slotToIndexLUT_[22];

  // bit shifting amounts
  int shiftCsra2Alct_;
  int shiftCsra2Tmb_;
  int shiftCsra3Tmb_;  
};


}} // namespaces


#endif

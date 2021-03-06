#ifndef emu_pc_TestWorkerBase_h
#define emu_pc_TestWorkerBase_h

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/function.hpp>
#include "emu/pc/TestLogger.h"

namespace emu { namespace pc {

class TMB;
class CCB;


/** class TestWorkerBase
 *
 * A base class that contains generic TMB testing functionality like
 *  - registering a test procedure
 *  - running the test(s)
 *  - accessing test results
 *  - keeping log of test output
 *  - resets
 * which should be reused by its subclasses.
 *
 * Notes:
 *  - subclasses have to define the abstract methods;
 *  - subclasses have to implement copy c-tor and assignment operator which
 *    should properly take care of re-binding their test procedures to new objects
 *
 * \author Vadim Khotilovich
 */
class TestWorkerBase
{
public:

  typedef TestLogger::TestError TestError;

  TestWorkerBase();

  virtual ~TestWorkerBase();

  // not responsible for deleting pointers
  void SetTMB(TMB * tmb) {tmb_ = tmb;}
  void SetCCB(CCB * ccb) {ccb_ = ccb;}

  /// returns labels of available registered tests
  std::vector<std::string> GetTestLabels() const;

  /// total number of tests
  int NTests() const;

  /// number of passed tests
  int NTestsPass() const;

  /// number of failed tests
  int NTestsFail() const;

  /// Getter for the result of a test with specific label.
  /// Note: the results values are first initialized to -1 in the constructor.
  /// Running the tests through RunTest would set the corresponding result values to either 0 (pass) or >0 (error code).
  int GetTestResult(const std::string &test);

  /// setter for the result of a test with specific label
  void SetTestResult(const std::string &test, int result);

  /// Getter for the status of a test with specific label
  /// Note: Status values must be updated through SetTestStatus, as testStatuses_ is intended for tests that do not utilize RunTest
  int GetTestStatus(const std::string &test);

  /// Setter for the status of a test with a specific label
  void SetTestStatus(const std::string &test, int status);

  /// Report an error during a test
  /// Errors reported are written to the log if logging is enabled
  void ReportError(TestError & error);

  /// Setter for the board label within the logger
  void SetBoardLabel(std::string);

  /// Run a test with specific label.
  /// A special case of a label is "All", which would cause running of all registered tests.
  /// \return 0 if success, numerical error code > 0 if problem
  int RunTest(const std::string &test);

  // Pause logging test results
  void ResumeLogging();

  // Resume logging test results
  void PauseLogging();

  // Finish testing session
  void FinishTesting();

  // Set test logger
  void SetLogger(TestLogger *);

  /// Allows to set the results output destination.
  /// Initially, the internal out_ output is set to std::cout in the constructor.
  virtual void RedirectOutput(std::ostream * output);

  /// reference accessor to the current output stream
  std::ostream & out() { return *out_; }

protected:

  /// defines the signature for test procedures
  typedef boost::function<int ()> TestProcedure;

  /// Register a new test procedure with a given label
  /// @param test is a test's label (note: it cannot be "All" which is reserved for running all tests)
  /// @param proc is a binding for a test procedure
  /// If a procedure with a given label was registered before, it would only reset the functional binding.
  void RegisterTheTest(const std::string &test, TestProcedure proc);

  /// Register the collection of test procedures by calling RegisterTheTest for each specific test.
  /// Has to be implemented by every subclass!
  virtual void RegisterTestProcedures() = 0;

  /// Converts test procedure name to corresponding test label according to a set convention.
  std::string TestLabelFromProcedureName(const std::string &proc);

  /// Hardware preparation procedure that has to be performed before every test.
  virtual void PrepareHWForTest();

  /// issue HardReset through CCB
  virtual void HardReset();

  /// issue L1Reset through CCB
  virtual void L1Reset();

  /// Compare float values with some tolerance
  /// and report error ID if the comparison fails
  bool CompareAndReport(float testval, float compareval, float tolerance, bool print_pass, unsigned int errorID);
  bool CompareAndReport(float testval, float compareval, float tolerance, unsigned int errorID);

  /// Compare integer values with some tolerance
  /// and report error ID if the comparison fails
  bool CompareAndReport(int testval, int compareval, bool equal, bool print_pass, unsigned int errorID);
  bool CompareAndReport(int testval, int compareval, bool equal, unsigned int errorID);

  // Holders for CCB and TMB pointers.
  // This class is not responsible for deleting the pointers ("aggregation")
  CCB * ccb_;
  TMB * tmb_;

private:

  /// where to store the output with results
  std::ostream * out_ ;

  TestLogger * log_;

  /// keep _ordered_ list of test labels
  std::vector<std::string> testLabels_;

  /// test label -> test procedure association
  std::map<std::string, TestProcedure> testProcedures_;

  /// test label -> test result association
  std::map<std::string, int> testResults_;

  /// test label -> test status association
  std::map<std::string, int> testStatuses_;

  std::vector<TestError> testErrors_;
};


}} // namespaces

#endif

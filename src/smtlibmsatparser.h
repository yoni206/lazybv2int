#pragma once

#include <string>
#include <vector>

#include "smt-switch/smt.h"

namespace lbv2i {

/** Reads a file and returns the assertions as an smt-switch Term
 *  @param f the input file to read in smt-lib2 format
 *  @param tr a TermTranslator that converts a term to a given solver
 *    e.g. instantiate the TermTranslator with: TermTranslator tr(s),
 *    where s is the solver you'd like to use to build the assertion term
 *  @return a term representing all the assertions in the file
 *          if there are multiple assertions, they are conjuncted
 */
smt::Term parse_smt2(FILE * f, smt::TermTranslator tr);

std::string remove_asserts(std::string input);

class SExprBuffer
{
 public:
  SExprBuffer() : num_unbalanced(0), in_command(false) {}
  ~SExprBuffer(){};

  bool any_new_commands() { return commands.size(); }
  std::vector<std::string> & get_commands() { return commands; }
  void clear_commands() { commands.clear(); }
  void add_string(std::string input);

 protected:
  size_t num_unbalanced;  // the number of unbalanced open parantheses
  std::vector<std::string> commands;  // a balanced set of commands
  std::string buffered_input;         // buffered input that is not yet balanced
  bool in_command; // set to true BEFORE processing the next character, if in a command
};

}  // namespace lbv2i

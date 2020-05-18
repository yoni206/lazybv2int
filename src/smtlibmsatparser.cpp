#include "smtlibmsatparser.h"

#include <iostream>
#include <vector>

#include "msat/include/msat_term.h"
#include "stdio.h"

using namespace smt;
using namespace std;

namespace lbv2i {

Term parse_smt2(FILE * f, TermTranslator tr)
{
  msat_config cfg = msat_create_config();
  msat_env env = msat_create_env(cfg);
  msat_term res = msat_from_smtlib2_file(env, f);

  if (MSAT_ERROR_TERM(res)) {
    std::cout << "got error term after parsing" << std::endl;
    throw std::exception();
  }

  Term mterm(new MsatTerm(env, res));
  Term transferred_term = tr.transfer_term(mterm);
  msat_destroy_env(env);
  msat_destroy_config(cfg);
  return transferred_term;
}

string remove_asserts(string input)
{
  string assert_pattern("(assert");
  vector<string> processed;
  size_t loc = input.find(assert_pattern);
  while (loc != string::npos) {
    size_t current_loc = loc + assert_pattern.length();
    size_t num_unbalanced = 1;
    while (num_unbalanced) {
      try {
        if (input[current_loc] == '(') {
          num_unbalanced++;
        } else if (input[current_loc] == ')') {
          num_unbalanced--;
        }
        current_loc++;
      }
      catch (const out_of_range & oor) {
        cerr << "unmatched parentheses for assert in:" << endl;
        cerr << input.substr(loc, input.length() - loc) << endl;
        throw std::exception();
      }
    }
    processed.push_back(input.substr(0, loc));
    input = input.substr(current_loc, input.length() - current_loc);
    loc = input.find(assert_pattern);
  }

  // add the leftover
  processed.push_back(input);

  // recombine string
  string output("");
  for (auto s : processed) {
    output += s;
  }
  return output;
}

void SExprBuffer::add_string(string input)
{
  for (std::string::size_type loc = 0; loc < input.size(); loc++) {
    in_command = (num_unbalanced != 0);
    if (input[loc] == '(') {
      num_unbalanced++;
    } else if (input[loc] == ')') {
      num_unbalanced--;
    }

    // add to the buffered input
    buffered_input.push_back(input[loc]);

    // if it was in a command and became balanced, then add it to contents
    // because the command has finished
    if (in_command && num_unbalanced == 0) {
      // buffered input is a complete command, add it to commands
      commands.push_back(buffered_input);
      // reset buffered input
      buffered_input = "";
    }
  }
  // add back the new line
  buffered_input += "\n";
}

}  // namespace lbv2i

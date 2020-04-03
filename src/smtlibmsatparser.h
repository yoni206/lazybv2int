#pragma once

#include <string>

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

}  // namespace lbv2i

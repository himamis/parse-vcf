/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#ifndef PARSER_H_
#define PARSER_H_

#include <istream>

namespace parsevcf {

bool parse(std::istream& input);

} /* namespace parsevcf */

#endif /* PARSER_H_ */

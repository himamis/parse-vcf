/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#ifndef ENTRIES_PARSER_H_
#define ENTRIES_PARSER_H_

#include "lexer.h"

namespace parsevcf {

bool header(lexer& input);

bool entries(lexer& input);

} /* namespace parsevcf */

#endif /* ENTRIES_PARSER_H_ */

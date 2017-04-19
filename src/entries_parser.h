/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#ifndef ENTRIES_PARSER_H_
#define ENTRIES_PARSER_H_

#include "lexer.h"
#include "DefaultHandler.h"

namespace parsevcf {

bool header(lexer& input, DefaultHandler& handler);

bool entries(lexer& input, DefaultHandler& handler);

} /* namespace parsevcf */

#endif /* ENTRIES_PARSER_H_ */

/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#ifndef META_PARSER_H_
#define META_PARSER_H_

#include "DefaultHandler.h"
#include "Lexer.h"

namespace parsevcf {

bool metaInformation(lexer& input, DefaultHandler& handler);

} /* namespace parsevcf */

#endif /* META_PARSER_H_ */

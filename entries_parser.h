#ifndef ENTRIES_PARSER_H_
#define ENTRIES_PARSER_H_

#include "lexer.h"

namespace parsevcf {

bool header(lexer& input);

bool entries(lexer& input);

} /* namespace parsevcf */

#endif /* ENTRIES_PARSER_H_ */

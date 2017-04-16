/*
 * parser.h
 *
 *  Created on: 16 Apr 2017
 *      Author: balazs
 */

#ifndef META_PARSER_H_
#define META_PARSER_H_

#include "lexer.h"

namespace parsevcf {

bool metaInformation(lexer& input);

} /* namespace parsevcf */

#endif /* META_PARSER_H_ */

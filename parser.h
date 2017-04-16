/*
 * parser.h
 *
 *  Created on: 16 Apr 2017
 *      Author: balazs
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <istream>

namespace parsevcf {

bool parse(std::istream& input);

} /* namespace parsevcf */

#endif /* PARSER_H_ */

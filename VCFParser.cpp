/*
 * VCFParser.cpp
 *
 *  Created on: 15 Apr 2017
 *      Author: balazs
 */

#include <sstream>
#include <string>

#include "VCFParser.h"
#include "lexer.h"
#include "meta_parser.h"

using namespace std;

namespace parsevcf {

VCFParser::VCFParser(std::ifstream& input, const DefaultHandler& handler) :
		_input(input), _handler(handler), _state(kMeta) { }

VCFParser::~VCFParser() { }

void VCFParser::parse() {
	lexer lex = lexer(_input);
	if (metaInformation(lex)) {
		printf("%s", "All good man.\n");
	} else {
		printf("%s", "Whoa, something is wrong\n");
	}
}


} /* namespace parsevcf */

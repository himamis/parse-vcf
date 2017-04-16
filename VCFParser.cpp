/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include <sstream>
#include <string>

#include "VCFParser.h"
#include "parser.h"

using namespace std;

namespace parsevcf {

VCFParser::VCFParser(std::ifstream& input, const DefaultHandler& handler) :
		_input(input), _handler(handler) { }

VCFParser::~VCFParser() { }

void VCFParser::parse() {
	if (parsevcf::parse(_input)) {
		printf("%s", "All good man.\n");
	} else {
		printf("%s", "Whoa, something is wrong\n");
	}
}

} /* namespace parsevcf */

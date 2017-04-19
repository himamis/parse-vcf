/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include <sstream>
#include <string>

#include "VCFParser.h"
#include "parser.h"

using namespace std;

namespace parsevcf {

VCFParser::VCFParser(std::istream& input, DefaultHandler& handler) :
		_handler(handler), _input(input) {
}

VCFParser::~VCFParser() { }

bool VCFParser::parse() {
	return parsevcf::parse(_input, _handler);
}

} /* namespace parsevcf */

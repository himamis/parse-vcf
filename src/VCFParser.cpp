/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "VCFParser.h"

#include <sstream>
#include <string>
#include "EntryParser.h"
#include "MetaParser.h"

using namespace std;

namespace parsevcf {

VCFParser::VCFParser(std::istream& input, DefaultHandler& handler) :
		_handler(handler), _input(input) {
}

VCFParser::~VCFParser() {
}

bool VCFParser::parse() {
	lexer lex = lexer(_input);
	_handler.startDocument();

	metaInformation(lex, _handler);
	if (!header(lex, _handler)) {
		error_missing(lex, "header");
		return false;
	}
	if (!entries(lex, _handler)) {
		error_missing(lex, "entries");
		return false;
	}

	_handler.endDocument();
	return true;
}

} /* namespace parsevcf */

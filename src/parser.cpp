/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "parser.h"

#include "entries_parser.h"
#include "meta_parser.h"

namespace parsevcf {

bool parse(std::istream& input, DefaultHandler& handler) {
	lexer lex = lexer(input);
	handler.startDocument();

	metaInformation(lex, handler);
	if (!header(lex, handler)) {
		error_missing(lex, "header");
		return false;
	}
	if (!entries(lex, handler)) {
		error_missing(lex, "entries");
		return false;
	}

	handler.endDocument();
	return true;
}

} /* namespace parsevcf */

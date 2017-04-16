/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "parser.h"

#include "entries_tokernizer.h"
#include "meta_tokenizer.h"

namespace parsevcf {

bool parse(std::istream& input) {
	lexer lex = lexer(input);

	metaInformation(lex);
	if (!header(lex)) {
		error_missing(lex, "header");
		return false;
	}
	if (!entries(lex)) {
		error_missing(lex, "entries");
		return false;
	}
	return true;
}

} /* namespace parsevcf */

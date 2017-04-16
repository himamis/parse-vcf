#include "parser.h"
#include "meta_parser.h"
#include "entries_parser.h"

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

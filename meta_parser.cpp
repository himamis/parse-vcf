#include "meta_parser.h"

using namespace std;

namespace parsevcf {

bool equals(lexer& input) {
	return next_character(input, '=');
}

bool newline(lexer& input) {
	return next_line(input);
}

bool comma(lexer& input) {
	return next_character(input, ',');
}

bool quotemarks(lexer& input) {
	return next_character(input, '"');
}

bool langle(lexer& input) {
	return next_character(input, '<');
}

bool rangle(lexer& input) {
	return next_character(input, '>');
}

bool quoted_string(lexer& input, string& ret) {
	first_rule(quotemarks, input)

	if (!next_string_until_char(input, ret, '"')) {
		error_missing(input, "\"");
		return false;
	}
	rule(quotemarks, input)
	return true;
}

bool metaKey(lexer& input) {
	// anything until equals sign
	static const string until = "=";

	string ret;
	return next_string_until_one_of(input, ret, until);
}

bool metaPrefix(lexer& input) {
	return next_string(input, "##"); // ##
}

bool metaValueListKey(lexer& input) {
	string ret;
	if (!next_string_until_char(input, ret, '=')) {
		return false;
	}
	return true;
}

bool metaValueListValue(lexer& input) {
	string ret;
	if (!quoted_string(input, ret)) {
		if (!next_string_until_one_of(input, ret, ",>")) {
			return false;
		}
	}
	return true;
}

bool metaValueListEntry(lexer& input) {
	first_rule(metaValueListKey, input) // key
	rule(equals, input)					// =
	rule(metaValueListValue, input) 	// value
	return true;
}

bool metaValueList(lexer& input) {
	first_rule(langle, input)			// <
	rule(metaValueListEntry, input)		// entry

	while (comma(input)) {
		rule(metaValueListEntry, input)	// (, entry) *
	}

	rule(rangle, input)					// >
	return true;
}

bool metaValueString(lexer& input) {
	string ret;
	return next_string_until_newline(input, ret);
}

bool metaValue(lexer& input) {
	string ret;
	if (!metaValueList(input)) {
		if (!metaValueString(input)) {
			return false;
		}
	}
	return true;
}

bool metaEntry(lexer& input) {
	first_rule(metaPrefix, input)
	rule(metaKey, input)
	rule(equals, input)
	rule(metaValue, input)
	rule(newline, input)
	return true;
}

bool metaInformation(lexer& input) {
	// list of meta entries
	first_rule(metaEntry, input)

	do {} while (metaEntry(input));
	return true;
}

} /* namespace parsevcf */


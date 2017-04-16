/*
 * parser.c
 *
 *  Created on: 16 Apr 2017
 *      Author: balazs
 */

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

bool quoted_string(lexer& input, string& ret) {
	if (!next_character(input, '"')) {
		return false;
	}
	if (!next_string_until_char(input, ret, '"')) {
		error_missing(input, "\"");
		return false;
	}
	if (!next_character(input, '"')) {
		error_missing(input, "\"");
		return false;
	}
	return true;
}

bool metaKey(lexer& input) {
	// anything until equals sign
	static const string until = "=";

	string ret;
	return next_string_until_one_of(input, ret, until);
}

bool metaPrefix(lexer& input) {
	// ##
	return next_string(input, "##");
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
	if (!metaValueListKey(input)) {
		return false;
	}
	if (!equals(input)) {
		error_missing(input, "=");
		return false;
	}
	if (!metaValueListValue(input)) {
		error_missing(input, "meta value list value");
		return false;
	}
	return true;
}

bool metaValueList(lexer& input) {
	if (!next_character(input, '<')) {
		return false;
	}
	rule(metaValueListEntry, input)

	while (comma(input)) {
		rule(metaValueListEntry, input)
	}

	if (!next_character(input, '>')) {
		error_missing(input, ">");
		return false;
	}
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


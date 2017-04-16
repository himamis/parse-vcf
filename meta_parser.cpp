/*
 * parser.c
 *
 *  Created on: 16 Apr 2017
 *      Author: balazs
 */

#include "meta_parser.h"

#include <iostream>

using namespace std;

static const string unknown = "unknown value";

void error(const string& message) {
	cout << message;
	cout << endl;
	cout.flush();
}

void error_missing(const string& expecting = unknown) {
	string message = "Error, was expecting ";
	message += expecting;
	message += ".";
	error(message);
}

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
		error_missing("\"");
		return false;
	}
	if (!next_character(input, '"')) {
		error_missing("\"");
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
	return next_character(input, '#') && next_character(input, '#');
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
		error_missing("=");
		return false;
	}
	if (!metaValueListValue(input)) {
		error_missing("meta value list value");
		return false;
	}
	return true;
}

bool metaValueList(lexer& input) {
	if (!next_character(input, '<')) {
		return false;
	}
	if (!metaValueListEntry(input)) {
		error_missing("meta value list entry");
		return false;
	}

	while (comma(input)) {
		if (!metaValueListEntry(input)) {
			error_missing("meta value list entry");
			return false;
		}
	}

	if (!next_character(input, '>')) {
		error_missing(">");
		return false;
	}
	if (!newline(input)) {
		error_missing("newline");
		return false;
	}
	return true;
}

bool metaValue(lexer& input) {
	string ret;
	if (!metaValueList(input)) {
		if (!next_string_until_newline(input, ret)) {
			return false;
		}
	}
	return true;
}

bool metaEntry(lexer& input) {
	// prefix key = value
	if (!metaPrefix(input)) {
		return false;
	}
	if (!metaKey(input)) {
		error_missing("meta key");
		return false;
	}
	if (!equals(input)) {
		error_missing("=");
		return false;
	}
	if (!metaValue(input)) {
		error_missing("meta value");
		return false;
	}
	if (!newline(input)) {
		error_missing("newline");
		return false;
	}
	return true;
}

bool metaInformation(lexer& input) {
	// list of meta entries

	if (!metaEntry(input)) {
		return false;
	}
	do {} while (metaEntry(input));
	return true;
}

/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "entries_parser.h"
#include <iostream>

using namespace std;

namespace parsevcf {

static const string kChrom = "CHROM";
static const string kPos = "POS";
static const string kId = "ID";
static const string kRef = "REF";
static const string kAlt = "ALT";
static const string kQual = "QUAL";
static const string kFilter = "FILTER";
static const string kInfo = "INFO";
static const string kFormat = "FORMAT";

static const string kPass = "PASS";
static const string kUnknown = ".";

bool tab(lexer& input) {
	return next_character(input, '\t');
}

bool semicolon(lexer& input) {
	return next_character(input, ';');
}

bool hashtag(lexer& input) {
	return next_character(input, '#');
}

bool sample_name(lexer& input, string& sample) {
	return next_string_until_one_of(input, sample, "\t\n");
}

bool sample_names(lexer& input) {
	first_rule(next_string, input, kFormat)
	rule(tab, input)

	string sample;
	rule(sample_name, input, sample)

	while (tab(input)) {
		rule(sample_name, input, sample)
	}
	return true;
}

bool header(lexer& input) {
	first_rule(hashtag, input)

	rule_string(kChrom, input);
	rule(tab, input)
	rule_string(kPos, input);
	rule(tab, input)
	rule_string(kId, input);
	rule(tab, input)
	rule_string(kRef, input);
	rule(tab, input)
	rule_string(kAlt, input);
	rule(tab, input)
	rule_string(kQual, input);
	rule(tab, input)
	rule_string(kFilter, input);
	rule(tab, input)
	rule_string(kInfo, input);

	if (next_character(input, '\t')) {
		rule(sample_names, input)
	}

	rule(next_line, input)
	return true;
}

bool chrom(lexer& input) {
	string ret;
	if (!next_string_until_char(input, ret, '\t')) {
		return false;
	}
	return true;
}

bool pos(lexer& input) {
	string ret;
	if (!next_string_until_char(input, ret, '\t')) {
		return false;
	}
	return true;
}

bool id(lexer& input) {
	string ret;
	if (!next_string_until_char(input, ret, '\t')) {
		return false;
	}
	return true;
}

bool ref(lexer& input) {
	string ret;
	if (!next_string_until_char(input, ret, '\t')) {
		return false;
	}
	return true;
}

bool alt(lexer& input) {
	string ret;
	if (!next_string_until_char(input, ret, '\t')) {
		return false;
	}
	return true;
}

bool qual(lexer& input) {
	string ret;
	if (!next_string_until_char(input, ret, '\t')) {
		return false;
	}
	return true;
}

bool filterValue(lexer& input) {
	string filter;
	if (!next_string_until_one_of(input, filter, "\t;")) {
		return false;
	}
	return true;
}

bool filterList(lexer& input) {
	first_rule(filterValue, input)
	while (semicolon(input)) {
		rule(filterValue, input)
	}
	return true;
}

bool filter(lexer& input) {
	if (!next_string(input, kPass)) {
		if (!next_string(input, kUnknown)) {
			if (!filterList(input)) {
				return false;
			}
		}
	}
	return true;
}

bool infoValue(lexer& input) {
	string value;
	if (!next_string_until_one_of(input, value, "\t;")) {
		return false;
	}
	cout << value << endl;
	return true;
}

bool infoKey(lexer& input) {
	string key;
	if (!next_string_until_one_of(input, key, "=\t;")) {
		return false;
	}
	cout << key << endl;
	return true;
}

bool infoListEntry(lexer& input) {
	first_rule(infoKey, input)
	if (eat('=', input)) {
		rule(infoValue, input)
	}
	return true;
}

bool infoList(lexer& input) {
	first_rule(infoListEntry, input)
	while (semicolon(input)) {
		rule(infoListEntry, input)
	}
	return true;
}

bool info(lexer& input) {
	if (!next_string(input, kUnknown)) {
		if (!infoList(input)) {
			return false;
		}
	}
	return true;
}

bool entry(lexer& input) {
	first_rule(chrom, input)
	rule(tab, input)
	rule(pos, input)
	rule(tab, input)
	rule(id, input)
	rule(tab, input)
	rule(ref, input)
	rule(tab, input)
	rule(alt, input)
	rule(tab, input)
	rule(qual, input)
	rule(tab, input)
	rule(filter, input)
	rule(tab, input)
	rule(info, input)

	return true;
}

bool entries(lexer& input) {
	while (entry(input)) {
		rule(next_line, input)
		if (input.stream.eof()) {
			break;
		}
	}

	return true;
}

} /* namespace parsevcf */

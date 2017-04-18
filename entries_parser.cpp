/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "entries_parser.h"

#include "constants.h"

using namespace std;
using namespace parsevcf::constants;

namespace parsevcf {

bool tab(lexer& input) {
	return next_character(input, '\t');
}

bool semicolon(lexer& input) {
	return next_character(input, ';');
}

bool hashtag(lexer& input) {
	return next_character(input, '#');
}

bool sampleName(lexer& input, string& sample) {
	return next_string_until_one_of(input, sample, "\t\n");
}

bool sampleNames(lexer& input, DefaultHandler& handler) {
	first_rule(next_string, input, constants::kFormat)
	rule(tab, input)

	vector<string> names;
	string sample;
	rule(sampleName, input, sample)
	names.push_back(sample);

	while (tab(input)) {
		rule(sampleName, input, sample)
		names.push_back(sample);
	}

	handler.sampleNames(names);
	return true;
}

bool header(lexer& input, DefaultHandler& handler) {
	first_rule(hashtag, input)
	using namespace constants;

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

	if (eat('\t', input)) {
		rule(sampleNames, input, handler)
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
	return true;
}

bool infoKey(lexer& input) {
	string key;
	if (!next_string_until_one_of(input, key, "=\t;")) {
		return false;
	}
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

bool formatEntry(lexer& input) {
	string format;
	if (!next_string_until_one_of(input, format, "\t:")) {
		return false;
	}
	return true;
}

bool format(lexer& input) {
	first_rule(formatEntry, input)
	while (eat(':', input)) {
		rule(formatEntry, input)
	}
	return true;
}

bool sampleValue(lexer& input) {
	string entry;
	if (!next_string_until_one_of(input, entry, "\t\n:")) {
		return false;
	}
	return true;
}

bool sampleValues(lexer& input) {
	first_rule(sampleValue, input)
	while (eat(':', input)) {
		rule(sampleValue, input)
	}
	return true;
}

bool sampleEntries(lexer& input) {
	first_rule(sampleValues, input)
	while(eat('\t', input)) {
		rule(sampleValues, input)
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

	if (eat('\t', input)) {
		rule(format, input)
		rule(tab, input)
		rule(sampleEntries, input)
	}

	return true;
}

bool entries(lexer& input, DefaultHandler& handler) {
	while (entry(input)) {
		rule(next_line, input)
		if (input.stream.eof()) {
			break;
		}
	}

	return true;
}

} /* namespace parsevcf */

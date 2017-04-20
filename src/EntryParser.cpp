/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "EntryParser.h"

#include "Common.h"

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
	first_rule(next_string, input, tokens::format)
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
	using namespace tokens;

	rule_string(chrom, input);
	rule(tab, input)
	rule_string(pos, input);
	rule(tab, input)
	rule_string(id, input);
	rule(tab, input)
	rule_string(ref, input);
	rule(tab, input)
	rule_string(alt, input);
	rule(tab, input)
	rule_string(qual, input);
	rule(tab, input)
	rule_string(filter, input);
	rule(tab, input)
	rule_string(info, input);

	if (eat('\t', input)) {
		rule(sampleNames, input, handler)
	}

	rule(next_line, input)
	return true;
}

bool val(lexer& input, string& ret) {
	if (!next_string_until_char(input, ret, '\t')) {
		return false;
	}
	return true;
}

bool valorend(lexer& input, string& ret) {
	if (!next_string_until_one_of(input, ret, "\t\n")) {
		return false;
	}
	return true;
}

bool entry(lexer& input, DefaultHandler& handler) {
	string value;
	vector<string> values;

	// chrom
	first_rule(val, input, value)
	values.push_back(value);

	for (int i = 0; i < 7; i++) {
		// pos, id, ref, alt, qual, filter info
		rule(tab, input)
		rule(val, input, value)
		values.push_back(value);
	}

	if (eat('\t', input)) {
		// format
		rule(val, input, value)
		values.push_back(value);
		rule(tab, input)

		// sample
		rule(val, input, value)
		values.push_back(value);

		while (eat('\t', input)) {
			// sample
			rule(valorend, input, value)
			values.push_back(value);
		}
	}

	SNVEntry entry;
	entry.values = values;
	handler.entry(entry);

	return true;
}

bool entries(lexer& input, DefaultHandler& handler) {
	while (entry(input, handler)) {
		rule(next_line, input)
		if (input.stream.eof()) {
			break;
		}
	}

	return true;
}

} /* namespace parsevcf */

/*
 * entries_parser.cpp
 *
 *  Created on: 16 Apr 2017
 *      Author: balazs
 */

#include "entries_parser.h"

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

bool tab(lexer& input) {
	return next_character(input, '\t');
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


	STRING(input, kChrom);
	rule(tab, input)
	STRING(input, kPos);
	rule(tab, input)
	STRING(input, kId);
	rule(tab, input)
	STRING(input, kRef);
	rule(tab, input)
	STRING(input, kAlt);
	rule(tab, input)
	STRING(input, kQual);
	rule(tab, input)
	STRING(input, kFilter);
	rule(tab, input)
	STRING(input, kInfo);

	if (next_character(input, '\t')) {
		if (!sample_names(input)) {
			error_missing(input, "expecting sample names");
			return false;
		}
	}

	if (!next_line(input)) {
		error_missing(input, "newline");
		return false;
	}
	return true;
}

bool entries(lexer& input) {
	string line;
	while(next_string_until_newline(input, line)) {
		if (!next_line(input)) {
			// eof
			break;
		}
	}
	return true;
}

} /* namespace parsevcf */

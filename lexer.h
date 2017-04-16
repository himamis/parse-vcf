/*
 * lexer.h
 *
 *  Created on: 16 Apr 2017
 *      Author: balazs
 */

#ifndef LEXER_H_
#define LEXER_H_

#include <istream>

namespace parsevcf {

struct lexer {
	lexer(std::istream& stream) :
			stream(stream), pos(0), line(1) {
		std::getline(stream, current_line);
		current_line += '\n';
	}
	std::istream& stream;
	std::string current_line;
	int pos;
	int line;
};

void error(const lexer& input, const std::string& message);

void error_missing(const lexer& input, const std::string& expecting);

bool next_line(lexer& input);

bool next_character(lexer& input, const char& character);

bool next_string(lexer& input, const std::string& str);

bool next_string_until_one_of(lexer& input, std::string& output,
		const std::string& match);

bool next_string_until_char(lexer& input, std::string& output,
		const char& match);

bool next_string_until_newline(lexer& input, std::string& output);

// Helper macros
/////////////////
// TODO
#define rule_character(lexer, character) if (!next_character(lexer, character)) { \
	error_missing(lexer, #character); \
	return false; \
}

#define rule_string(string, lexer) if (!next_string(lexer, string)) { \
	error_missing(lexer, string); \
	return false; \
}

#define rule_string_first(lexer, string) if (!next_string(lexer, string)) { \
	return false; \
}

#define rule(rule, lexer, args...) if (!rule(lexer, ##args)) { \
	error_missing(lexer, #rule); \
	return false; \
}

#define first_rule(rule, lexer, args...) if (!rule(lexer, ##args)) { \
	return false; \
}

#define create_rule(name, helper, lexer) if ()

} /* namespace parsevcf */

#endif /* LEXER_H_ */

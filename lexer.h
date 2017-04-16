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
	lexer(std::istream& stream) : stream(stream), pos(0) {
		std::getline(stream, current_line);
	}
	std::istream& stream;
	std::string current_line;
	int pos;
};

bool next_line(lexer& input);

bool next_character(lexer& input, const char& character);

bool next_string_until_one_of(lexer& input, std::string& output, const std::string& match);

bool next_string_until_char(lexer& input, std::string& output, const char& match);

bool next_string_until_newline(lexer& input, std::string& output);

} /* namespace parsevcf */

#endif /* LEXER_H_ */

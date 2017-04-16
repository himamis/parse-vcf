#include "lexer.h"

using namespace std;

bool next_line(lexer& input) {
	if (input.pos == input.current_line.length()) {
		getline(input.stream, input.current_line);
		input.pos = 0;
		return true;
	}
	return false;
}

bool next_character(lexer& input, const char& character) {
	if (character == '\n') {
		return next_line(input);
	}
	if (input.current_line[input.pos] == character) {
		input.pos++;
		return true;
	}
	return false;
}

bool next_string_until_one_of(lexer& input, string& output,
		const string& match) {
	size_t found = input.current_line.find_first_of(match, input.pos);
	if (found != string::npos) {
		output = input.current_line.substr(input.pos, found - input.pos);
		input.pos = found;
		return true;
	}
	return false;
}

bool next_string_until_newline(lexer& input, string& output) {
	if (input.pos == input.current_line.length()) {
		return false;
	}
	output = input.current_line.substr(input.pos);
	input.pos = input.current_line.length();
	return true;
}

bool next_string_until_char(lexer& input, string& output, const char& match) {
	size_t found = input.current_line.find_first_of(match, input.pos);
	if (found != string::npos) {
		output = input.current_line.substr(input.pos, found - input.pos);
		input.pos = found;
		return true;
	}
	return false;
}

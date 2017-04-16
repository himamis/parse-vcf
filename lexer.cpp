/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "lexer.h"

#include <iostream>

using namespace std;

namespace parsevcf {

static const string unknown = "unknown value";

void error(const lexer& input, const string& message) {
	cout << "Error parsing at line ";
	cout << input.line;
	cout << " at position ";
	cout << input.pos;
	cout << ".";
	cout << endl;
	cout << message;
	cout << endl;
	cout.flush();
}

void error_missing(const lexer& input, const string& expecting = unknown) {
	string message = "Error, was expecting ";
	message += expecting;
	message += ".";
	error(input, message);
}

bool next_line(lexer& input) {
	if (input.pos == input.current_line.length() - 1) {
		getline(input.stream, input.current_line);
		if (input.stream.eof()) {
			input.current_line = "";
			input.pos = 0;
			return false;
		}
		input.current_line += '\n';
		input.pos = 0;
		input.line++;
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

bool next_string(lexer& input, const string& str) {
	if (input.current_line.substr(input.pos, str.length()) == str) {
		input.pos += str.length();
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
	return next_string_until_char(input, output, '\n');
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

} /* namespace parsevcf */

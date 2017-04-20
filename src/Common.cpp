/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "Common.h"

namespace parsevcf {

std::vector<std::string> tokenize(const std::string& str, const char token) {
	std::vector<std::string> ret;
	int current_pos = 0;
	int sep_pos;
	while ((sep_pos = str.find(token, current_pos)) != std::string::npos) {
		ret.push_back(str.substr(current_pos, sep_pos - current_pos));
		current_pos = sep_pos + 1;
	}
	ret.push_back(str.substr(current_pos, str.length() - current_pos));
	return ret;
}

} /* namespace parsevcf */

#ifndef SNVENTRY_H_
#define SNVENTRY_H_

#include <string>
#include <vector>
#include <map>
#include <limits>

#include "Sample.h"

namespace parsevcf {

typedef float quality_t;

const quality_t kUnknownQuality = std::numeric_limits<float>::max();

struct SNVEntry {
	const std::string& chromosome;
	const unsigned long position;
	const std::vector<const std::string&>* id;
	const std::string& reference;
	const std::vector<const std::string&>* alternative;
	const quality_t quality;
	const std::vector<const std::string&>* filter;
	const std::map<const std::string&, const std::string&>* info;

	const std::vector<const std::string&>& format;
	const std::vector<const Sample&>& samples;
};

} /* namespace parsevcf */

#endif /* SNVENTRY_H_ */

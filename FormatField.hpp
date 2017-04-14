/*
 * FormatField.hpp
 *
 *  Created on: 14 Apr 2017
 *      Author: balazs
 */

#ifndef FORMATFIELD_HPP_
#define FORMATFIELD_HPP_

#include <string>
#include "CommonFields.hpp"

namespace parsevcf {

enum FormatType {
	kInteger,
	kFloat,
	kCharacter,
	kString
};

struct FormatField {
	const std::string& id;
	const number_t number;
	const FormatType type;
	const std::string& description;
};

} // namespace parsevcf

#endif /* FORMATFIELD_HPP_ */

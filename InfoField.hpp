/*
 * FileName.hpp
 *
 *  Created on: 14 Apr 2017
 *      Author: Balazs Bencze
 */

#ifndef INFOFIELD_HPP_
#define INFOFIELD_HPP_

#include <string>
#include "CommonFields.hpp"

namespace parsevcf {

enum InfoType {
	kInteger,
	kFloat,
	kFlag,
	kCharacter,
	kString
};

struct InfoField {
	InfoField(const std::string& id, const InfoType type, const number_t number, const std::string& description):
	id(id), type(type), number(number), description(description) {
		source = 0;
		version = 0;
	}
	const std::string& id;
	const InfoType type;
	const number_t number;
	const std::string& description;
	const std::string* source;
	const std::string* version;
};

} // namespace parsevcf

#endif /* INFOFIELD_HPP_ */

/*
 * FileName.hpp
 *
 *  Created on: 14 Apr 2017
 *      Author: Balazs Bencze
 */

#ifndef INFOFIELD_HPP_
#define INFOFIELD_HPP_

#include <string>

namespace parsevcf {

enum InfoType {
	kInteger,
	kFloat,
	kFlag,
	kCharacter,
	kString
};

typedef int number_t;

// If the field has one value per alternate allele
const number_t kAlternate = -1;
// If the field has one value for each possible allele (including the reference)
const number_t kReference = -2;
// If the field has one value for each possible genotype (more relevant to the FORMAT tags)
const number_t kGenotype = -3;
// If the number of possible values varies, is unknown, or is unbounded
const number_t kUnknown = -4;

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

/*
 * FilterField.hpp
 *
 *  Created on: 14 Apr 2017
 *      Author: balazs
 */

#ifndef FILTERFIELD_HPP_
#define FILTERFIELD_HPP_

#include <string>

namespace parsevcf {

struct FilterField {
	const std::string& id;
	const std::string& description;
};

} // namespace parsevcf

#endif /* FILTERFIELD_HPP_ */

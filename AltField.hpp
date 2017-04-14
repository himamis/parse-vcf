/*
 * AltField.hpp
 *
 *  Created on: 14 Apr 2017
 *      Author: balazs
 */

#ifndef ALTFIELD_HPP_
#define ALTFIELD_HPP_

#include <string>

namespace parsevcf {

struct AltField {

	const std::string& id;
	const std::string& description;
};

}

#endif /* ALTFIELD_HPP_ */

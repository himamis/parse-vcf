/*
 * CommonField.hpp
 *
 *  Created on: 14 Apr 2017
 *      Author: balazs
 */

#ifndef COMMONFIELDS_HPP_
#define COMMONFIELDS_HPP_

namespace parsevcf {

typedef int number_t;

// If the field has one value per alternate allele (A)
const number_t kAlternate = -1;
// If the field has one value for each possible allele (including the reference) (R)
const number_t kReference = -2;
// If the field has one value for each possible genotype (more relevant to the FORMAT tags) (G)
const number_t kGenotype = -3;
// If the number of possible values varies, is unknown, or is unbounded (.)
const number_t kUnknown = -4;

}

#endif /* COMMONFIELDS_HPP_ */

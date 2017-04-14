/*
 * main.cpp
 *
 *  Created on: 14 Apr 2017
 *      Author: balazs
 */

#include "InfoField.hpp"

using namespace parsevcf;

int main(int argc, char **argv) {

	parsevcf::InfoField field("csa", kInteger, kGenotype, "description");
	return 0;
}


/*
 * main.cpp
 *
 *  Created on: 14 Apr 2017
 *      Author: balazs
 */

#include "MetaInformation.hpp"

using namespace parsevcf;

int main(int argc, char **argv) {
	parsevcf::InfoField info = {.id = "ID", .type = kIntegerInfoType, .number = kGenotypeNumber,
			.description = "Description", .source = 0, .version = 0
	};
	return 0;
}


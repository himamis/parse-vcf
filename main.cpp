/*
 * main.cpp
 *
 *  Created on: 14 Apr 2017
 *      Author: balazs
 */

#include "MetaInformation.hpp"

using namespace parsevcf;

int main(int argc, char **argv) {
	parsevcf::InfoField field("ID", kIntegerInfoType, kGenotypeNumber, "Description");
	return 0;
}


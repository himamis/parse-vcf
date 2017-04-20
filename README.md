# parse-vcf

This library parses variant call files (VCF) written in standard c++. The parser implements the VCF4.3 grammar, although it is more permissive.

## Getting Started

Check out a copy of this library, include all the files from the `src` folder and you're ready to go.
A minimal example:
```
#include "DefaultHandler.h"
#include "SNVEntry.h"
#include "VCFParser.h"
#include <iostream>
#include <fstream>

class ExampleHandler: public parsevcf::DefaultHandler {

	void entry(const parsevcf::SNVEntry& entry) {
		std::cout << entry.id();
		std::cout.flush();
	}
};

int main() {
	std::fstream input("name-of-file.vcf");
	ExampleHandler handler;
	parsevcf::VCFParser parser(input, handler);

	parser.parse();
}

```

## Running the tests

To run the tests just call `make`.

## License

This project is licensed under the GPLv2 License - see the [LICENSE](LICENSE) file for details
#include <iostream>

#include "NatProcessor.h"

void displayhelp() {
	std::cout << "usage: ./NAT nat_file flow_file output_file" << std::endl;
	std::cout << "		nat_file: File name consisting network address mapping" << std::endl;
	std::cout << "		flow_file: File name consisting list of IP addresses to be translated" << std::endl;
	std::cout << "		output_file: File name of translated IP addresses" << std::endl;
}

int main(int argc, char **argv) {

	// show help in case of insufficient arguments
	if (4 != argc) {
		displayhelp();
		return 1;
	}

	NatProcessor natproc;
	string natfile = string(argv[1]);
	string flowfile = string(argv[2]);
	string outputfile = string(argv[3]);

	natproc.parseNatFile(natfile);
	natproc.translateFlowFile(flowfile, outputfile);
}
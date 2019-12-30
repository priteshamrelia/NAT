#include <string>

#include "NatProcessor.h"

NatProcessor::NatProcessor()
{
}

NatProcessor::~NatProcessor()
{
}

// divide string into two parts, left and right based on delim provided
int split(string s, char delim, string &left, string &right) {

	// returns index of first delimeter matching
	size_t delim_index = s.find(delim);

	// In case, no delimeter found in given string, return -1 indicating error
	// which is handled during every call of this function to skip erroneous entry
	if (delim_index == string::npos) {
		return -1;
	}

	// based on delimeter index, divides string into left and right string
	left = s.substr(0, delim_index);
	right = s.substr(delim_index + 1);

	return 0;
}

// This function is responsible for processing NAT file
// Process each line read from NAT file and populate appropriate map
void NatProcessor::processNatLine(string line) {
	// Split into incoming and outgoing translation
	string in, out;
	if (-1 == split(line, ',', in, out))
		return;

	// Split into ip and port to make checking wildcards easy
	string ip, port;
	if (-1 == split(in, ':', ip, port))
		return;

	// Only port dependent entries
	if (!ip.compare("*")) {
		port_specified.emplace(port, out);
	}
	// Only IP dependent entries
	else if (!port.compare("*")) {
		ip_specified.emplace(ip, out);
	}
	// For entries that require both port and IP
	else {
		port_ip_specified.emplace(in, out);
	}
}


// This function is responsible for processing FLOW file
// Process each line read from FLOW file and 
// write to output file by analysing all map entries
void NatProcessor::processFlowLine(string line) {
	unordered_map<string, string>::const_iterator found;

	// First, we check for port and ip combination
	if ((found = port_ip_specified.find(line)) != port_ip_specified.end()) {
		this->outfile << line << " -> " << (*found).second << endl;
		return;
	}

	string ip, port;
	if (-1 == split(line, ':', ip, port))
		return;

	// If port and ip combination doesn't match, we check one by one, first IP and then Port
	if ((found = ip_specified.find(ip)) != ip_specified.end()) {
		this->outfile << line << " -> " << (*found).second << endl;
		return;
	}
	if ((found = port_specified.find(port)) != port_specified.end()) {
		this->outfile << line << " -> " << (*found).second << endl;
		return;
	}

	// In case, no entry from any mapping matches with incoming entry
	this->outfile << "No nat match for " << line << endl;
}


// This function process file based on given function handler.
// Function pointer is passed while calling this method and distinguish processing of 
// nat file with processing of flow file
void NatProcessor::processFile(string filename, void(NatProcessor::*filehandler)(string)) {
	string line;
	ifstream infile(filename);

	// Attemp to open file and process line by line
	if (infile.is_open()) {
		while (getline(infile, line)) {
			(this->*filehandler)(line);
		}
	}
	// exit the code if file is not found or already locked by another resource in the system.
	else {
		fprintf(stderr, "Can't open input file %s.\n", filename.c_str());
		exit(1);
	}

	infile.close();
}


void NatProcessor::parseNatFile(string natfilename)
{
	this->port_ip_specified.clear();
	this->ip_specified.clear();
	this->port_specified.clear();

	processFile(natfilename, &NatProcessor::processNatLine);
}


void NatProcessor::translateFlowFile(string flowfilename, string outfilename)
{
	this->outfile.open(outfilename);
	processFile(flowfilename, &NatProcessor::processFlowLine);
	this->outfile.close();
}

#pragma once

#include <unordered_map>
#include <fstream>

using namespace std;

class NatProcessor
{
public:
	NatProcessor();
	~NatProcessor();
	void parseNatFile(string natfilename);
	void translateFlowFile(string flowfilename, string outfilename);
private:
	unordered_map<string, string> port_ip_specified, ip_specified, port_specified;
	ofstream outfile;

	void processFile(string natfilename, void(NatProcessor::* filehandler)(string));
	void processNatLine(string line);
	void processFlowLine(string line);
};

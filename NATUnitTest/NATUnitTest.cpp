#include "pch.h"
#include "CppUnitTest.h"

#include <fstream>
#include "../NAT/NatProcessor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NATUnitTest
{
	TEST_CLASS(NATUnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			NatProcessor natproc;
			string natfile = "NAT";
			string flowfile = "FLOW";
			string outputfile = "OUTPUT";

			natproc.parseNatFile(natfile);
			natproc.translateFlowFile(flowfile, outputfile);
			
			string expected[] = {"10.0.1.1:8080 -> 192.168.0.1 : 80", 
				"No nat match for 5.6.7.8:55555",
				"10.0.1.1:8086 -> 192.168.0.4:80",
				"9.8.7.6:21 -> 1.2.3.4:12",
				"No nat match for 10.1.1.2:8080",
				"No nat match for 34.65.12.9:22",
				"10.0.1.2:8080 -> 1.1.1.1:1"};
			string line;
			
			ifstream infile(outputfile);
			if (infile.is_open()) {
				int count = 0;
				while (getline(infile, line)) {
					Assert::AreEqual(line, expected[count]);
					count += 1;
				}
			}
		}

		TEST_METHOD(TestMethod2)
		{
			NatProcessor natproc;
			string natfile = "NAT_multiple_pattern_matching";
			string flowfile = "FLOW_multiple_pattern_matching";
			string outputfile = "OUTPUT";

			natproc.parseNatFile(natfile);
			natproc.translateFlowFile(flowfile, outputfile);

			string expected[] = { "10.0.1.1:8080 -> 192.168.0.1:80",
				"No nat match for 5.6.7.8:55555",
				"10.0.1.1:8086 -> 192.168.0.4:80",
				"9.8.7.6:8080 -> 1.2.3.4:12",
				"10.1.1.2:8080 -> 1.2.3.4:12",
				"No nat match for 34.65.12.9:22",
				"10.0.1.2:8080 -> 1.1.1.1:1" };
			string line;

			ifstream infile(outputfile);
			if (infile.is_open()) {
				int count = 0;
				while (getline(infile, line)) {
					Assert::AreEqual(line, expected[count]);
					count += 1;
				}
			}
		}

		TEST_METHOD(TestMethod3)
		{
			NatProcessor natproc;
			string natfile = "NAT_all_pattern_matching";
			string flowfile = "FLOW_all_pattern_matching";
			string outputfile = "OUTPUT";

			natproc.parseNatFile(natfile);
			natproc.translateFlowFile(flowfile, outputfile);

			string expected[] = { "10.0.1.1:8080 -> 192.168.0.1:80",
				"No nat match for 5.6.7.8:55555",
				"10.0.1.1:8086 -> 192.168.0.4:80",
				"No nat match for 9.8.7.6:8080",
				"No nat match for 10.1.1.2:8080",
				"No nat match for 34.65.12.9:22",
				"10.0.1.2:8080 -> 1.1.1.1:1" };
			string line;

			ifstream infile(outputfile);
			if (infile.is_open()) {
				int count = 0;
				while (getline(infile, line)) {
					Assert::AreEqual(line, expected[count]);
					count += 1;
				}
			}
		}
	};
}

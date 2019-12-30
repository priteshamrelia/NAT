# NAT
Implementation of a simplified NAT (Network Address Translation)

Given project implements a NAT (Network Address Translation) that maps in addresses to out addresses. It supports IPv4 and port combination as an address. 

The NAT file will describe the translations for your NAT Table. The format of each line will be as so:
<ip>:<port>,<ip>:<port>

The FLOW file will describe the incoming flows through your NAT. The format of each line will be as so
<ip>:<port>


It stores mapping of in addresses and out addresses called NAT table by parsing given NAT file. And for a given FLOW file, it looks for match for each line in NAT table. Based on match found, it redirects appropriate output into output file.

NAT table contains following three maps:
  port vs out address
  ip vs out address
  ip:port vs out address


NATUnitTest project contains unit testing of project NAT. It tests implementation with all possible combination of inputs. In case of invalid entry either in NAT file or in FLOW file, it skips entry and proceed for further mapping.

Future Work:
  Solution is not able to identify IP addresses based on specific classes (Class A, B, C). For example,
    given NAT entry 10.0.*.*:8080,192.168.2.1:80, all addresses starting with 10.0 and with port number 8080 should be mapped to 192.168.2.1:80
    Currently, either it doesn't parse partial combination of IP and port address mapping.

#include <iostream>
#include "DataXML.h"

#include "Registry.h"


int main() {
	DataXML obj;
	obj.read("File.xml");
	Registries regs = obj.registries;
	Registry customers = regs.customers;

	//obj.write("File2.xml");
}
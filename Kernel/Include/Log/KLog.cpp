#include "KLog.h"

void kostream::kostreamPrint() {
	KPrintString(outputString);
}

kostream kostream::write(const char *data) {
	kostream output = kostream(data);
	output.kostreamPrint();
	return output;
}

kostream kostream::write(string str) {
	kostream output = kostream(outputString + str);
	output.kostreamPrint();
	return output;
}

kostream klog() {
	kostream infoStream = kostream();
	return infoStream;
}
// protobufcase2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void ListMsg(const lm::helloworld & msg) {
	cout << msg.id() << endl;
	cout << msg.str() << endl;
}

int main(void)
{
	//写入log
	lm::helloworld msg1;
	msg1.set_id(101);
	msg1.set_str("hello");

	// write the new address book back to disk. 
	fstream output("./log", ios::out | ios::trunc | ios::binary);

	if (!msg1.SerializeToOstream(&output)) {
		cerr << "failed to write msg." << endl;
		return -1;
	}
	output.close();


	//读进内存，屏幕显示
	lm::helloworld msg2;

	fstream input("./log", ios::in | ios::binary);
	if (!msg2.ParseFromIstream(&input)) {
		cerr << "Failed to parse address book." << endl;
		return -1;
	}
	input.close();

	ListMsg(msg2);

	getchar();

	return 0;
}


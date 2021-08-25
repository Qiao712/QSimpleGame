#include "Singleton.h"
#include "StringIdManager.h"
#include "Event.h"
#include "EventA.h"
#include "PoolAllocator.h"

#include <iostream>
#include <typeinfo>
using namespace std;
using namespace QSimpleGame;

class B {
public:
	int a;
	char b;
	B() {
		cout << "B" << endl;
	}
};


class Test {
public:
	Test() {
		cout << "Construct Test" << endl;
	}
	~Test() {
		cout << "Destory Test" << endl;
	}
};

union TestU {
	TestU(){}
	~TestU(){}
	Test t;
	int a;
};

int main() {
	StringIdManager::init();

	//EVENT类型识别
	auto& SIM = StringIdManager::instance();
	Event a;
	EventA b;
	cout << SIM.getString(a.getType()) <<' '<< SIM.getString(b.getType() )<< endl;

	//池分配器
	PoolAllocator<Test>::init(1000);
	PoolAllocator<Test>& pa = PoolAllocator<Test>::instance();
	for (int i = 0; i < 50; i++) {
		pa.construct();
	}
	Test* t = pa.construct();
	cout << pa.getNum();
	pa.destory(t);


	StringIdManager::destory();
}
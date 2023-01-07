#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#pragma
#ifndef Node_H
#define Node_H
using namespace std;

class Node
{
private:

public:
	int num;
	char sym;
	Node* l, * r;
	Node() {
		l=NULL;
		r = NULL;
	}
	Node(Node* L, Node* R)
	{
		l = L;
		r = R;
		num = L->num + R->num;
	}
};
#endif

struct himan {
	char c = 0;
	int count = 0;
};
struct t {
	char c;
	vector<bool> vec;
};
void coding();
void decode();
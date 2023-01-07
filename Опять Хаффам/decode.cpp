#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;
vector<bool> vec1;
t tab1[255];
void Build_dec(Node* root) {
	if (root->l != NULL) // ���� ����� ���-�� ���� ������ � ������ 0
	{
		vec1.push_back(0);
		Build_dec(root->l); // ���������� �������� �������
	}

	if (root->r != NULL)// ���� ������ ���-�� ���� ������ � ������ 1
	{
		vec1.push_back(1);
		Build_dec(root->r);// ���������� �������� �������
	}

	if (root->sym) {
		tab1[root->sym].vec = vec1;  // ���� ���������� �� �����, �� ����������� � � ����� � tab1

	}
	if (!vec1.empty()) {
		vec1.pop_back(); //��������� ��� �� 1}
	}
}
void decode() {
	setlocale(LC_ALL, "Russian");
	string file_name_to_decode;
	cout << "������� ��� ������������� �����: ";
	cin >> file_name_to_decode;
	ifstream file1;
	file1.open(file_name_to_decode.c_str(),ios::out | ios::binary);
	if (file1) { cout << "���� ������� ������" << endl; }
	else { cout << "���� �� ������" << endl; return; }
	himan m[255];
	int N = 0;
	
	int zise;
	file1.read((char*)&zise, sizeof(int));
	file1.seekg(4, ios::beg);
	char blu;
	int c;
	for (int i = 4; i < (zise * 5); i = i + 5) {
		file1.seekg(i, ios::beg);
		file1.read((char*)&blu, sizeof(char));
		file1.seekg(i + 1, ios::beg);
		file1.read((char*)&c, sizeof(int));
		m[blu].count = c;
		m[blu].c = blu;
	}
	for (int i = 0; i < 255; i++) {
		if (m[i].count > 0) { N++; }
	}
	int step = 255 / 2;       // � ������ ��������� ��������� �������� ����������
	while (step > 0) {       // ������ ��������
		for (int i = step; i < 255; i++) {
			int j = i;
			himan x = m[j];
			while ((j >= step) && (x.count < m[j - step].count)) { //������ ������� ������ ������
				m[j] = m[j - step];
				j = j - step;
			}
			m[j] = x;
		}
		step = step / 2;     // ��������� ���, �������� ���� ��� ������ ����
	}
	list<Node*> rar;
	for (int i = 0; i < 255; i++) {
		if (m[i].count > 0) {
			Node* k = new Node;
			k->sym = m[i].c;
			k->num = m[i].count;
			rar.push_back(k);
		}
	}
	while (rar.size() != 1) // ���� �� ���������� ���� �������
	{
		Node* SonL = rar.front(); // ������ ������ ������� ���� ������ ������� �� list 
		rar.pop_front(); // ������� �������
		Node* SonR = rar.front(); // ������ ������� ������� ���� ������(����� �������� �������) ������� �� list 
		rar.pop_front(); // ������� �������
		Node* parent = new Node(SonL, SonR); // ������ ���� 
		rar.push_back(parent); // ��������� ��� � list
	}
	Node* root = rar.front();
	Build_dec(root);
	Node* p = root;
	int count = 0;
	char byte = 0;
	byte = file1.get();
	while (!file1.eof())
	{
		bool b = byte & (1 << (7 - count)); // ��������� 1 ��� 0 � ���������
		if (b) { p = p->r; }
		else { p = p->l; } // ���� 1 ��������� ������ ����� �����
		if ((p->sym)) { cout << p->sym; p = root; } // ������� ������ 
		count++;
		if (count == 8) { count = 0; byte = file1.get(); } // ���� cout = 8 �������� ��� � ������������� ��������� ������

	}
	file1.close(); // �� �������� ������� ����
	return;
}
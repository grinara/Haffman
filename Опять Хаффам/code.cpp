#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;
vector<bool> vec;
t tab[255];
void Build_cod(Node* root) {
	if (root->l != NULL) // ���� ����� ���-�� ���� ������ � ������ 0
	{
		vec.push_back(0);
		Build_cod(root->l); // ���������� �������� �������
	}

	if (root->r != NULL)// ���� ������ ���-�� ���� ������ � ������ 1
	{
		vec.push_back(1);
		Build_cod(root->r);// ���������� �������� �������
	}

	if (root->sym) {
		int i = 0;
		for (; i < 255; i++) {
			if (root->sym == tab[i].c) {
				break;
			}
		}
		tab[i].vec = vec;  // ���� ���������� �� �����, �� ����������� � � ����� � tab
	}
	if (!vec.empty()) {	vec.pop_back(); }//��������� ��� �� 1
}
void coding() {
	setlocale(LC_ALL, "Russian");
	string file_name_to_code;
	cout << "������� ��� ����� ��� �����������: ";
	cin>>file_name_to_code;
	ifstream file1;
	file1.open(file_name_to_code.c_str(), ios::in | ios::binary);
	if (file1) { cout << "���� ������� ������" << endl; }
	else { cout << "���� �� ������" << endl; return; }
	himan m[255];
	int N=0;
	while (!file1.eof()) { //���� ���������� ��������� ������� �������
		char  c0 = file1.get();
			for (int i = 0; i < 255; i++) {
				if (m[i].c == 0) {
					m[i].c = c0;
					m[i].count++;
					tab[i].c = c0;
					break;
				}
				if (m[i].c == c0) {
					m[i].count++;
					break;
				}
		}
	}
	for (int i = 0; i < 255; i++) {if (m[i].count > 0) { N++; }}
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
	list <Node*> da;
	for (int i = 0; i < 255; i++) {
		if (m[i].count >0) {
			Node* k = new Node;
			k->sym = m[i].c;
			k->num = m[i].count;
			da.push_back(k);
		}
	}
	while (da.size() != 1) // ���� �� ���������� ���� �������
	{
		Node* left = da.front(); // ������ ������ ������� ���� ������ ������� �� list 
		da.pop_front(); // ������� �������
		Node* right = da.front(); // ������ ������� ������� ���� ������(����� �������� �������) ������� �� list 
		da.pop_front(); // ������� �������
		Node* nod = new Node(left, right); // ������ ���� 
		da.push_back(nod); // ��������� ��� � list
	}
	Build_cod(da.front());
	file1.clear(); // ���������� ���������
	file1.seekg(0);// ���������� ��������� � ������ �����

	fstream file1_cip("112.txt", ios::binary | ios::out);
	int c = N;
	char kar = 0;
	file1_cip.write((char*)&c, sizeof(int));
	for (int i = 0; i < 255;i++) {
		if (m[i].count >0) {
			kar = m[i].c;
			c = m[i].count;
			file1_cip.write((char*)&kar, sizeof(char));
			file1_cip.write((char*)&c, sizeof(int));
		}
	}

	int count = 0; // �������
	char b = 0; //��������������� ����������
	while (!file1.eof()) {
		char c = file1.get(); // ����� ����������
		int i = 0;
			for (; tab[i].c != c; i++);
			vector<bool> x = tab[i].vec;
			for (int j = 0; j < x.size(); j++) {
				b = b | x[j] << (7 - count); // ����������� ������ x � ����
				count++;
				if (count == 8) { count = 0; file1_cip << b; b = 0; } // ���� �������� count = 8  ���� ��������� � file1_cip
			}
	}

	file1.close(); // �� �������� ������� ����
	file1_cip.close(); // �� �������� ������� ����
	return;
	
}



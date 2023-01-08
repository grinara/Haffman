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
	if (root->l != NULL) // если слева что-то есть вносим в вектор 0
	{
		vec1.push_back(0);
		Build_dec(root->l); // рекурсивно вызываем функцию
	}

	if (root->r != NULL)// если справа что-то есть вносим в вектор 1
	{
		vec1.push_back(1);
		Build_dec(root->r);// рекурсивно вызываем функцию
	}

	if (root->sym) {
		int i = 0;
		for (; root->sym != tab1[i].c && i < 255; i++);
		tab1[i].vec = vec1;  // если наткнулись на букву, то ассоциируем её с кодом в tab
	}
	if (!vec1.empty()) {
		vec1.pop_back(); //сокращаем код на 1}
	}
}
void decode() {
	setlocale(LC_ALL, "Russian");
	string file_name_to_decode;
	cout << "Введите имя декадируемого файла: ";
	cin >> file_name_to_decode;
	ifstream file1;
	file1.open(file_name_to_decode.c_str(),ios::out | ios::binary);
	if (file1) { cout << "Файл успешно открыт" << endl; }
	else { cout << "Файл не открыт" << endl; return; }
	himan m[255];
	int N = 0;
	
	int zise;
	file1.read((char*)&zise, sizeof(int));
	file1.seekg(4, ios::beg);
	char blu;
	int c;
	for (int i = 4,j=0; i < (zise * 5) && j<255; i = i + 5,j++) {
		file1.seekg(i, ios::beg);
		file1.read((char*)&blu, sizeof(char));
		file1.seekg(i + 1, ios::beg);
		file1.read((char*)&c, sizeof(int));
		m[j].count = c;
		m[j].c = blu;
		tab1[j].c = blu;
	}
	for (int i = 0; i < 255; i++) {
		if (m[i].count > 0) { N++; }
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
	while (rar.size() != 1) // пока не останеться один элемент
	{
		Node* SonL = rar.front(); // создаём левого потомка берём первый элемент из list 
		rar.pop_front(); // удаляем элемент
		Node* SonR = rar.front(); // создаём правого потомка берём первый(после удаления другого) элемент из list 
		rar.pop_front(); // удаляем элемент
		Node* parent = new Node(SonL, SonR); // создаём узел 
		rar.push_back(parent); // добавляем его в list
	}
	Node* root = rar.front();
	Build_dec(root);
	Node* p = root;
	int count = 0;
	char byte = 0;
	byte = file1.get();
	while (!file1.eof())
	{
		bool b = byte & (1 << (7 - count)); // проверяем 1 или 0 в кодировке
		if (b) { p = p->r; }
		else { p = p->l; } // если 1 двигаемся вправо иначе влево
		if ((p->sym)) { cout << p->sym; p = root; } // выводим символ 
		count++;
		if (count == 8) { count = 0; byte = file1.get(); } // если cout = 8 обнуляем его и рассматриваем следующий символ

	}
	file1.close(); // не забываем закрыть файл
	return;
}
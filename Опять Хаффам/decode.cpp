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
		tab1[root->sym].vec = vec1;  // если наткнулись на букву, то ассоциируем её с годом в tab1

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
	int step = 255 / 2;       // в группе выбранных элементов проводим сортировку
	while (step > 0) {       // прямой вставкой
		for (int i = step; i < 255; i++) {
			int j = i;
			himan x = m[j];
			while ((j >= step) && (x.count < m[j - step].count)) { //вместо обменов сделай сдвиги
				m[j] = m[j - step];
				j = j - step;
			}
			m[j] = x;
		}
		step = step / 2;     // уменьшаем шаг, повторям пока шаг больше нуля
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
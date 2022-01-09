#include "md5.h"
#include <string>
#include <sstream>
#include <ctime>
#include <iostream>
#include <bitset>

using namespace std;

int Euclid(int e, int fi) {
	int a = 0, b = 0;
	if (e > fi) {
		a = e;
		b = fi;
	} else {
		b = e;
		a = fi;
	}
	int u = 0;
	int v = 1;
	int m = a;
	while (b != 0) {
		int q = a / b;
		int r = a % b;
		int vk = u - v * q;
		a = b;
		b = r;
		u = v;
		v = vk;
	}
	while (u < 0)u += m;
	while (u >= m)u -= m;
	return u;
}

int Prime_number(int P) {
	for (int i = 2; i <= P / 2; i++) {
		if (P % i == 0)return 0;
	}
	return 1;
}

int Generate_P() {
	int P = 0;
	do {
		P = rand() % 99 + 10;
	} while (Prime_number(P) != 1);
	return P;
}

int Generate_Q(int p) {
	int q = 0;
	do {
		q = rand() % 99 + 10;
	} while (Prime_number(q) != 1);
	return q;
}

int Greatest_common_divisor(int a, int b) {
	if (a > b) { a = a, b = b; }
	else {
		int c = a;
		a = b, b = c;
	}
	int r;
	while (b != 0) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int Generate_e(int fi) {
	int e = 0;
	do {
		e = rand() % (fi - 1) + 2;
	} while (Greatest_common_divisor(e, fi) != 1);
	return e;
}

int step(int a, int b, int c) {
	int r = a;
	for (int i = 1; i < b; i++) {
		r *= a;
		while (r > c) {
			r = r - c;
		}
	}
	return r;
}

void RSA(int *mass) {
	int p, q, n, fi, e, d, m, l = 1, t, c;
	p = Generate_P();
	q = Generate_Q(p);
	n = p * q;
	fi = (p - 1) * (q - 1);
	e = Generate_e(fi);
	d = Euclid(e, fi);
	m = 100;
	c = step(m, e, n);
	t = step(c, d, n);
	//if (t == m)cout << "OK";
	mass[0] = e;
	mass[1] = d;
	mass[2] = n;

}

string electronic_signature(string text) {
	srand(time(0));
	string Code;
	string RSA_encode_result;
	int i, m, mass[3], HASH;
	RSA(mass);
	Code = md5hash(text);
	cout << "m(md5 в int): " << endl;
	for (i = 0; i < Code.length(); i++) {
		m = int(Code[i]);
		cout << m << " ";
		HASH = step(m, mass[0], mass[2]);
		RSA_encode_result += std::to_string(HASH);
		RSA_encode_result += ' ';
	}
	RSA_encode_result += std::to_string(mass[1]);//дописывваем d в конец(e используется в шифровании)
	RSA_encode_result += ' ';
	RSA_encode_result += std::to_string(mass[2]);//дописывваем n(p*q) в конец
	return RSA_encode_result;
}

string Decode_RSA(string text) {
	string decode_result;
	string code = "1";
	int j = 1, word_number_counter = 1, index;
	int mass_1 = 0, mass_2 = 0, decode, encode_number;
	//Кол-во слов в эл подписи
	for (int i = 0; i < text.length(); i++) {
		if (text[i] == ' ') { j++; }
	}
	index = j - 1;
	//записть d и n в переменные для декодирования
	for (int i = 0; i <= text.length(); i++) {//проходимся по подписи
		if (text[i] == ' ' ||
		    i == text.length()) {//условие конца слов 2-ой пункт из-за последнего слова после него идет"/0"
			if (word_number_counter == j - 1) {//номер пред последнего слова (d)
				istringstream num_1(code, istringstream::in);//перевод из строки в int другие ф не работают хз почему
				num_1 >> mass_1;
			}
			if (i == text.length()) {//условие последнего слова (n)
				code += text[i];
				istringstream num_2(code, istringstream::in);
				num_2 >> mass_2;
			}
			word_number_counter++;//счетчик номера слова
			code.clear();//очистка строки со словом так как при каждом цикле мы забиваем его по новой
		}
		code += text[i];
	}
	code.clear();//очистка строки со словом так как при каждом цикле мы забиваем его по новой
	word_number_counter = 1;
	//декодирование
	for (int i = 0; i < text.length(); i++) {
		if (text[i] == ' ' || i == text.length()) {
			if (word_number_counter == index)break;//index номер пред последнего слова
			istringstream num(code, istringstream::in);
			num >> encode_number;
			decode = step(encode_number, mass_1, mass_2);
			decode_result += std::to_string(decode);
			decode_result += ' ';
			code.clear();
			i++;
			word_number_counter++;
		}
		code += text[i];
	}
	cout << endl;
	return decode_result;
}

string Convert_to_integer(string Code) {
	string number;
	int c;
	for (int i = 0; i < Code.length(); i++) {
		c = int(Code[i]);
		number += std::to_string(c);
		number += " ";
	}
	return number;
}


int main() {
	string text, code, decode, md5text;

	getline(cin, text);

	cout << md5hash(text) << endl;
	cout << Convert_to_integer(md5hash(text)) << endl;

	code = electronic_signature(text);

	cout << "code " << code << endl;
	text = md5hash(text);
	decode = Decode_RSA(code);
	cout << "decode" << endl;
	cout << decode;
	return 0;
}

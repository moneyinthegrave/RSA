#include <iostream>
#include <random>

using namespace  std;
// использование рандомной генерации чисел с помощью вихря мерсенна
std::random_device rd;
std::mt19937 mersenne(rd());
// проверка на простое число
unsigned int Prost(unsigned int P){
	for( int i=2;i<=P/2;i++){
		if(P%i==0)return 0;
	}
	return 1;
}
//
unsigned int gcd(unsigned int a,unsigned int b){
	(a>b)? a=a,b=b:a=b, b=a;
	unsigned int r;
//	while(b!=0){
//		r=a%b;
//		a=b;b=r;
//	}
	while(b!=0){
		r=a%b;
		a=b;b=r;
	}
	return a;
}
// создание числа р
unsigned int Gen_P(){
	unsigned int P;
	do{
		P=mersenne();
	}while(Prost(P)!=1);
	return P;
}
// создание числа q
// требуются проверки
// проблемы:
// 1 может вызвать сама себя даже если условие выхода истинно
// 2 возвращется 0
unsigned int Gen_Q(unsigned int p){
	unsigned int q;
	do{
		q=mersenne();
	}while(Prost(q)!=1||q==p);
	return q;
}
// создание числа e
unsigned int Gen_e(unsigned int fi){
	unsigned int e;
	do{
		e=mersenne(); //
	}while(gcd(e, fi)!=1 && e > fi);
	return e;
}
// создание числа d
unsigned int Gen_d(unsigned int e,unsigned  int fi){
	unsigned int q, r, u, V; u=1,V=0; unsigned int buf, k=fi;
	while(e!=0){
		q=fi/e;
		r=fi%e;
		u=u-V*q;
		V=V-u*q;
		fi=e;e=r;
		buf=u;
		u=V;V=buf;
	}
	while(u<0){u+=k;}
	while(u>=k){u-=k;}
	return u;
}
 int step( unsigned long long int a, unsigned long long int b, unsigned long long int c){
	 int r=a;
	 cout << "run step" ;

	 cout << c << "is c";
	 cout << a << "is a";
	 cout << b << "is b";
	for( int i=1;i<b;i++){
		r*=a;
		while(r>=c){r-=c;}
		 }
	cout << "run return step";
	return r;
}

int main()
{
	int t, c,m;
	do {
	unsigned int p, q, fi, e, d;
	unsigned long  long int n;
	cout << "run p" << endl;
	p=Gen_P();
	cout << "p " << p << endl;
	cout << "run q" << endl;
	q = Gen_Q(p);
	cout << "q " << q << endl;
	cout << "run n" << endl;
	cout << "p " << p << " q "<< q << endl;
	n=p*q;
	cout << n << " ist n " << endl;
	cout << "run fi" << endl;
	fi=(p-1)*(q-1);
	cout << "run e" << endl;
	e=Gen_e(fi);
	cout << "e " << e << endl;
	cout << "run d" << endl;
	d=Gen_d(e, fi);
	unsigned int max_unsigned_int_size = -1;
	cout << max_unsigned_int_size << "max_unsigned_int_size" << endl;
	cout << "d " << d ;
	m=5;

	c = step(m, e, n);
	 t=step(c,d,n); }
	while (t != m);

	cout << endl;
	cout << "run ok" << endl;
	cout << t << "t" << m << "m";

	return 0;
}
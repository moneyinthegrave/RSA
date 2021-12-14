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
	}while(Prost(P)==1);
	return P;
}
// создание числа q
// требуются проверки
//
//
//
unsigned int Gen_Q(unsigned int p, int num, int num2){
	unsigned int q;
	do{
		q=mersenne();
		int num2 = 0;
		while (q /= 10) {
			num2++;
			std::cout << num2 << " " << q << std::endl;
		}
		cout << "num2" << num2<< endl;
		if (num != num2) {
			q = Gen_Q(p, num, num2);
		}
		else {
			return q;
		}
	}while(Prost(q)==1||q==p||num!=num2);
}
// создание числа e
unsigned int Gen_e(unsigned int fi){
	unsigned int e;
	do{
		e=mersenne(); //
	}while(gcd(e, fi)!=1 && e > fi);
	cout << e << endl;
	return e;
}
// создание числа d
unsigned int Gen_d(unsigned int e,unsigned  int fi){
	unsigned int q, r, u, V; u=1,V=0; unsigned int k=fi;
	while(e!=0){
		unsigned int buf;
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
unsigned int step(unsigned int a,unsigned int b,unsigned int c){
	unsigned int r=a;
	for(unsigned int i=1;i<b;i++){
		r*=a;
		while(r>=c){r-=c;}
	}return r;
}

int main()
{
	int num = 0, num2 = 0;
	unsigned int p, q, n, fi, e, d;
	p=Gen_P();
	cout << "p " << p << endl;
	while (p /= 10) {
		num++;
		std::cout << num << " " << p << std::endl;
	}
	cout << "num" << num<< endl;

	q = Gen_Q(p, num, num2);

	cout << "q " << q << endl;
	n=p*q;
	fi=(p-1)*(q-1);
	e=Gen_e(fi);
	cout << "e " << e << endl;
	d=Gen_d(e, fi);
	unsigned int m=5;
	unsigned int c=step(m,e,n);
	unsigned int t=step(c,d,n);
	if (t==m){
		cout<<"OK";
	}
	cout << endl;
	cout << c<<endl;
	cout << t<<endl;
	cout << m<<endl;
	return 0;
}
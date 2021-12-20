#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <random>

std::random_device rd;
std::mt19937 mersenne(rd());
bool isPrime(long int prime);
long int Gen_e( long int t );
long int gcd( long int e, long int t );
long int Gen_d( long int e, long int t );
long int encrypt( long int i, long int e, long int n );
long int decrypt(long int i, long int d, long int n );

long int Gen_P(){
	long int P;
	P=mersenne();
	return P;
}

long int Gen_Q(){
	long int q;

	q=mersenne();
	;
	return q;
}

int main( )
{
	long int p, q, n, t, e, d;

	long int encryptedText[100];
	memset(encryptedText, 0, sizeof(encryptedText));

	long int decryptedText[100];
	memset(decryptedText, 0, sizeof(decryptedText));

	bool flag;

	std::string msg;

	// Cоздание открытого и секретного ключей

	// 1. Выбираются два различных случайных простых числа p и q заданного размера

	do
	{
		p = Gen_P();
		flag = isPrime( p );

		if ( flag == false )
		{
		}
	} while ( flag == false );


	do
	{
		q =Gen_Q();
		flag = isPrime( q );

		if ( flag == false )
		{
		}
	} while ( flag == false);

	// 2. Вычисляется их произведение n = p ⋅ q, которое называется модулем.
	n = p * q;
	std::cout << "\nResult of computing n = p*q = " << n << std::endl;

	// 3. Вычисляется значение функции Эйлера от числа n: φ(n) = (p−1)⋅(q−1)
	t = ( p - 1 ) * ( q - 1 );
	std::cout << "Result of computing Euler's totient function:\t t = " << t << std::endl;

	// 4. Выбирается целое число e ( 1 < e < φ(n) ), взаимно простое со значением функции Эйлера (t)
	//	  Число e называется открытой экспонентой
	e = Gen_e( t );

	// 5. Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
	//    d ⋅ e ≡ 1 (mod φ(n))
	d = Gen_d( e, t );

	// 6. Пара {e, n} публикуется в качестве открытого ключа RSA
	std::cout << "\nRSA public key is (n = " << n << ", e = " << e << ")" << std::endl;

	// 7. Пара {d, n} играет роль закрытого ключа RSA и держится в секрете
	std::cout << "RSA private key is (n = " << n << ", d = " << d << ")" << std::endl;


	return 0;
}

bool isPrime( long int prime)
{
	long int i, j;

	j = (long int)sqrt((long double)prime);

	for ( i = 2; i <= j; i++)
	{
		if ( prime % i == 0 )
		{
			return false;
		}
	}

	return true;
}

long int Gen_e( long int t )
{
	// Выбирается целое число e ( 1 < e < t ) // взаимно простое со значением функции Эйлера (t)

	long int e;

	for ( e = 2; e < t; e++ )
	{
		if (gcd( e, t ) == 1 )
		{
			return e;
		}
	}

	return -1;
}

long int gcd( long int e, long int t )
{
	while ( e > 0 )
	{
		long int myTemp;

		myTemp = e;
		e = t % e;
		t = myTemp;
	}

	return t;
}

long int Gen_d( long int e, long int t)
{
	// Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
	//    d ⋅ e ≡ 1 (mod φ(n))

	long int d;
	long int k = 1;

	while ( 1 )
	{
		k = k + t;

		if ( k % e == 0)
		{
			d = (k / e);
			return d;
		}
	}

}


long int encrypt( long int i, long int e, long int n )
{
	long int current, result;

	current = i - 97;
	result = 1;

	for ( long int j = 0; j < e; j++ )
	{
		result = result * current;
		result = result % n;
	}

	return result;
}

long int decrypt(long int i, long int d, long int n)
{
	long int current, result;

	current = i;
	result = 1;

	for ( long int j = 0; j < d; j++ )
	{
		result = result * current;
		result = result % n;
	}
	return result + 97;
}

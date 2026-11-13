#include <iostream>
#include <random>
#include <string>
#include <chrono>

using namespace std;

const string alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+";
const int length=20;

void Password();


int main()
{
	Password();	
}

void Password()
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 generator(seed);
	uniform_int_distribution<int> distribution(0, alphabet.length() - 1);
	string pass;
	for(int i = 0; i<length; i++)
	{

		int random_index=distribution(generator);
		pass.append(1, alphabet[random_index]);
	}
	cout<<pass<<endl;
}


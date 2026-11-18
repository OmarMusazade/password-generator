#include <iostream>
#include <string>
#include <openssl/rand.h>

using namespace std;

const string alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+";
const int length=20;
const int limit=71;

void Password();


int main()
{
	Password();	
}

void Password()
{
	unsigned char buf[length];
	string pass;
	while(pass.length()<length)
	{
		if(RAND_bytes(buf,sizeof(buf))!=1)
		{
			cerr<<"RNG error"<<endl;
		}
		for(int i=0;i<sizeof(buf) && pass.length()<length;i++)
		{
			if(buf[i]<=limit)
			{
				pass+=alphabet[buf[i]];
			}
		}
	}
	cout<<pass<<endl;
}


#include <iostream>
#include <string>
#include <openssl/rand.h>
#include <stdexcept>

using namespace std;

// characters
const string alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+";
// length of the password
const int length=20;
// limit of highest index for the buf, which will choose the characters from the alphabet
const int limit=alphabet.length()-1;

string Password();


int main()
{
	cout<<Password()<<endl;
}

string Password()
{
	unsigned char buf[length];
	string pass;
	while(pass.length()<length)
	{
		// RAND_bytes returns 1 on success, this checks correctness of RNG
		if(RAND_bytes(buf,sizeof(buf))!=1)
		{
			throw runtime_error("RNG failed");
		}
		for(size_t i=0;i<sizeof(buf) && pass.length()<length;i++)
		{
			if(buf[i]<=limit)
			{
				pass+=alphabet[buf[i]];
			}
		}
	}

	return pass;
}


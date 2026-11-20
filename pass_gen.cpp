#include <iostream>
#include <string>
#include <openssl/rand.h>
#include <stdexcept>
#include <vector>

using namespace std;

// characters
const string lower="abcdefghijklmnopqrstuvwxyz";
const string upper="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string num="0123456789";
const string sym="!@#$%^&*()-_=+";
const string alphabet=lower+upper+num+sym;
// length of the password
const int length=20;
// limit of highest index for the buf, which will choose the characters from the alphabet
const int limit=alphabet.length()-1;

string Shuffle(string pass);
string Password();


int main()
{
	try
	{
		cout<<Password()<<endl;
	}
	catch (const exception &e)
	{
		cerr<<"ERROR"<<endl;
		return 1;
	}
}

string Shuffle(string pass)
{
	string new_pass="";
	vector<unsigned char> buf(pass.length());
	while(!pass.empty())
	{
		if(RAND_bytes(buf.data(),buf.size())!=1)
		{
			throw(runtime_error("RNG failed"));
		}
		for(int i=0;i<buf.size() && !pass.empty();i++)
		{
			if(buf[i]<pass.length())
			{
				new_pass+=pass[buf[i]];
				pass.erase(buf[i],1);
			}
		}
	}
	return new_pass;
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
		for(int i=0;i<sizeof(buf);i++)
		{
			if(buf[i]<10)
			{
				pass+=lower[buf[i]];
				pass+=upper[buf[i]];
				pass+=num[buf[i]];
				pass+=sym[buf[i]];
				break;
			}

		}
		for(size_t i=0;i<sizeof(buf) && pass.length()<length;i++)
		{
			if(buf[i]<=limit)
			{
				pass+=alphabet[buf[i]];
			}
		}
	}
	return Shuffle(pass);
}


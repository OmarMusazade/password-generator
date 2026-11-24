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
// limit of highest index for the buf, which will choose the characters from the alphabet
const int limit=alphabet.length()-1;

// functions to generate password and randomly shuffle it
string Shuffle(string pass);
string Password(size_t length);


int main()
{
	// getting the length of the password from STDIN
	size_t length=0;
	cout<<"Enter the length of the password (between 4-128)"<<endl;
	if(!(cin>>length) || length<4 || length>128)
	{
		cerr<<"Error"<<endl;
		return 1;
	}
	try
	{
		cout<<Password(length)<<endl;
	}
	catch (const exception &e)
	{
		cerr<<"ERROR"<<e.what()<<endl;
		return 1;
	}
}

//Fisher-Yates shuffle to ensure each password does not start with same character class order
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
		for(size_t i=0;i<buf.size() && !pass.empty();i++)
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

string Password(size_t length)
{
	vector<unsigned char> buf(length);
	string pass;
	// ensuring each character class appears at least once 
	const string classes[4]={lower,upper,num,sym};
	size_t done=0;
	while(done<4)
	{
		if(RAND_bytes(buf.data(),buf.size())!=1)
		{
			throw runtime_error("RNG failed");
		}
		for(size_t i=0;i<buf.size() && done<4;i++)
		{
			if(buf[i]<classes[done].length())
			{
				pass+=classes[done][buf[i]];
				done++;	
			}
		}
	}
	while(pass.length()<length)
	{
		// RAND_bytes returns 1 on success, this checks correctness of RNG
		if(RAND_bytes(buf.data(), buf.size())!=1)
		{
			throw runtime_error("RNG failed");
		}

		for(size_t i=0;i<buf.size() && pass.length()<length;i++)
		{
			if(buf[i]<=limit)
			{
				pass+=alphabet[buf[i]];
			}
		}
	}
	return Shuffle(pass);
}


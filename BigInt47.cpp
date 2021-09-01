
/** Alexandre Schein
BigInt
**/

#include<string>
#include<vector>
#include<iomanip>
#include <time.h>
#include<algorithm>
#include <cstring>

#include <iostream>

using namespace std;


class BigInt
{

private:
	
	vector<char> storage;  //storage for char values
	
private:
	
	bool isNeg() {
		if ((int)storage.back() == 0) //testing whether (int) value of the char is 9
		{
			return false;  //0 is positive
		}
		else{
			return true; //it is negative
			}
		}
	
	vector<char>  tensComplement()
	 
	{ //returns the char vector
	
		int carryout; //carry variable to keep track of carry 1's
		
		vector<char>::iterator it = storage.begin();	//iterator begininng at beginning of storage
		
		while (it != storage.end()) 
		{
			*it = 9 - *it; 
			it++;
		}
		
		it = storage.begin(); //resetting the iterator
		*it += 1;  //updating 
		while (it != storage.end()) 
		{
			if (carryout == 1)
			 {
				*it = *it + 1;
				carryout = 0;
			}
			if (*it == 10) 
			{
				*it = 0;
				carryout = 1;
			}
			it++;
		}
		
		return storage;
	}
	
	void trim() 
	{
		
		while (storage.size() > 1 && storage[storage.size() - 2] == 9 && storage.back()==9) 
		{
			storage.pop_back(); //removing the extra sign bit 
		}
		
		while (storage.size() > 1 && storage[storage.size() - 2] == 0 && storage.back() ==0 ) 
		{
			storage.pop_back(); //removing the extra sign bit
		}
	}	
		

public:

	BigInt() { 							//default
	
		storage.push_back(0);		//default set to 0 + sign bit
		storage.push_back(0);
	}

	BigInt(int x) {			//overloaded consturctor passing in an int
	
		int positive = abs(x); 
		
		while (positive > 0) {
			
			char place = positive % 10;
			storage.push_back(place); 		//storing the char into storage
			positive /= 10; 							//traversing through the individual numbers in the int
		}
		
		if (x < 0) 
		{
			storage = tensComplement();	//10s complementing the number
			storage.push_back(9); //adding 9 for negative
		}
		else 
		{
			storage.push_back(0); //positive

		}
	}

	BigInt(string x) 					//overloaded string
	{								
		
		int i;
		
		for (i=x.length()-1; i>0; i--) 
		{
			storage.push_back(x[i] - '0'); //subtracing 0->48 in ascii 
		}
		if ((int)x[i] == 0) 
		{
			storage.push_back(0); //adding 0 
		}
		
		else if (x[i] == '-') 
		{
			tensComplement();
			storage.push_back(9); //addign 9
		}
		else {
			storage.push_back(x[i] - '0'); //-48 
			storage.push_back(0); //add 0 in front for positive
		}
		
	}

	void showStorage() {
		
		vector<char>::reverse_iterator rit; //reverse iterator

		for (rit = storage.rbegin(); rit != storage.rend(); rit++) 
		{
			cout << (int)*rit; 					//type casting pointer to int to display int value 
		}
		cout << endl; 
	}   
	
	friend ostream & operator<<(ostream & out, const BigInt & a)
	{		
		int count =1;
		int count_2 = 0;
		
		BigInt temp(a);
		//cout<<",";

		int n = temp.storage.size();

		int iter_count= 0;
		
		vector <char>::reverse_iterator rit; //using revere iterator for backwards
		
		if (temp.storage.size() > 1) {
			rit = temp.storage.rbegin() +1;
		}
		else {
			rit = temp.storage.rbegin();
		}
		
		if(temp.isNeg()){  //if number is neg
			out<<"-"; 
			temp.tensComplement();
		}		
		
		vector<int> chars;
		count = 1;
		for (rit; rit != temp.storage.rend(); rit++)
		{
			out<<(int)*rit;
			n--;
									
//			if(n%3 == 1 && rit!= temp.storage.rend()-1 && rit!=temp.storage.rbegin()+1)
//			{
//				//out<<(int)*rit;
//				out<<",";
//			}
//			
//			else if (n==4){ //if size equals 4
//				//out<<(int)*rit;
//				out<<",";
//			}
	
		}

		return out;
	}
	
	BigInt operator+ (BigInt x) { 
		
		int count =0;
		int carryout = 0;  //for carryout 1's
		
		BigInt first(*this);
				
		if (first.isNeg()) 
		{
			first.storage.push_back(9);  //add 9
		}
		else 
		{
			first.storage.push_back(0); //add 0
		}
		if (x.isNeg()){
			x.storage.push_back(9); // add 9 to 2nd
		}
		else 
		{
			x.storage.push_back(0); //add 0 to 2nd
		}
		
		vector<char>::iterator iter_1; //first iterator for first bigint
		
		vector<char>::iterator iter_2; //second iter for 2nd int
		
		
		if (first.storage.size() > x.storage.size()) //testing which numberis longer
		{
			while (first.storage.size() != x.storage.size()) 
			{
				if (x.isNeg()) 
				{
					x.storage.push_back(9);
				}
												//sign bit assigning
				else 
				{
					x.storage.push_back(0);

				}
			}
		}
		else if (first.storage.size() < x.storage.size()) 
		{ 
			while (first.storage.size() != x.storage.size()) 
			{
				if (first.isNeg()) {  
					first.storage.push_back(9);  

				}											//adding sign bits
				else {
					first.storage.push_back(0);

				}
			}
		}

		iter_1 = first.storage.begin();
		//restarting the iterators again
		iter_2  = x.storage.begin();
		
		while (iter_1 != first.storage.end())
		{
			if (carryout == 0)   //carryout DNE
			{
				*iter_1 = *iter_1 + *iter_2;
			}
			if (carryout == 1) 
			{
				*iter_1 = *iter_1 + *iter_2 + carryout;
				carryout = 0;
			}
			if (*iter_1 > 9) {
				carryout = 1; //carryout exists
				*iter_1 %= 10;
			}
			
			*iter_1++; //incrementing
			*iter_2++;
		}
		
		first.trim();
		
		return first;
	}


	BigInt operator+ (int x)   //adding regular int
	{
		BigInt added(x); //convert to bigint
		BigInt answer = *this + BigInt(x);
		return answer;//returning 
	}
	
	BigInt operator-(BigInt x) 
	{
		BigInt subtracted(x); //conver
		subtracted.tensComplement();
		BigInt answer= *this + subtracted; //adding the tens comp

		return answer;
	}

	BigInt operator-(int x)
	{
		BigInt subtracted(x);
		BigInt answer = *this - subtracted; //subtracting regular int converted
		return answer;
	}

	BigInt operator++(int dummy) //post increment operator
	{
		//BigInt temp(*this);
		*this = *this + 1;
		return *this;
	}
	
	BigInt operator++() //pre increment operator
	{
		*this = *this + 1 ;
		return *this;
	}

	BigInt operator--(int dummy) //post decrement operator
	{
		//BigInt temp(*this);
		*this = *this - 1; //subtracting 1 from the bigint
		return *this;
	}

	BigInt operator--() 		//pre-decrement 
	{
		*this = *this + -1;
		return *this;
	}

	bool operator > (BigInt right)   //GREATER THAN COMP
	{
		BigInt left(*this); 

		BigInt result = left - right; //if result goes in left direction, first is a negative
		if (result.isNeg()) 
		{
			return false;
		}
		else   //first successfully subtracted right and stayed positive
		{
			return true;
		}
	}


	bool operator < (BigInt right)  //less than compar
	{
		BigInt left(*this);
		
		BigInt result = left - right; 	//if result goes in left direction, first is a negative
		if (result.isNeg()) 
		{
			return true;
		}
		else {
			return false;
		}
	}

	bool operator == (BigInt right) //equals
	{
		BigInt left(*this);	//setting left to the current BigInt
		vector<char>::iterator iter_1; //iterators 
		iter_1 = left.storage.begin();
		vector<char>::iterator iter_2;
		iter_2= right.storage.begin();

		if (left.isNeg() && right.isNeg()==false) {  //if left is neg and right isnt
			iter_2++;
			return false;
		}
		if (right.isNeg() && left.isNeg()==false) { //vice versa
			iter_1++;
			return false;
		}
		else if (left-right==0){  //if 0
			return true;
		}
		else{
			return false; //otherwise false
		}
	}

	BigInt operator+=(int x) 
	{
		*this = *this + BigInt(x); //adding
		return *this;
	}

	BigInt operator-=(int x)  //subtracting
	{
		*this = *this - BigInt(x);
		return *this;
	}
	
	
	BigInt operator*(BigInt x) 
	{ 
		int count =0;
		
		BigInt temp(*this);
		BigInt result;
		BigInt result2;
		
		vector<char>::iterator it = x.storage.begin();
		
		int k = 0; //position in the string
		while(it != x.storage.end() && x.storage.size()>0)
		{
			for (int j = 0; j <= x.storage[k]-1; j = j + 1) 
			{
				result2 = result2 + temp;
			}
			
			temp.storage.insert(temp.storage.begin(),0);
			result = result + result2;
			result2 = 0;
			
			k++; 
			it++; //iterator moves through
		}
		return result;
	}

	BigInt operator*=(BigInt x) 
	{ 
	
		if(x < *this)
		{
			*this = *this *x;
		}
		else{
			*this = x * *this;
		}

		trim();
		return *this;
	}

};

int fact(int n) {			//int

	if (n > 1) {
		return n * fact(n - 1);
	}
	else {
		return 1;
	}
}


BigInt fact(BigInt n) {		//bigint 
		
	if (n>1){
		return n*fact(n-1);
	}
	else{
		return 1;
	}}




int main()
{
	

BigInt a;

cout << "\ntesting BigInt a:\t" << a << endl;

a.showStorage();

BigInt b(50);

cout << "\ntesting BigInt b(50):\t" << b << endl;

b.showStorage();

BigInt c(-37);

cout << "\ntesting BigInt c(-37):\t" << c << endl;

c.showStorage();

BigInt d("123456789012");

cout << "\ntesting BigInt d(\"123456789012\"):\t" << d << endl;

d.showStorage();

BigInt e("-2345");

cout << "\ntesting BigInt e(\"-2345\"):\t" << e <<endl;

e.showStorage();


// do the addition operator

BigInt sum = BigInt(10) + BigInt(20);

cout << "\ntesting sum = BigInt(10) + BigInt(20):\t"<< sum << endl;


// do the subtraction operator

BigInt diff = sum - BigInt(20);

cout << "\ntesting diff = sum - BigInt(20):\t"<< diff << endl;


// do the x++ operator

cout << sum++;

cout << "\ntesting sum++:\t"<< sum << endl;


// do the ++x operator

cout << ++sum;

cout << "\ntesting ++sum:\t"<< sum << endl;


// do the x-- operator

cout << sum--;

cout << "\ntesting sum--:\t"<< sum << endl;


// do the --x operator

cout << --sum;

cout << "\ntesting --sum:\t"<< sum << endl;


// do the < operator

BigInt left(24);

BigInt right(-37);

cout << "\ntesting left < right:\t";

cout << "The less of "<<left<<" and "<<right<<" is " << ((left < right)? left: right) << endl;


// do the == operator

cout << "\ntesting left == right:\t";

cout << left << " and " << right << ((left==right)?" are ":" are not ")<< "equal\n";


// do the > operator

cout << "\ntesting left > right:\t";

cout << "The greater of "<<left<<" and "<<right<<" is " << ((left > right)? left: right) <<endl;

// test the int Factorial function

cout << "\ntesting int factorial loop:";

for(int i = 0; i < 30; i++)

cout << "\nfact("<<i<<") = "<<fact(i);


cout << "\n\nLargest positive integer: "<<INT_MAX << endl;

long long huge = LLONG_MAX;

cout << "\nLargest positive long long: "<<huge;


getchar();


// test the BigInt Factorial function

cout << "\ntesting BigInt factorial loop:";

for(BigInt I = 0; I < BigInt(100); I+=7)

cout << "\n\nfact("<<I<<") = "<<fact(I);

getchar();


cout<< "\nHow far from the Earth to Pluto? ";

// 4.6 billion miles * 5280 feet per mile * 12 inches per foot

cout << BigInt("4600000000") * BigInt(5280) * BigInt(12) << " inches"<< endl;

cout<< "\nWhat is the size of the observable universe?"<<endl;

// 93 billion light years *

// 365 days per year *

// 24 hours per day *

// 3600 seconds per hour *

// 299,792,458 meters oer second *

// 1000 millimeters per meter

BigInt AcrossTheUniverse(1);

AcrossTheUniverse *= BigInt(93) * BigInt(100000000); // 93 * 1 billion light years

AcrossTheUniverse *= BigInt(365); // 365 days per year

AcrossTheUniverse *= BigInt("24"); // 24 hours per day

AcrossTheUniverse *= BigInt(3600); // 3600 seconds per hour

AcrossTheUniverse *= BigInt(299792458); // 299,792,459 meters per second

AcrossTheUniverse *= BigInt(1000); // 1000 millimeters per meter

cout << AcrossTheUniverse<<" millimeters"<<endl;


left = BigInt(-500000);

right = BigInt("-499999");

cout << endl;

BigInt fact99 = fact(BigInt(99));

BigInt fact98 = fact(BigInt(98));


BigInt diff1 = fact99 - fact98;

BigInt diff2 = fact98 - fact99;


cout << "\n\nfact99 = "<<fact99;

cout << "\n\nfact98 = "<<fact98;

cout << "\n\nfact99 - fact98 = "<< fact99 - fact98;

cout << "\n\nfact98 - fact99 = "<< fact98 - fact99;

cout << "\n\n(fact99 - fact98) + (fact98 - fact99) = "<<(fact99 - fact98) + (fact98 - fact99);


cout << endl<<endl;

if (left < right)

cout << left << " is less than "<<right;

else

cout << left << " is not less than " << right;


cout << endl<<endl;

if (left > right)

cout << left << " is greater than "<<right;

else

cout << left << " is not greater than " << right;

cout << endl<<endl;

if (left == right)

cout << left << " is equal to "<<right;

else

cout << left << " is not equal to " << right;

cout << endl;


getchar();

return 0;
}



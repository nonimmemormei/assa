#pragma comment(lib,"winmm.lib")
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
using namespace std;
double PCFreq = 0.0;
__int64 CounterStart = 0;

void error(int err);
bool error_float(float a);
int input_n();
void input_array(int *a, int n);
void check_array(int *a, int n);
void sort(int *a,int n);
void output(int *a, int n);
void StartCounter();
double GetCounter();



int main()
{ 


	int n;
	n=input_n();
	int *a=new int [n];
	input_array(a,n);
	StartCounter();
	check_array(a,n);
	cout << "Your time: " << GetCounter() << "mks" << endl;
	output(a,n);
	delete [] a;
	system("Pause");


}



void error(int err)
{
	switch(err)
	{
	case 0:
		cin.clear(); 
		char binput[5];
		cin >> binput;
		break;
	case 1:
		cerr << "n must be 0 < n < 127! Please, enter the correct n: " << endl; 
		error(0);
		break;
	case 2:
		cerr << "Element must be number -128 <= a[i] <= 127. Please enter the correct number: " << endl; 
		error(0);
		break;

	}
}
bool error_float(float f)
{
	float b=f-(int)f;
	if (b==0)
		return false;
	else return true;
}
int input_n()
{ 
	float f;
	int n;
	do
	{   
		cin.exceptions(cin.failbit);

		try
		{  
			cout << "Enter n: ";
			cin >> f;
			if ((error_float(f))||(f<=0) || (f>=127))
				cout <<  "n must be 0 < n < 127. Please, enter the correct n: " << endl;
		}

		catch(...)
		{
			error(1);
		}
	}
	while ((f<=0) || (f>=127)||(error_float(f)));
	return n=f;
}

void input_array(int *a, int n)
{
	float f;
	int i=0;
	cout << "Enter elements of array through space  "<< endl;
	while (i<n)
	{
		cin.exceptions(cin.failbit);

		try
		{
			cin >> f;
			if (error_float(f) || f<=-128|| f>=127)
				cout <<  "In position "<<i+1<<" must be number -128 <= a[i] <= 127. Please, enter correct number:  " ;
			else {
				a[i] = (int) f;
				i++;
			}
		}
		catch (...)
		{
			error(2);
		}
	}
}

void check_array(int *a, int n)
{

	int i = 0;
	while(a[i] <= a[i+1] && i < n-1)
	{
		i++;
	}

	if(i != n-1)
	{
		cout << "Array is not sorted! "<< endl;
		sort(a,n);
	}
	else
		cout << "Array already sorted! "<< endl;

}

void sort(int *a,int n)
{
	int x;
	int t=true;
	while(t)
	{
		t=false;
		for (int i=0; i<n-1; i++){
			if(a[i]>a[i+1]){
				x=a[i+1];
				a[i+1]=a[i];
				a[i]=x;
				t=true;
			}

		}
	}
}

void output(int *a, int n)
{
	cout << "Your array: "<< endl;
	for (int i=0; i<n;i++){
		cout<< a[i]<<" ";
		if((i+1)%15==0)
			cout<< endl;

	}
	cout<< endl;

}

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}
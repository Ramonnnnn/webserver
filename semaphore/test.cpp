#include "semaph.h"
#include <iostream>
#include <stdexcept>

using namespace advcpp;
using namespace std;

const int size = 4;
int nums[] = {1,2,3,4};




int main()
{
	// try
	// {
	// 	Mutex mutex1;
	// 	mutex1.Lock();

	// 	for(int i = 0; i < size; ++i)
	// 	{
	// 		++nums[i];
	// 	}

	// 	mutex1.Unlock();

	// 	bool isLocked = mutex1.Trylock(3);
	// 	if(isLocked)
	// 	{
	// 		cout << nums[0];
	// 		mutex1.Unlock();
	// 	}
	// }
	// catch(runtime_error& _error)
	// {
	// 	cout << _error.what() << '\n';
	// }
}
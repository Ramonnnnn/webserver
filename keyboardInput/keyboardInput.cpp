#include "keyboardInput.h"
#include <iostream>

namespace advcpp
{

using namespace std;

void KeyboardInput::Input(std::string& _request)
{
	cout << "Please insert http request:" << '\n';
	getline(std::cin, _request);
}

}

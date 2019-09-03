#include "webServer.h"
#include <stdexcept>

using namespace advcpp;
using namespace std;




int main()
{
	
	size_t numOfThreads = 10;
	WebServer webServer(numOfThreads);
	webServer.Start();
}
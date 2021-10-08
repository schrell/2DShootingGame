#define OLC_PGE_APPLICATION
#include "CSP.h"

using namespace std;

// Override base class with your custom functionality
int main()
{
	CSP demo;
	if (demo.Construct(SCREEN_WIDTH, SCREEN_HEIGHTS, 2, 2))
		demo.Start();
	return 0;
}
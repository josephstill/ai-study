#include "Map.h" 


int main()
{
	int retVal;
	Map* m;

	// This will change
	m = createMap(3);
	if (m)
	{
		retVal = 0;
	}
	else
	{
		retVal = -1;
	}
    return retVal;
}

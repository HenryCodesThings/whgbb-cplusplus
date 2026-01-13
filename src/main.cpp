#include "Level.h"

int main()
{
    // Run Level 1
    if (RunLevel1())
    {
        // Run Level 2
        RunLevel2();
    }
	else if (RunLevel1() == false)
    {
        RunLevel2();
    }

    return 0;
}

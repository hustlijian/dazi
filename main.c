#include "dazi.h"
#include "file.h"

int main(int argc, char *argv[])
{
	if (argc>1)
	{
		setFilename(argv[1]);
	}
	while (1) {
		Init();	
		Run();
		Quit();
	}
	
	return 0;
}
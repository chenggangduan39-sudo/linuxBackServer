#include "public.h"
int main()
{
	DirectoryScanner scanner;
	scanner.scanDir("/projects/back");
	scanner.printFileInfo();
	return 0;
}
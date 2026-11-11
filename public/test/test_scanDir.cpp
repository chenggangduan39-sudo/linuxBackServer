#include "public.h"
int main()
{
	DirectoryScanner scanner;
	scanner.scanDir("/projects/back/public", "*.h,*.cpp", 1, true);
	scanner.printFileInfo();
	return 0;
}
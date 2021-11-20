#include "minicrt.h"

int main(long argc, char *argv[])
{
	long i;
	FILE *fp;
	fp = fopen("test.txt", "w");
	{
		char *buf = "hello how are you  \n";
		long len = strlen(buf);
		// write "hello how are you" to text.txt
		fwrite(buf, 1, len, fp);
		write(0, "hey", 3);
		printf(" hello world\n");
		printf("%d  %s\n", len, buf);
	}
	fclose(fp);
	return 0;
}
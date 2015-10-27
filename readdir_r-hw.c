#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

/* see chapter4/readdir_r-v1.c for extra comments */

int main(int argc, char **argv)
{

	/* Always list the current directory */
	char *d_to_open = ".";

	DIR *dstream = opendir(d_to_open);
	if (dstream == NULL) {
		perror("opening directory failed");
		exit(2);
	}

	struct dirent d;
	struct dirent *result;


	for(;;) {

		int ret = readdir_r(dstream, &d, &result);

		/*Get name of current file in directory 
		 * and get stat values from it */
		char *path = d.d_name;
		struct stat buf;

		if(stat(path, &buf) != 0){
			perror("error getting stat of file.");
			exit(4);
		}

		if (ret != 0) {
			perror("readdir_r error");
			exit(3);
		}
		if (!result) {
			break;
		}
		
		/* If file is not a directory */
		if(d.d_type != DT_DIR)
		printf("mode: %o\t name: %s\n", buf.st_mode, d.d_name);
		
		/*if file is a directory, simpy add (Directory)
		 * to end of string */
		else
		printf("mode: %o\t name: %s (Directory)\n", buf.st_mode, d.d_name);

	}

	return 0;
}

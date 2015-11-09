#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>


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


	for (;;) {

		int ret = readdir_r(dstream, &d, &result);

		if (ret != 0) {
			perror("readdir_r error");
			exit(3);
		}
		if (!result) {
			break;
		}

		struct stat mystat;	/* must declare the struct itself, not just
										a pointer to it, so the memory gets 
										allocated for the whole struct */

		if ((stat(d.d_name, &mystat) == -1)) { /* but stat wants a pointer to
																the struct, so use & */
			perror("stat");
			exit(4);
		}

		char *dir = "";		/* variable dir points to an empty string */

		if (S_ISDIR(mystat.st_mode))  /* if it's a directory, change dir */
			dir = "(Directory)";      /* to point to the string "(Directory)" */
		
		//creates space for user id and group id structures
		//as well as buffer to get all info regarding each
		struct passwd usrn;
		struct passwd *usrnp;
		struct group grpn;
		struct group *grpnp;
		char buf[1024];

		//returns 0 if successful or no file with given userid
		//so any error value will result in statement being true
		if(getpwuid_r(mystat.st_uid, &usrn, buf, sizeof buf, &usrnp)){
			perror("getpwuid_r error");
			exit(5);
		}
		//returns 0 if successful or no file with given grpid
		//so any error value will result in statement being true
		if(getgrgid_r(mystat.st_gid, &grpn, buf, sizeof buf, &grpnp)){
			perror("getgrgid_r error");
			exit(6);
		}

		printf("user: %s\tgroupuser: %s\tmode: %llo\t, name: %s %s\n", usrn.pw_name, grpn.gr_name, (long long) mystat.st_mode,
				d.d_name, dir);
	}
	return 0;
}

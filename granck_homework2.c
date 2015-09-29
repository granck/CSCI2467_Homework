/*
 *
 * granck_homework2.c
 * By: Garrick Ranck
 * September 27, 2015
 *
 * The lseek function changes the current offset of the open file.
 * The append flag on an open file runs a check whenever a write is 
 * being performed and sets the offset to the end of the file.
 * Since this has no affect on the read command, we are free to use the lseek
 * to alter the offset and read anywhere from the file.
 * However, if we change the offset of the file and then immediately try to write
 * then our offset will be changed to reflect the end of the file instead of where 
 * we currently are.
 *
 * In this example, we open a file and perform a read and write from it.
 * Then we use lseek to alter the offset before a second read and then again
 * before a second write. What we will notice is that in both cases, the write always
 * changes the offset to the end of the file, so both buffers from read will be placed
 * there regardless of where we moved the offset prior.
 **/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

	if(argc != 2){
		printf("Wrong number of arguments\n");
		exit(8);
	}//end if
	
	int testFile = open(argv[1], O_APPEND | O_CREAT | O_RDWR );
	if(testFile == -1){
		perror("Open testFile failed");
		exit(1);
	}//end if

	ssize_t rret = 0;
	char buf[32];

	rret = read(testFile, buf, 32);
	if(rret == -1){
		perror("Error reading testFile");
		exit(2);
	}//end if


	ssize_t wret = 0;

	wret = write(testFile, &buf[0], 32);
	if(wret == -1){
		perror("Write to testFile error");
		exit(3);
	}//end if

	if(lseek(testFile, 64, SEEK_SET) == -1){
		perror("Lseek to new offset error");
		exit(4);
	}//end if

	rret = read(testFile, buf, 32);
	if(rret == -1){
		perror("Error reading testFile after offset change");
		exit(5);
	}//end if
	
	if(lseek(testFile, 0, SEEK_SET) == -1){
		perror("Lseek to new offset error");
		exit(4);
	}//end if

	wret = write(testFile, &buf[0], 32);
	if(wret == -1){
		perror("Error write to testFile after offset change");
		exit(6);
	}//end if
	
	int dcret = close(testFile);
	if(dcret == -1){
		perror("closing testFile");
		exit(7);
	}//end if

	exit(0);
}//end main

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <linux/limits.h>

void usage(int argc, char** argv);
void find_file(char* dir_name, char* file_to_find);

int main(int argc, char** argv)
{
	DIR* dp;
	struct dirent* dirp;

	// check if this application is being used properly
	usage(argc, argv);

	// check to see if provided directory is accessible
	errno = 0;
	dp = opendir(argv[1]);
	if(dp == NULL) {
		switch(errno) {
			case EACCES:
				fprintf(stderr, "Permission denied\n");
				break;
			case ENOENT:
				fprintf(stderr, "Directory does not exist\n");
				break;
			case ENOTDIR:
				fprintf(stderr, "'%s' is not a directory\n", argv[1]);
				break;	
		}
	}

	// print all files in the directory
	int cnt = 0;
	while((dirp = readdir(dp)) != NULL) {
		fprintf(stdout, "%d: %s", cnt, dirp->d_name);
		if(dirp->d_type == DT_DIR) {
			printf("\t directory");
		}
		printf("\n");
		cnt++;
	}

	// close the directory 
	closedir(dp);


	// now, recursivey traverse the directory structure to find the provided
	// file name
	char* file_to_find = argv[2];
	find_file(argv[1], file_to_find);

	return 0;
}


void usage(int argc, char** argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./%s directory_name file_to_find\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

void find_file(char* dir_name, char* file_to_find)
{
	// creating a directory pointer
	DIR *dp = opendir(dir_name);
	// creating a pointer to struct dirent
	struct dirent* dirp;
	// iterating over dp, reading a new element from it each time until the NULL pointer is read
	while ((dirp=readdir(dp))!= NULL) {
		// if type is a directory
		if (dirp->d_type==DT_DIR) {
			// first determine whether it is the parent or sub-directory
			if (strcmp(dirp->d_name, ".")==0||strcmp(dirp->d_name, "..")==0) {
					}
			// if not
			else {
				// creating a variable for the temporary directory
				char temp_dir[PATH_MAX];
				// storing the directory name passed into the function in temp_dir
				strcpy(temp_dir, dir_name);
				// creating a subdirectory variable to hold the name of the directory dropped into
				char sub_dir[PATH_MAX];
				// copying the name of the subdirectory into the variable
				strcpy(sub_dir, dirp->d_name);
				// adding a slash at the end of the original directory name
				strcat(temp_dir, "/");
				// adding the subdirectory name to the end of the temporary directory
				strcat(temp_dir, sub_dir);
				// recursively calling find file with this new directory sequence to further drop into subdirectories
				find_file(temp_dir, file_to_find);
			}
		}
		// if the name of the file pointed to by dirp is the same as file_to_find
		if (strcmp(dirp->d_name, file_to_find)==0) {
			// print to standard output that the file has been found in a location
			fprintf(stdout, "Found %s in %s\n", dirp->d_name, dir_name);
		}
	}
}


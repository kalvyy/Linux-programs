#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>

int pathTree(char * path){
	DIR * directory;
	struct dirent * file;

	if(!(directory = opendir(path))){
		printf("Failed to open %s diretory\n", path);
		return -1;
	}

	while(file = readdir(directory)){
		if(!strcmp(file->d_name, "..") || !strcmp(file->d_name, ".")){
			continue;
		}

		char nextPath[PATH_MAX];
		strcpy(nextPath, path);
		strcat(nextPath, file->d_name);
		printf("%s\n", nextPath);

		struct stat stats;
		if(stat(nextPath, &stats) < 0){
      printf("Stat error for %s file\n", nextPath);
			return -1;
		}

		if(S_ISDIR(stats.st_mode)){
			strcat(nextPath, "/");
			pathTree(nextPath);
		}
	}
}


int main(int argc, char ** argv){
	if(argc != 2){
		printf("Program require 1 parameter: path to directory\n");
		return -1;
	}

	pathTree(argv[1]);
}









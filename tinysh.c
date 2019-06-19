#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
int is_cmd(int cnt, char *cmd);
int is_valid(int cnt, char *cmd[]);
const char * mergeCmd(int cnt, char *cmd[]);
void __ls(int cnt, char *cmd[]);
// void __cd(int cnt, char *cmd[]);
void __pwd();
void __touch(int cnt, char *cmd[]);
int main(int argc, char *argv[]){
	if(argc == 1){
		printf("ERROR: Expected at least 1 argument\n");
		exit(0);
	}
	switch(is_cmd(argc,argv[1])){
		case 0:
			__ls(argc,argv);
			break;
		case 1:
			__pwd();
			break;
		// case 2:
		// 	__cd(argc,argv);
		// 	break;
		case 3:
			__touch(argc,argv);
			break;
		default:
			printf("ERROR: Invalid command: %s\n",argv[1]);
			exit(0);
			break;
	}
	exit(0);
}

/**
 * this function controls the comming argument
 * if its valid command
 * @param cnt argument count
 * @param cmd the entered argument
 * $return what command to go in switch-case part
 */
int is_cmd(int cnt, char *cmd){
	char arr[5][6] = {"ls","pwd","cd","touch"};
	int sr=-1;
	for(int i = 0; i < sizeof(arr); i++)
		if(strcmp(arr[i],cmd)==0){ sr = i; break; }

	return sr;
}

/**
 * this function checks 
 * if entered command is valid for combination of ls command
 * @param cnt argument count
 * @param cmd the entered argument
 * $return 1 if its valid
 */
int is_valid(int cnt, char *cmd[]){
	char arr[6][4] = {"-l","-a","-la","-al"};
	int sr = 0;
	for(int i = 2; i < cnt; i++)
		for(int j = 0; j < sizeof(arr); j++)
			if(strcmp(arr[j],cmd[i])==0){ sr = 1; break; }

	return sr;
}

/**
 * this function merges argument if needed
 * @param cnt argument count
 * @param cmd the entered argument
 * $return merged command line
 */
const char * mergeCmd(int cnt, char *cmd[]){
	int v = 0;
	char *str = (char *)malloc(v);
	for(int i = 1; i <= cnt - 1; i++){
		str = (char *)realloc(str, (v + strlen(cmd[i])));
		strcat(str, cmd[i]);
		strcat(str, " ");
	}
	return str;
}

/**
 * listing function for given directory
 * @param cnt argument count
 * @param cmd the entered argument
 */
void __ls(int cnt, char *cmd[]){
	DIR *dp;
	struct dirent *dirp;
	char buf[MAXPATHLEN];
	if(cnt >= 3){
		if((is_valid(cnt,cmd) == 0)){
			printf("ERROR: Invalid parameter\n");
			exit(0);
		}
		const char * str = mergeCmd(cnt,cmd);
		system(str);
		exit(0);
	}
	if((dp = opendir(cmd[1])) == NULL ){
		dp = opendir(".");
	}
	while((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);
	closedir(dp);
}

/**
 * directory changing function for given directory
 * @param cnt argument count
 * @param cmd the entered argument
 */
// void __cd(int cnt, char *cmd[]){
// 	if (cnt != 3){
// 		fprintf(stderr, "%s: need a directory!\n", cmd[1]);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (chdir(cmd[2]) == -1){
// 		fprintf(stderr, "%s: unable to chdir to %s\n", cmd[1],cmd[2]);
// 		exit(EXIT_FAILURE);
// 	}
// 	printf("CWD is now: %s\n", getcwd(cwd, sizeof(cwd)));
// 	exit(EXIT_SUCCESS);
// }

/**
 * gives current working directory
 */
void __pwd(){
	char cwd[PATH_MAX];
	if(getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s", cwd);
	else
		perror("getcwd() error");
}

/**
 * this function creates file in current directory
 * checks before creating file
 * if file exixst deletes the maching file names in argument
 * runs as much as cnt variable
 * @param cnt argument count
 * @param cmd the entered argument
 */
void __touch(int cnt, char *cmd[]){
	char *buffer;
	char command[512];
	char file_name[25];
	for(int i = 2; i < cnt; i++)
		remove(cmd[i]);

	for(int i = 2; i < cnt; i++){
		buffer = malloc(strlen(cmd[i]) + 5);
		strcpy(buffer,cmd[i]);
		sprintf(command,"touch %s\0",buffer);
		system(command);
		free(buffer);
	}
	printf("File(s) successfully created.");
}

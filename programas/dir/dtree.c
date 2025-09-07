/* dtree.c - print directory tree under argv[1]. */
/* Does an indented directory tree listing. */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <stdlib.h>
#include <string.h>

void do_a_directory(char * pathname, int level);

int main(int argc, char * argv[])
{
	/* Usage check */
	if( argc < 2)
	{
		fprintf(stderr,"Usage: dtree directory\n");
		exit(1);
	}
	do_a_directory(argv[1], 0);

	return 0;
}

void do_a_directory(char * pathname, int level)
{
	DIR * directory;                /* Like a FILE *, but for directories. */
	struct dirent * entry;          /* Only used as a pointer - see dirent.h */
	char * newname;                 /* Name of directory at next level. */
	struct stat statbuf;            /* So we can check which files are directories. */
	long where;                     /* We will leave this directory and come */
	/* back - need to remember where we were. */
	int retval, i;
	/* Print this directory name, properly indented. */
	for( i = 0; i < level; i++)
		printf("   ");
	printf("%s\n", pathname);

	/* Open a directory for directory reads. */
	directory = opendir(pathname);
	if(directory == NULL)
	{
		fprintf(stderr, "Cannot open %s\n", pathname);
		perror("Reason");
		return;
	}
	while( ( entry = readdir(directory)) != NULL)
	{
		/* Skip if . or .. */
		if( strcmp(entry -> d_name, ".") == 0 ||
				  strcmp(entry -> d_name, "..") == 0 )
			continue;
		/* Manufacture pathname of entry relative to where we started. */
		newname = (char *) malloc(MAXPATHLEN);
		strcpy(newname, pathname);
		strcat(newname, "/");
		strcat(newname, entry -> d_name);
		/* stat it to see if it is a directory. */
		retval = stat(newname, &statbuf);
		if (retval == 0 &&  ( statbuf.st_mode & S_IFDIR))
		{
			/* If it is, close current directory, do the lower one recursively */
			/* and on return reopen the current directory, remembering to */
			/* get back to where we were. */
			where = telldir(directory);
			closedir(directory);
			do_a_directory(newname, level + 1);
			directory = opendir(pathname);
			if(directory == NULL)
			{
				fprintf(stderr, "Cannot open %s\n", pathname);
				return;
			}
			seekdir(directory, where);
		}
		free(newname);
	}
	closedir(directory);
}

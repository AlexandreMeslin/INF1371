#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main (int argc, char *argv[])
{
	DIR *dirp;
	struct dirent *dp;
	struct stat entryInfo;
	char pathName[PATH_MAX];

	if (argc == 1)
	{
		printf ("Uso: %s <diretório>\n", argv[0]);
		return (-2);
	}

	if ((dirp = opendir(argv[1])) == NULL)
	{
		printf ("Erro na abertura do diretório %s\n", argv[1]);
		exit (-1);
	}

	puts ("INODE\tFilename");
	while ((dp = readdir(dirp)) != NULL)
	{
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) continue;
		printf ("%d\t%-20s\t", (int)dp->d_ino, dp->d_name);

		strcpy (pathName, argv[1]);
		strcat (pathName, "/");
		strcat (pathName, dp->d_name);
		if (lstat (pathName, &entryInfo) == 0)
		{
			if (S_ISDIR(entryInfo.st_mode)) puts ("diretório");
			else if (S_ISLNK(entryInfo.st_mode)) puts ("link simbólico");
			else if (S_ISREG(entryInfo.st_mode)) puts ("arquivo");
			else puts ("não sei");
		}
	}

	closedir (dirp);
	return 0;
}

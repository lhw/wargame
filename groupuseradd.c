#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int 
main(int argc, char **argv)
{
	uid_t ruid, euid, suid;
	gid_t rgid, egid, sgid;


	/* we advanced a level */
   if(rgid != egid) {

		getresuid(&ruid, &euid, &suid);
		getresgid(&rgid, &egid, &sgid);

		/* check if we already joined the group */
		int ngroups = 20; /* maximal size of array */
		struct passwd *pw;
		gid_t *groups;
		struct group *gr;

		/* allocate memory for group structure */
		groups = malloc(ngroups * sizeof(gid_t));
		if(NULL == groups)
			return EXIT_FAILURE;

		/* get entry from /etc/passwd */
		pw = getpwuid(ruid);
		if(NULL == pw) {
			free(groups);
			return EXIT_FAILURE;
		}

		/* get entry from /etc/passwd */
		if(-1 == getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups)) {
			free(groups);
			return EXIT_FAILURE;
		}

      /* iterate and check for membership */
      int i;
      for(i = 0; i < ngroups; i++) {
         gr = getgrgid(groups[i]);
         if(NULL != gr && gr->gr_gid == egid) {
            /* we are already on this group */
            free(groups);
            fprintf(stderr, "you already submitted this level ;)\n");
            return EXIT_SUCCESS;
         }
      }

		/* since we are not in this group at the moment, join it */
		fprintf(stderr, "congratz, you made it :)\n");

		FILE *fh = tmpfile();
		if(NULL == fh) {
			fprintf(stderr, "could not open groupfile\n");
			return EXIT_FAILURE;
		}

#define _GNU_SOURCE
		while(NULL != (gr = getgrent()))
			if(gr->gr_gid == egid) {
				/* add user to the group first */

				/* get number of members */
				int j = 0;
				while(gr->gr_mem[j++]);

				/* new bigger buffer to fit new member in */
				char **new = malloc((j + 1) * sizeof(char*));
				memcpy(new, gr->gr_mem, j - 1);
				new[j - 1] = pw->pw_name;
				new[j] = NULL;
				gr->gr_mem = new;

				/* finally write the modified entry */
				putgrent(gr, fh);
				free(new);
			} else
				/* write normal unchanged entry */
				putgrent(gr, fh);
		free(groups);

		/* write back to real group file */
		char buf[4048];

		long len = ftell(fh);
		rewind(fh);

		fread(&buf, 4048, 1, fh);
		FILE *grpfile = fopen("/etc/group", "w");
		fwrite(&buf, len, 1, grpfile);
		fclose(grpfile);
		fclose(fh);
   } else {
      /* actually the user did not succeed with his exploit */
      fprintf(stderr, "nice try bro\n");
   }


	return EXIT_SUCCESS;
}

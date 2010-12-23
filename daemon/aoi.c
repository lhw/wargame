#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>
#include <err.h>
#include <pwd.h>

#ifndef __OpenBSD__
#include <getopt.h>
#endif
     
#define CMD_GAME	1
#define CMD_HELP	2
#define CMD_LIST	3
#define CMD_VIEW	4
#define CMD_NONE	0

int port = 5000;
char *chrootdir = "/tmp/aoi";
char *filesdir = ".";
char *user = "nobody";
char *passfile = "pass";

char arg[5]; /* for the exploit; assumption: command + \0 = 5 chars */

static const struct cmd {
	const char *cmd;
	int code;
} cmds[] = {
	{ "help",	CMD_HELP },
	{ "list",	CMD_LIST },
	{ "view",	CMD_VIEW }
};

void
usage(void)
{
	extern char *__progname;
	fprintf(stderr, "usage: %s [-dh] [-c chroot_dir] [-f files_dir] [-p port]\n",
		__progname);
	exit(1);
}

int
whatcmd(char *cmd)
{
	int i;
	for (i=0; i < sizeof(cmds) / sizeof(cmds[0]); i++)
		if (strncmp(cmds[i].cmd, cmd, 4) == 0)
			return cmds[i].code;
	return CMD_NONE;
}

void
dolist(int c)
{
	DIR *dirp;
	struct dirent *dp;
	char name[1024];
	if ((dirp = opendir(filesdir)) == NULL)
		err(1, "opendir");
	while ((dp = readdir(dirp)) != NULL) {
		snprintf(name, sizeof(name), "%s\n", dp->d_name);
		send(c, name, strlen(name), 0);
	}
}

void
doview(int c, char *buf)
{
	FILE *fp;
	char *bufp;
	char file[1024];
	char line[1024];
	
	/* XXX: crappy code, definetly needs rewrite */
	strsep(&buf, " ");
	bufp = strsep(&buf, " ");
	if ((bufp == "\0") || (bufp == NULL)) {
		char *msg = "file missing.\nusage: view file\n";
		send(c, msg, strlen(msg), 0);
		return;
	}
	snprintf(file, sizeof(file), "%s%s", filesdir, bufp);

	if (strstr(file, passfile)) {
		char *msg = "permission denied\n";
		send(c, msg, strlen(msg), 0);
		return;
	}
	if ((fp = fopen(file, "r")) == NULL) {
		/* err(1, "fopen"); */
		char *msg = "file not found\n";
		send(c, msg, strlen(msg), 0);
		return;
	}
	while (fgets(line, sizeof(line), fp))
		send(c, line, strlen(line), 0);
	fclose(fp);
}

void
dohelp(int c, char *buf)
{
	char *bufp;
	
	/* XXX: crappy code, see also doview() */
	strsep(&buf, " ");
	bufp = strsep(&buf, " ");
	if ((bufp == "\0") || (bufp == NULL)) {
		char *msg = "available commands: game help list view\n"
			"for further information type help command\n";
		send(c, msg, strlen(msg), 0);
	} else {
		/* security problem: because we assume help gets
		   an argument that is always 4 characters, an
		   attacker can easily exploit this */
		strcpy(arg, bufp);
		if (strncmp("list", arg, 4) == 0) {
			char *msg = "usage: list\nlists all available files\n";
			send(c, msg, strlen(msg), 0);
		} else if (strncmp("view", arg, 4) == 0) {
			char *msg = "usage: view file\nshows the content of the file\n";
			send(c, msg, strlen(msg), 0);
		} else if (strncmp("game", arg, 4) == 0) {
			char msg[30];
			sprintf(msg, "hint: address is %p\n", arg);
			send(c, msg, strlen(msg), 0);
		} else {
			char *msg = "unknown command.\navailable commands are: help game list view";
			send(c, msg, strlen(msg), 0);
		}
	}
}

int
handlecommand(int c, char *buf)
{
	char *msg = "unknown command\n";
	switch(whatcmd(buf)) {
	case CMD_LIST:
		dolist(c);
		break;
	case CMD_VIEW:
		doview(c, buf);
		break;
	case CMD_HELP:
		dohelp(c, buf);
		break;
	case CMD_NONE:
		send(c, msg, strlen(msg), 0);
		break;
	}
}

int
main(int argc, char *argv[])
{
	int ch, daemon = 0, s;
	struct passwd *pw;
	struct sockaddr_in sin;
	pid_t pid;

	while ((ch = getopt(argc, argv, "c:df:hp:u:")) != -1) {
		switch (ch) {
		case 'c':
			chrootdir = optarg;
			break;
		case 'd':
			daemon = 1;
			break;
		case 'f':
			filesdir = optarg;
			break;
		case 'p':
			port = atoi(optarg);
			break;
		case 'u':
			user = optarg;
			break;
		case '?':
		case 'h':
			usage();
			break;
		}
	}

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err(1, "socket");

	memset(&sin, 0, sizeof(sin));
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		err(1, "bind");
	if (listen(s, 5) < 0)
		err(1, "listen");

	if ((pw = getpwnam(user)) == NULL)
		err(1, "getpwnam");

	if (chroot(chrootdir) < 0)
		err(1, "chroot");
	if (chdir("/") < 0)
		err(1, "chdir");

	if(setgroups(1, &pw->pw_gid) ||
	   setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) ||
           setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid))
		err(1, "can't drop privileges");

	endpwent();

	if (daemon) {
		switch (pid = fork()) {
		case -1:
			err(1, "cannot fork");
		case 0:
			break;
		default:
			printf("pid: %d\n", pid);
			exit(0);
		}
	}

	for (;;) {
		int c;
		ssize_t n;
		char buf[1024];
		struct sockaddr_in cin;
		socklen_t len = sizeof(cin);

		if ((c = accept(s, (struct sockaddr *)&cin, &len)) < 0)
			err(1, "accept");
		pid = fork();
		if (pid < 0)
			err(1, "fork");
		if (pid = 0)
			continue;
		
		while ((n = recv(c, buf, sizeof(buf), 0)) > 0) {
			if (n > 0)
				buf[n-1] = '\0';
			handlecommand(c, buf);
			memset(buf, 0, sizeof(buf));
		}
		//return;
	}
}

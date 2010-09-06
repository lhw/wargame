#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>
#include <err.h>
     
#define CMD_GAME	1
#define CMD_HELP	2
#define CMD_LIST	3
#define CMD_VIEW	4
#define CMD_NONE	0

int port = 5000;
char *dir = "./pics/";

static const struct cmd {
	const char *cmd;
	int code;
} cmds[] = {
	{ "game",	CMD_GAME },
	{ "help",	CMD_HELP },
	{ "list",	CMD_LIST },
	{ "view",	CMD_VIEW }
};

void
usage(void)
{
	extern char *__progname;
	fprintf(stderr, "usage: %s [-h] [-d dir] [-p port]\n",
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
	if ((dirp = opendir(dir)) == NULL)
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
	snprintf(file, sizeof(file), "%s%s", dir, bufp);
	
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
	char arg[5]; /* assumption: command + \0 = 5 chars */
	
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
			char *msg = "usage: game\nwanna play a nice game? ;)\n";
			send(c, msg, strlen(msg), 0);
		} else {
			char *msg = "unknown command.\navailable commands are: game list view";
			send(c, msg, strlen(msg), 0);
		}
	}
}

void
dogame(int c)
{
	int n;
	char buf[256];
	
	char *msg = "Greetings, Professor Falken. Shall we play a game?\n";
	send(c, msg, strlen(msg), 0);
	
	if ((n = recv(c, buf, 256, 0)) < 0) {
		close(c);
		return;
	}
	/* just for obscurity */
	if (n > 5) {
		char *msg2 = "exception: exiting.\n";
		send(c, msg2, strlen(msg2), 0);
		close(c);
		return;
	}

	char *msg3 = "I'm not interested any longer.\nGoodbye\n";
	send(c, msg3, strlen(msg3), 0);
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
	case CMD_GAME:
		dogame(c);
		break;
	case CMD_NONE:
		send(c, msg, strlen(msg), 0);
		break;
	}
}

int
main(int argc, char *argv[])
{
	int ch, s;
	struct sockaddr_in sin;

	while ((ch = getopt(argc, argv, "d:hp:")) != -1) {
		switch (ch) {
		case 'd':
			dir = optarg;
			break;
		case 'p':
			port = atoi(optarg);
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

	for (;;) {
		int c;
		ssize_t n;
		char buf[1024];
		struct sockaddr_in cin;
		socklen_t len = sizeof(cin);

		if ((c = accept(s, (struct sockaddr *)&cin, &len)) < 0)
			err(1, "accept");
		
		while ((n = recv(c, buf, sizeof(buf), 0)) > 0) {
			if (n > 0)
				buf[n-1] = '\0';
			handlecommand(c, buf);
			memset(buf, 0, sizeof(buf));
		}
	}
}

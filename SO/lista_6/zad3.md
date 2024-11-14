### Właścicielem pliku programu su(1) jest «root», a plik ma ustawiony bit «set-uid». Jaką tożsamość będzie miał na początku proces wykonujący «su», jeśli przed execve(2) było euid=1000?
euid=0, ruid=1000, suid=0,
ponieważ plik ma ustawiony bit set-uid, tożsamość procesu zmienia się na tożsamość właściciela pliku, czyli roota

### Zreferuj działanie uproszczonej wersji programu su1 zakładając, że wszystkie wywołania systemowe kończą się bez błędów, a użytkownik zdołał się uwierzytelnić. Skoncentruj się na funkcjach czytających bazę danych użytkowników, odczytujących i sprawdzających hasło, oraz zmieniających tożsamość procesu.

```C
/* See LICENSE file for copyright and license details. */
#include <sys/types.h>

#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "passwd.h"
#include "util.h"

extern char **environ;

static int lflag = 0;
static int pflag = 0;

static void
usage(void)
{
	eprintf("usage: %s [-lp] [username]\n", argv0);
}

int
main(int argc, char *argv[])
{
	char *usr, *pass;
	char *shell, *envshell, *term;
	struct passwd *pw;
	char *newargv[3];
	uid_t uid;

	ARGBEGIN {
	case 'l':
		lflag = 1;
		break;
	case 'p':
		pflag = 1;
		break;
	default:
		usage();
	} ARGEND;

	if (argc > 1)
		usage();
	usr = argc > 0 ? argv[0] : "root";

	errno = 0;
	pw = getpwnam(usr); // get password file entry
	if (!pw) {
		if (errno)
			eprintf("getpwnam: %s:", usr);
		else
			eprintf("who are you?\n");
	}

	uid = getuid();
	if (uid) {
		pass = getpass("Password: "); // taki readline tyle że bez echo
		if (!pass)
			eprintf("getpass:");
		if (pw_check(pw, pass) <= 0) // uwierzytelnienie
			exit(1);
	}

	if (initgroups(usr, pw->pw_gid) < 0) // dodanie do grupy
		eprintf("initgroups:"); 
	if (setgid(pw->pw_gid) < 0) // ustawienie gid
		eprintf("setgid:");
	if (setuid(pw->pw_uid) < 0) // ustawienie uid
		eprintf("setuid:");

	shell = pw->pw_shell[0] == '\0' ? "/bin/sh" : pw->pw_shell;
	if (lflag) {
		term = getenv("TERM");
		clearenv();
		setenv("HOME", pw->pw_dir, 1);
		setenv("SHELL", shell, 1);
		setenv("USER", pw->pw_name, 1);
		setenv("LOGNAME", pw->pw_name, 1);
		setenv("TERM", term ? term : "linux", 1);
		if (chdir(pw->pw_dir) < 0)
			eprintf("chdir %s:", pw->pw_dir);
		newargv[0] = shell;
		newargv[1] = "-l";
		newargv[2] = NULL;
	} else {
		if (pflag) {
			envshell = getenv("SHELL");
			if (envshell && envshell[0] != '\0')
				shell = envshell;
		} else {
			setenv("HOME", pw->pw_dir, 1);
			setenv("SHELL", shell, 1);
			if (strcmp(pw->pw_name, "root") != 0) {
				setenv("USER", pw->pw_name, 1);
				setenv("LOGNAME", pw->pw_name, 1);
			}
		}
		newargv[0] = shell;
		newargv[1] = NULL;
	}
	execve(shell, newargv, environ);
	weprintf("execve %s:", shell);
	return (errno == ENOENT) ? 127 : 126;
}


char *getpass(const char *prompt)
{
	int fd;
	struct termios s, t;
	ssize_t l;
	static char password[128];

	if ((fd = open("/dev/tty", O_RDONLY|O_NOCTTY)) < 0) fd = 0;

	tcgetattr(fd, &t);
	s = t;
	t.c_lflag &= ~(ECHO|ISIG);
	t.c_lflag |= ICANON;
	t.c_iflag &= ~(INLCR|IGNCR);
	t.c_iflag |= ICRNL;
	tcsetattr(fd, TCSAFLUSH, &t);
	tcdrain(fd);

	fputs(prompt, stderr);
	fflush(stderr);

	l = read(fd, password, sizeof password);
	if (l >= 0) {
		if (l > 0 && password[l-1] == '\n') l--;
		password[l] = 0;
	}

	tcsetattr(fd, TCSAFLUSH, &s);

	if (fd > 2) close(fd);

	return password;
}

struct passwd *getpwnam(const char *name)
{
	struct passwd *pw;
	setpwent(); // idz na początek pliku
	while ((pw=getpwent()) && strcmp(pw->pw_name, name));
	endpwent(); // zamknij plik
	return pw;
}

struct passwd {
    char   *pw_name;       /* username */
    char   *pw_passwd;     /* user password */
    uid_t   pw_uid;        /* user ID */
    gid_t   pw_gid;        /* group ID */
    char   *pw_gecos;      /* user information */
    char   *pw_dir;        /* home directory */
    char   *pw_shell;      /* shell program */
};

int pw_check(const struct passwd *pw, const char *pass)
{
	char *cryptpass, *p;
	struct spwd *spw;

	p = pw->pw_passwd;
	if (p[0] == '!' || p[0] == '*') { // jeśli hasło jest zablokowane??
		weprintf("denied\n");
		return -1;
	}

	if (pw->pw_passwd[0] == '\0') {  // jeśli nie ma hasła
		if (pass[0] == '\0') 
			return 1;
		weprintf("incorrect password\n");
		return 0;
	}

	if (pw->pw_passwd[0] == 'x' && pw->pw_passwd[1] == '\0') {
        // jeśli hasło jest w pliku /etc/shadow
		errno = 0;
		spw = getspnam(pw->pw_name); // get shadow password file entry
		if (!spw) {
			if (errno)
				weprintf("getspnam: %s:", pw->pw_name);
			else
				weprintf("who are you?\n");
			return -1;
		}
		p = spw->sp_pwdp; // hasło z pliku shadow
		if (p[0] == '!' || p[0] == '*') { // jeśli hasło jest zablokowane??
			weprintf("denied\n");
			return -1;
		}
	}

	cryptpass = crypt(pass, p); // zaszyfruj hasło
	if (!cryptpass) {
		weprintf("crypt:");
		return -1;
	}
	if (strcmp(cryptpass, p) != 0) {
		weprintf("incorrect password\n");
		return 0;
	}
	return 1;
}
```
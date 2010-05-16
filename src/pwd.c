#include <pwd.h>
#include <stdlib.h>
#include <windows.h>

static struct passwd pwd;
static char* home_dir = ".";
static char* login_shell = "cmd";

/* FIXME stub to just make it compile */
/* Close the password-file stream.  */
void endpwent(void) {
}

/* FIXME stub to just make it compile */
/* Search for an entry with a matching username.  */
struct passwd *getpwnam(const char *name) {
	return 0;
}

char *getlogin() {
	static char name[256];
	DWORD max_len = 256;
	GetUserName(name, &max_len);
	return name;
}

struct passwd *getpwuid(int user_id) {
	pwd.pw_name = getlogin();
	pwd.pw_dir = home_dir;
	pwd.pw_shell = login_shell;
	pwd.pw_uid = 0;
	return &pwd;
}


#ifndef _GRP_H_
#define _GRP_H_

typedef unsigned long gid_t;

struct group {
	char *gr_name;			/* the name of the group	*/
	gid_t gr_gid;			/* the numerical group ID	*/
	char **gr_mem;			/* null-terminated vector of pointers*/
					/*   to the individual member names*/
	char *gr_passwd;		/* group password; returns "*" always */
	long reserved[19];
};

#endif	/* _GRP_H_ */

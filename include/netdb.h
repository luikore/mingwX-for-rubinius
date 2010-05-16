#ifndef _NETDB_H
#define _NETDB_H

// from ws2tcpip.h
// including ws2tcpip.h may cause a bunch of problem

/* getnameinfo constants */ 
#define NI_MAXHOST	1025
#define NI_MAXSERV	32

#define NI_NOFQDN 	0x01
#define NI_NUMERICHOST	0x02
#define NI_NAMEREQD	0x04
#define NI_NUMERICSERV	0x08
#define NI_DGRAM	0x10

#ifndef SOCKLEN_T_DEFINED
#define SOCKLEN_T_DEFINED
typedef int socklen_t;
#endif

#ifndef _WINSOCK2_H

struct sockaddr {
	unsigned short sa_family;
	char	sa_data[14];
};

struct  servent {
	char	*s_name;
	char	**s_aliases;
	short	s_port;
	char	*s_proto;
};

#endif

#ifndef _WS2TCPIP_H

struct addrinfo {
	int     ai_flags;
	int     ai_family;
	int     ai_socktype;
	int     ai_protocol;
	size_t  ai_addrlen;
	char   *ai_canonname;
	struct sockaddr  *ai_addr;
	struct addrinfo  *ai_next;
};

#endif

#endif // _NETDB_H

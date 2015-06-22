/*#include  <netinet/in.h>*/

IPv4 address structure

struct in_addr {
	in_addr_t  s_addr;
}

struct sockaddr_in {
	uint8_t    	sin_len;
	sa_family_t	sin_family;
	in_port_t	sin_port;
	struct in_addr	sin_addr;
	char	sin_zero[8];
};

generic socket address struct : sockaddr   /*include <sys/socket.h>*/
struct sockaddr {
	uint8_t		sa_len;
	sa_family_t	sa_family;
	char		sa_data[14];
};



IPv6  socket address structure  sockaddr_in6

struct in6_addr {
	unit8_t s6_addr[16];
};

#define  SIN6_LEN

struct sockaddr_in6 {
	uint8_t		sin6_len;
	sa_family_t	sin6_family;
	in_port_t	sin6_port;
	uint32_t	sin6_flowinfo;
	struct in6_addr sin6_addr;
	uint32_t	sin6_scope_id;
};

struct sockaddr_storage {
	uint8_t		ss_len;
	sa_family_t	ss_family;
	
	
};



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
#ifndef PROTO_H
#define PROTO_H

/****************/
/*	srcs/	*/
/****************/
/*ft_general.c*/
void	launch_server(void);
/*libft.c*/
int	get_next_line(FILE *fd, char **line);
char	*ft_itoa(int n);

/************************/
/*	srcs/network/	*/
/************************/
/*ft_general_network.c*/
int	init_server(void);
int	sendfile_net(const char *path, const char *filename, SOCKET socket);
int	send_net(SOCKET socket, const char *buffer);
char	*recv_net(SOCKET socket);
/*ft_server_core.c*/
void	server_core(SOCKET local_sock);

#endif

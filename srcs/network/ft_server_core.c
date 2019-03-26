#include "TRON_Arcade_HL.h"

void	server_core(SOCKET local_sock)
{
	SOCKADDR_IN client_in = {0};
	unsigned int client_size = sizeof(client_in);
	char get[] = "GET Host List";
	//char post[] = "POST Hostname";
	fd_set readfs;
	SOCKET client_sock = 0;
	int fd_max;
	char *buffer = NULL;
	
	while (1)
	{
		FD_ZERO(&readfs);
		FD_SET(local_sock, &readfs);
		if (client_sock > 0)
			FD_SET(client_sock, &readfs);

		fd_max = ((client_sock > local_sock) ? client_sock : local_sock);
		select(fd_max + 1, &readfs, NULL, NULL, NULL);

		if (FD_ISSET(local_sock, &readfs))
		{
			client_sock = accept(local_sock, (SOCKADDR *)&client_in, &client_size);
			printf("New client connected\n");
		}
		else if (FD_ISSET(client_sock, &readfs))
		{
			buffer = recv_net(client_sock);
			if (strcmp(get, buffer) == 0)
			{
				sendfile_net("srcs/network/", ".host_list.tron", client_sock);
				close(client_sock);
				client_sock = 0;
				break;
			}
			printf("get != buffer\n");
			close(client_sock);
			break;
		}
	}
}

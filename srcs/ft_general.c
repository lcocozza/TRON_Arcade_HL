#include "TRON_Arcade_HL.h"

void	launch_server(void)
{
	SOCKET local_sock;

	local_sock = init_server();
	printf("Server start\n");
	server_core(local_sock);
	close(local_sock);
}

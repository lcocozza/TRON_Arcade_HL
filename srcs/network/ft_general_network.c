#include "TRON_Arcade_HL.h"

int	init_server(void)
{
	SOCKADDR_IN local_in = {0};
	SOCKET local_sock;

	if ((local_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return -1;
	
	local_in.sin_addr.s_addr = htonl(INADDR_ANY);
	local_in.sin_port = htons(HL_PORT);
	local_in.sin_family = AF_INET;

	if (bind(local_sock, (SOCKADDR *)&local_in, sizeof(local_in)) == -1)
		return -1;
	if (listen(local_sock, 10) == -1)
		return -1;
	return local_sock;
}

int	sendfile_net(const char *path, const char *filename, SOCKET socket)
{
	char *file = NULL;
	char *buffer = NULL;
	FILE *fd_file = NULL;

	if (path != NULL)
	{
		file = malloc(sizeof(char) * (strlen(path) + strlen(filename) + 1));
		bzero(file, strlen(path) + strlen(filename) + 1);
		strcpy(file, path);
		strcat(file, filename);
	}
	else
	{
		file = malloc(sizeof(char) * (strlen(filename) + 1));
		bzero(file, strlen(filename) + 1);
		strcpy(file, filename);
	}

	if ((fd_file = fopen(file, "r")) == NULL)
	{
		free(file);
		return -1;
	}

	send_net(socket, filename);

	while (get_next_line(fd_file, &buffer) > 0)
		send_net(socket, buffer);
	send_net(socket, "EOF");

	free(file);
	fclose(fd_file);
	return 0;
}

int	recvfile_net(const char *path, SOCKET socket)
{
	char *file = NULL;
	char *filename = NULL;
	char *buffer = NULL;
	FILE *fd_file = NULL;

	filename = recv_net(socket);

	if (path != NULL)
	{
		file = malloc(sizeof(char) * (strlen(path) + strlen(filename) + 1));
		bzero(file, strlen(path) + strlen(filename) + 1);
		strcpy(file, path);
		strcat(file, filename);
	}
	else
	{
		file = malloc(sizeof(char) * (strlen(filename) + 1));
		bzero(file, strlen(filename) + 1);
		strcpy(file, filename);
	}

	if ((fd_file = fopen(file, "w+")) == NULL)
	{
		free(file);
		return -1;
	}

	while (strcmp(buffer, "EOF") != 0)
	{
		buffer = recv_net(socket);
		if (strcmp(buffer, "EOF") != 0)
			fputs(buffer, fd_file);
	}

	free(file);
	free(filename);
	free(buffer);
	fclose(fd_file);
	return 0;
}

int	send_net(SOCKET socket, const char *buffer)
{
	if (send(socket, ft_itoa(strlen(buffer) + 1), strlen(buffer) + 1, 0) == -1)
	{
		perror("send size");
		return -1;
	}
	if (send(socket, buffer, strlen(buffer) + 1, 0) == -1)
	{
		perror("send buffer");
		return -1;
	}
	return 0;
}

char	*recv_net(SOCKET socket)
{
	unsigned int size;
	char *buffer = NULL;
	int bytes = 0;

	buffer = calloc(6, sizeof(char));

	if ((bytes = recv(socket, buffer, sizeof(buffer), 0)) == -1)
	{
		perror("recv size");
		return NULL;
	}
	else
		printf("recv size: %d bytes\n", bytes);
	printf("recv size = |%s|\n", buffer);

	size = atoi(buffer);
	buffer = realloc(buffer, sizeof(char) * size);
	bzero(buffer, size);

	if ((bytes = recv(socket, buffer, sizeof(buffer), 0)) == -1)
	{
		perror("recv buffer");
		return NULL;
	}
	else
		printf("recv buffer: %d bytes\n", bytes);
	printf("recv buffer = |%s|\n", buffer);
	return buffer;
}

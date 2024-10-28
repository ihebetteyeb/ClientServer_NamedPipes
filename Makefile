CC = gcc
CFLAGS = -Wall
SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): Server.c Handlers_Serv.h server_cli_fifo.h
	$(CC) $(CFLAGS) -o $(SERVER) Server.c Handlers_Serv.h server_cli_fifo.h

$(CLIENT): Client.c Handlers_Cli.h server_cli_fifo.h
	$(CC) $(CFLAGS) -o $(CLIENT) Client.c Handlers_Cli.h server_cli_fifo.h

clean:
	rm -f $(SERVER) $(CLIENT)

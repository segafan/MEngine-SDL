#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <SDL_net.h>

struct TCPConnection
{
public:
	TCPConnection(TCPsocket socket, Uint32 timeout, int ID)
	{
		this->socket = socket;
		this->timeout = timeout;
		this->ID = ID;
	}

	TCPsocket socket;
	Uint32 timeout;
	int ID;
};

class Server
{
public:
	Server()
	{
		server = 0;

		playerNum = 0;
		maxPlayerNum = 2;

		socketSet = SDLNet_AllocSocketSet(maxPlayerNum);

		currentID = 0;
	}
	~Server()
	{
		for (unsigned int i = 0; i < clients.size(); i++)
		{
			if (clients[i].socket != 0)
			{
				SDLNet_TCP_DelSocket(socketSet, clients[i].socket);
				SDLNet_TCP_Close(clients[i].socket);
				clients[i].socket = 0;
			}
		}

		if (socketSet != 0)
		{
			SDLNet_FreeSocketSet(socketSet);
			socketSet = 0;
		}

		if (server != 0)
		{
			SDLNet_TCP_Close(server);
			server = 0;
		}
	}

	bool StartServer(const unsigned int& port)
	{
		if (SDLNet_ResolveHost(&ip, NULL, port) == 0)
		{
			server = SDLNet_TCP_Open(&ip);
			//TODO: Log this
			std::cout << "Server Started!" << std::endl;
		}
		else
			server = 0;

		return (server != 0);
	}

	void Update()
	{
		//Check for new sockets
		TCPsocket tempSocket = SDLNet_TCP_Accept(server);

		if (tempSocket)
		{
			//If not reached max players then connect
			if (playerNum < maxPlayerNum)
			{
				SDLNet_TCP_AddSocket(socketSet, tempSocket);
				clients.push_back(TCPConnection(tempSocket, SDL_GetTicks(), currentID));

				//TODO: Log this
				std::cout << "Client connected!" << std::endl;

				currentID++;
				playerNum++;
			}
			else
			{
				//TODO: Log this
				std::cout << "Reached Max Players client couldn't connect!" << std::endl;

				//TODO: Send disconnect data!

				SDLNet_TCP_Close(tempSocket);
				tempSocket = 0;
			}
		}

		tempSocket = 0;

		//Update current sockets

		//Get Data
		while (SDLNet_CheckSockets(socketSet, 0) > 0)
		{
			for (unsigned int i = 0; i < clients.size(); i++)
			{
				if (SDLNet_SocketReady(clients[i].socket))
				{
					if (clients[i].socket != 0)
					{
						clients[i].timeout = SDL_GetTicks();
						
						char* tempText = "";
						if (SDLNet_TCP_Recv(clients[i].socket, tempText, 1500) <= 0)
						{
							if (clients[i].socket != 0)
							{
								SDLNet_TCP_DelSocket(socketSet, clients[i].socket);
								SDLNet_TCP_Close(clients[i].socket);
							}
							clients[i].socket = 0;
							clients.erase(clients.begin() + i);
							
							std::cout << "Client Disconnected!" << std::endl;

							playerNum--;
							
							continue;
						}
						else
						{
							//TODO: Process Data or save it for further processing
						}
					}
				}
			}
		}

		//Send Data
		//TODO: Send data
	}

private:
	IPaddress ip;
	TCPsocket server;

	unsigned int playerNum;
	unsigned int maxPlayerNum;

	int currentID;

	SDLNet_SocketSet socketSet;
	std::vector<TCPConnection> clients;
};

#endif
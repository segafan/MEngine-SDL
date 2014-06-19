#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <vector>
#include <SDL_net.h>

#include "Util.h"

struct TCPConnection
{
public:
	TCPConnection()
	{
		this->socket = 0;
		this->timeout = SDL_GetTicks();
		this->ID = 0;
	}
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
		maxPlayerNum = 20;

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
				if (clients[currentID].socket == NULL)
				{
					SDLNet_TCP_AddSocket(socketSet, tempSocket);
					clients[currentID] = (TCPConnection(tempSocket, SDL_GetTicks(), currentID));

					//TODO: Log this
					std::cout << "Client " << currentID << " Connected!" << std::endl;

					currentID++;
					playerNum++;
				}
			}
			else
			{
				//TODO: Log this
				std::cout << "Reached Max Players client couldn't connect!" << std::endl;

				//TODO: Send disconnect data!
				std::string text = "dc Reached Max Players!";
				SDLNet_TCP_Send(tempSocket, text.c_str(), text.size() + 1);

				SDLNet_TCP_Close(tempSocket);
				tempSocket = 0;
			}
		}

		tempSocket = 0;

		//Update current sockets

		typedef std::map<int, TCPConnection>::iterator it_type;
		
		//Get Data
		while (SDLNet_CheckSockets(socketSet, 0) > 0)
		{
			for (it_type it = clients.begin(); it != clients.end(); it++)
			{
				//Set i to the number it's iterating
				int i = it->first;

				//Check for data on the socket
				if (SDLNet_SocketReady(clients[i].socket))
				{
					//Check if socket exists
					if (clients[i].socket != 0)
					{
						clients[i].timeout = SDL_GetTicks();
						
						//TODO: Maybe 255 for maxlen won't be enough
						//Recive Data
						char tempText[255];
						if (SDLNet_TCP_Recv(clients[i].socket, tempText, 255) <= 0)
						{
							//If socket Disconnected Delete socket
							if (clients[i].socket != 0)
							{
								SDLNet_TCP_DelSocket(socketSet, clients[i].socket);
								SDLNet_TCP_Close(clients[i].socket);
							}
							clients[i].socket = 0;
							clients.erase(i + 1);
							
							std::cout << "Client " << i << " Disconnected!" << std::endl;

							playerNum--;
							
							continue;
						}
						else
						{
							//Data Recived

							//TODO: This uses char* or char[] test if it's good
							//Remove unusable end of the text got from recv()
							std::cout << FormatRecv(tempText) << std::endl;

							//TODO: Process Data or save it for further processing
						}
					}
				}
			}
		}

		//Process Data


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
	std::map<int, TCPConnection> clients;
};

#endif
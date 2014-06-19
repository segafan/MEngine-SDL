#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include <SDL_net.h>

#include "Util.h"

class Client
{
public:
	Client()
	{
		ID = -1;

		server = 0;
		socketSet = SDLNet_AllocSocketSet(1);
	}

	~Client()
	{
		if (server != 0)
		{
			SDLNet_TCP_DelSocket(socketSet, server);
			SDLNet_TCP_Close(server);
			server = 0;
		}
		if (socketSet != 0)
		{
			SDLNet_FreeSocketSet(socketSet);
			socketSet = 0;
		}
	}

	bool Connect(const std::string& host, const unsigned int& port)
	{
		if (SDLNet_ResolveHost(&ip, host.c_str(), port) == 0)
		{
			server = SDLNet_TCP_Open(&ip);
			SDLNet_TCP_AddSocket(socketSet, server);

			//TODO: Log this
			if (server != 0)
				std::cout << "Connected to " << host << ":" << port << std::endl;
		}
		else
			server = 0;

		return (server != 0);
	}

	void Update()
	{
		//Get Data
		while (SDLNet_CheckSockets(socketSet, 0) > 0)
		{
			if (SDLNet_SocketReady(server))
			{
				if (server != 0)
				{
					char text[255];
					if (SDLNet_TCP_Recv(server, text, 255) <= 0)
					{
						if (server != 0)
						{
							SDLNet_TCP_DelSocket(socketSet, server);
							SDLNet_TCP_Close(server);
						}
						server = 0;

						std::cout << "Server Disconnected!" << std::endl;
					}
					else
					{
						std::cout << text << std::endl;
						//TODO: Process Data or save it for further processing
					}
				}
			}
		}


		//Send Data
	}

	void Send(const std::string& data)
	{
		//TODO: Don't send it push it to a vector array and then send data from the array
		std::string text = (data + "/").c_str();
		if (server != 0)
		{
			if (SDLNet_TCP_Send(server, &text, 255) <= 0)
				std::cout << "Disconnected" << std::endl;
		}
	}

private:
	int ID;

	IPaddress ip;
	TCPsocket server;

	SDLNet_SocketSet socketSet;
};

#endif
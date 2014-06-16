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
		server = 0;
		ID = 0;
	}

	~Client()
	{
		if (server != 0)
		{
			SDLNet_TCP_Close(server);
			server = 0;
		}
	}

	bool Connect(const std::string& host, const unsigned int& port)
	{
		if (SDLNet_ResolveHost(&ip, host.c_str(), port) == 0)
		{
			server = SDLNet_TCP_Open(&ip);

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
		std::string textNormal = "hi! how are you! 0123456789 abcdefjhigklmopqrstuvwxyz";
		textNormal += "/";
		const char* text = textNormal.c_str();
		std::cout << text << std::endl;
		if (server != 0)
		{
			if (SDLNet_TCP_Send(server, text, strlen(text)) <= 0)
				std::cout << "Disconnected" << std::endl;
		}
	}

private:
	int ID;

	IPaddress ip;
	TCPsocket server;

	SDLNet_SocketSet set;
};

#endif
#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include <SDL_net.h>

class Client
{
public:
	Client()
	{
		server = 0;
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
		char* text = "hi! how are you! 0123456789 abcdefjhigklmopqrstuvwxyz αινσφυϊόϋ";
		if (server != 0)
		{
			if (SDLNet_TCP_Send(server, text, strlen(text)) <= 0)
				std::cout << "Disconnected" << std::endl;
		}
	}

private:
	IPaddress ip;
	TCPsocket server;

	SDLNet_SocketSet set;
};

#endif
#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <SFML/Network.hpp>
#include <sstream>
#include <string>

#include "Player.h"
#include "Alien.h"

class NetworkHandler
{
public:

	sf::TcpSocket m_Socket;
	sf::TcpListener m_Listener;
	sf::TcpSocket m_Client;

	NetworkHandler();

	void sendIntData(int& data);
	void startServer(Player* players, Alien* aliens);
	void clientStart(Player* players, Alien* aliens);
	int getAlienInt(Alien& alien, int alienPlace);
	int returnIntData();
	void serverUpdate(Player* players, Alien* aliens);
	void clientUpdate(Player& player, Player* players, Alien* aliens);

	Player convertIntData(int inputValue);

	bool m_bServer;
	int m_iPlayerNum;

	const int m_kPortNum = 1048;

	int m_iCurrentOutput;

private:

	static const int m_kInformationSize = 62;
	int getPlayerInt(Player& player);
	sf::Packet packetArray(int* information);
	void networkSend(Player* players, Alien* aliens);
	int getBulletInt(Bullet& bullet, int bulletPlace);
	void networkReceive(Player* players, Alien* aliens);
	void sortData(Player* players, Alien* aliens, int* dataToSort);
	void outputArrayInformation(int* information, sf::Packet& recievedInformation);
};
#endif

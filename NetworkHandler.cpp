#include "NetworkHandler.h"

//Constructor.
NetworkHandler::NetworkHandler()
	:m_bServer(false)
	,m_iPlayerNum(-1)
{

}

//When called starts the server.
void NetworkHandler::startServer(Player* players, Alien* aliens)
{
	m_iCurrentOutput = 0;
	m_iPlayerNum = 1;
	m_bServer = true;
	m_Listener.setBlocking(false);
	m_Socket.setBlocking(false);
	m_Listener.listen(m_kPortNum);
	sf::Socket::Status status = m_Socket.connect("localhost", m_kPortNum);
	if (status != sf::Socket::Done)
	{
	}
	players[0].setActive(true);
}

//Sends an int value to the server.
void NetworkHandler::sendIntData(int& data)
{
	if (m_Socket.send(&data, 100) != sf::Socket::Done)
	{

	}
}

//Takes in an int array and outputs a packet with the data inside.
sf::Packet NetworkHandler::packetArray(int* information)
{
	sf::Packet tempPacket;
	for (int i = 0; i < m_kInformationSize; i++)
	{
		tempPacket << information[i];
	}
	return tempPacket;
}

//Takes in a packet and sets the array information to the data received.
void NetworkHandler::outputArrayInformation(int* information, sf::Packet& recievedInformation)
{
	for (int i = 0; i < m_kInformationSize; i++)
	{
		recievedInformation >> information[i];
	}
}

//Sends the game information to the other player, this includes all of the positions of players, aliens and players.bullets.
void NetworkHandler::networkSend(Player* players, Alien* aliens)
{
	int dataForSending[m_kInformationSize];

	for (int i = 0; i < m_kInformationSize; i++)
	{
		if (i == 0)
		{
			dataForSending[i] = getPlayerInt(players[0]);
		}
		else if (i < 21)
		{
			dataForSending[i] = getBulletInt(players[0].m_Bullets[i - 1], (i - 1));
		}
		else if (i < 22)
		{
			dataForSending[i] = getPlayerInt(players[1]);
		}
		else if (i < 42)
		{
			dataForSending[i] = getBulletInt(players[1].m_Bullets[i - 22], (i - 22));
		}
		else if(i < 63)
		{
			dataForSending[i] = getAlienInt(aliens[i - 42], (i - 42));
		}
	}

	m_Socket.setBlocking(true);
	sf::Packet packet = packetArray(dataForSending);
	size_t size = packet.getDataSize();
	m_Socket.send(packet);
	m_Socket.setBlocking(false);
}

//Turns the received packet into usable information for the game and changes the values in the arrays passed through.
void NetworkHandler::networkReceive(Player* players, Alien* aliens)
{
	sf::Packet value;
	m_Socket.setBlocking(true);
	m_Socket.receive(value);

	if (value.getDataSize() > 0)
	{
		int outputArray[m_kInformationSize];
		outputArrayInformation(outputArray, value);

		sortData(players, aliens, outputArray);
	}
	m_Socket.setBlocking(false);
}

//This sorts the array of data into the players, aliens and players.bullets arrays to be used in game.
void NetworkHandler::sortData(Player* players, Alien* aliens, int* dataToSort)
{
	for (int i = 0; i < m_kInformationSize; i++)
	{
		if (i == 0)
		{
			if (m_iPlayerNum != 1)
			{
				Player tempPlayer = convertIntData(dataToSort[i]);
				players[0].m_Position.x = tempPlayer.m_Position.x;
				players[0].m_Position.y = tempPlayer.m_Position.y;
				players[0].setActive(tempPlayer.isActive());
				players[0].m_bHasFired = false;
			}
		}
		else if (i < 21)
		{
			Player tempPlayer = convertIntData(dataToSort[i]);

			players[0].m_Bullets[i - 1].m_Position.x = tempPlayer.m_Position.x;
			players[0].m_Bullets[i - 1].m_Position.y = tempPlayer.m_Position.y;
		}
		else if (i < 22)
		{
			if (m_iPlayerNum != 2)
			{
				Player tempPlayer = convertIntData(dataToSort[i]);
				players[1].m_Position.x = tempPlayer.m_Position.x;
				players[1].m_Position.y = tempPlayer.m_Position.y;
				players[1].setActive(tempPlayer.isActive());
				players[1].m_bHasFired = false;
			}
		}
		else if (i < 42)
		{
			Player tempPlayer = convertIntData(dataToSort[i]);
			players[1].m_Bullets[i - 22].m_Position.x = tempPlayer.m_Position.x;
			players[1].m_Bullets[i - 22].m_Position.y = tempPlayer.m_Position.y;
		}
		else
		{
			Player tempPlayer = convertIntData(dataToSort[i]);
			aliens[i - 42].m_Position.x = tempPlayer.m_Position.x;
			aliens[i - 42].m_Position.y = tempPlayer.m_Position.y;
			aliens[i - 42].m_bDestroyed = tempPlayer.isActive();
		}
	}
}

//Used on server, listens to the defined port and accepts a user if connected.
void NetworkHandler::serverUpdate(Player* players, Alien* aliens)
{
	if (!(players[1].isActive()))
	{
		m_Listener.listen(m_kPortNum);

		if (m_Listener.accept(m_Socket) == sf::Socket::Done)
		{
			networkSend(players, aliens);
		}
	}

	int dataVal = returnIntData();
	if (dataVal != -1)
	{
		players[1].m_bIsNetworked = true;
		Player tempPlayer = convertIntData(dataVal);
		players[1].m_Position.x = tempPlayer.m_Position.x;
		players[1].m_Position.y = tempPlayer.m_Position.y;
		if (players[1].m_bHasFired != tempPlayer.m_bHasFired)
		{
			players[1].m_bHasFired = tempPlayer.m_bHasFired;
		}
		else
		{
			players[1].m_bHasFired = false;
		}
		players[1].setActive(tempPlayer.isActive());
	}

	if (m_iCurrentOutput > 10)
	{
		networkSend(players, aliens);
		m_iCurrentOutput = 0;
	}
	else
	{
		m_iCurrentOutput++;
	}
}


//When this is called all information is setup for the client, there must be a server to connect to at the IP and port
//or it will cause a crash.
void NetworkHandler::clientStart(Player* players, Alien* aliens)
{
	if (m_Socket.connect("localhost", m_kPortNum) == sf::Socket::Done)
	{
		networkReceive(players, aliens);
		players[1].setActive(true);
		int dataVal = getPlayerInt(players[1]);
		sendIntData(dataVal);
		m_iPlayerNum = 2;
	}
	else
	{
		int test = 0;
	}
}

//Used on client, connects to the server if there is a server at the specified IP at the designated port.
void NetworkHandler::clientUpdate(Player& player, Player* players, Alien* aliens)
{
	networkReceive(players, aliens);
	int dataVal = getPlayerInt(players[1]);
	sendIntData(dataVal);
	players[1].m_bHasFired = false;
}

//Turns player data into an int to be sent across the network.
int NetworkHandler::getPlayerInt(Player& player)
{
	int outputVal;

	if (player.m_bHasFired)
	{
		outputVal = 1 * 1000000000;
		player.m_bHasFired = false;
	}
	else
	{
		outputVal = 0;
	}

	if (player.isActive())
	{
		outputVal += 1 * 100000000;
	}
	else
	{
		outputVal += 0;
	}
	outputVal += (static_cast<int>(player.getPlayerNum()) * 1000000);
	outputVal += (static_cast<int>(player.m_Position.y) * 1000);
	outputVal += (static_cast<int>(player.m_Position.x));


	return outputVal;
}

//Turns player data into an int to be sent across the network.
int NetworkHandler::getAlienInt(Alien& alien, int alienPlace)
{
	int outputVal = 0;

	if (alien.m_bDestroyed)
	{
		outputVal += 1 * 100000000;
	}
	else
	{
		outputVal += 0;
	}
	outputVal += (static_cast<int>(alienPlace + 10) * 1000000);
	outputVal += (static_cast<int>(alien.m_Position.y) * 1000);
	outputVal += (static_cast<int>(alien.m_Position.x));


	return outputVal;
}

//Converts bullet class into int for sending through the network.
int NetworkHandler::getBulletInt(Bullet& bullet, int bulletPlace)
{
	int outputVal;

	outputVal = 0;
	outputVal += 1000000;
	if (bullet.m_Position.y > 0)
	{
		outputVal += (static_cast<int>(bullet.m_Position.y) * 1000);
		outputVal += (static_cast<int>(bullet.m_Position.x));
	}
	else
	{
		outputVal += 200 * 1000;
		outputVal += 999;
	}

	return outputVal;
}

//Converts the input int value into a usable player class.
Player NetworkHandler::convertIntData(int inputValue)
{
	Player outputPlayer;

	int values[5];

	//Breaks input int into usable ints.
	values[0] = inputValue % 1000;
	inputValue = inputValue / 1000;
	values[1] = inputValue % 1000;
	inputValue = inputValue / 1000;
	values[2] = inputValue % 100;
	inputValue = inputValue / 100;
	values[3] = inputValue % 10;
	inputValue = inputValue / 10;
	values[4] = inputValue % 10;
	inputValue = inputValue / 10;

	//Assigns the variables to their destination inside the outputPlayer.
	outputPlayer.m_Position.x = static_cast<float>(values[0]);
	outputPlayer.m_Position.y = static_cast<float>(values[1]);
	outputPlayer.setPlayerNum(values[2]);

	if (values[3] == 1)
	{
		outputPlayer.setActive(true);
	}
	else if (values[3] == 0)
	{
		outputPlayer.setActive(false);
	}
	if (values[4] == 1)
	{
		outputPlayer.m_bHasFired = true;
	}
	else if (values[4] == 0)
	{
		outputPlayer.m_bHasFired = false;
	}

	return outputPlayer;
}

//returns the data received from a client.
int NetworkHandler::returnIntData()
{
	int value = -1;
	size_t info;
	m_Socket.receive(&value, 100, info);
	return value;
}
#include "CommClient.h"
#include "OpenMSXConnection.h"

CommClient::~CommClient()
{
	closeConnection();
}

CommClient& CommClient::instance()
{
	static CommClient oneInstance;
	return oneInstance;
}

void CommClient::connectToOpenMSX(std::unique_ptr<OpenMSXConnection> conn)
{
	closeConnection();
	connection = std::move(conn);
	connect(connection.get(), SIGNAL(disconnected()), SLOT(closeConnection()));
	connect(connection.get(),
	        SIGNAL(logParsed(const QString&, const QString&)),
	        SIGNAL(logParsed(const QString&, const QString&)));
	connect(connection.get(),
	        SIGNAL(updateParsed(const QString&, const QString&, const QString&)),
	        SIGNAL(updateParsed(const QString&, const QString&, const QString&)));
	emit connectionReady();
}

void CommClient::closeConnection()
{
	if (connection) {
		connection->disconnect(this, SLOT(closeConnection()));
		connection.reset();
		emit connectionTerminated();
	}
}

void CommClient::sendCommand(CommandBase* command)
{
	if (connection) {
		connection->sendCommand(command);
	} else {
		command->cancel();
	}
}

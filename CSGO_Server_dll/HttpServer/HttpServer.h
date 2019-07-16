#pragma once

#include <QtCore/qglobal.h>
#include <QTcpServer>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QRegExp>
#include <QThread>
#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QHostAddress>

#ifndef BUILD_STATIC
# if defined(HTTPSERVER_LIB)
#  define HTTPSERVER_EXPORT Q_DECL_EXPORT
# else
#  define HTTPSERVER_EXPORT Q_DECL_IMPORT
# endif
#else
# define HTTPSERVER_EXPORT
#endif

#define RUN_KEY "HKEY_CURRENT_USER\\SOFTWARE\\Valve\\Steam"
#define RESOURCES ":/HttpServer/Resources"
#define DIR_CFG_CSGO "/steamapps/common/Counter-Strike Global Offensive/csgo/cfg"
#define FILE_LOCAL_CFG_CSGO "gamestate_integration_consolesample.cfg"

#define REXPLAYER "\\\"steamid\\\": \\\"([0-9]+)\\\",([0-9a-z\\n\\t\\\"\\s\\S]+)\\\"player\\\": \\{[\\n\\t\\s\\S]+\\\"steamid\\\": \\\"([0-9]+)\\\",[0-9a-z\\n\\t\\\"\\s\\S]+\\\"round_killhs\\\": ([0-9]+),[0-9a-z\\n\\t\\\"\\s\\S]+\\\"weapons\\\"([0-9a-z\\n\\t\\\"\\s\\S]+)\\\"kills\\\": ([0-9]+),\\n\\t\\t\\t\\\"assists\\\": [0-9]+,\\n\\t\\t\\t\\\"deaths\\\": ([0-9])+,"
#define REXWEAPON "\\\"Knife\\\",\\n\\t\\t\\t\\t\\\"state\\\": \\\"([a-z]+)"
typedef enum
{
	/* no error */
	HTTP_INITIAL_SUCCESS = 1,    /**< no error: The key matching is correct and the setup is successful*/
	HTTP_ERR_NONE = 0,    /**< Not errors */

	/* reserved for unexpected errors */
	HTTP_ERR_UNKNOWN = -1,   /**< unknown error. */

	/* error codes <0 */
	HTTP_ERR_LACK_STREAM = -2,   /**< Not installed Stream */
	HTTP_ERR_LACK_GAME = -3,   /**< Not installed GAME */
	HTTP_ERR_LACK_CFG = -4,   /**< Lack of CFG File of Resource */
	HTTP_ERR_COPY_CFG = -5,   /**< CFG File COPY FAIL */
} HTTP_RESULT;

typedef enum
{
	CSGO_KILL = 0,    /**< CsGo Kill*/
	CSGO_KILLhs,
	CSGO_DEATH,
	CSGO_KINFE,
	CSGO_GUN

} Game_Message;

typedef enum {
	Kills = 0,
	Death
}HTTP_Actions;

#define HTTP_GAME_LEN	 1 
typedef enum
{
	CSGO = 0
}HTTP_GAME;

extern QRegExp rx_Player;
extern QRegExp rx_Weapon;


class HTTPSERVER_EXPORT HttpServer : public QTcpServer
{
	Q_OBJECT
public:
	HttpServer();
	~HttpServer();
	HTTP_RESULT CheckEnv(HTTP_GAME game);

private:
	//void incomingConnection(int sockDesc);
	void incomingConnection(qintptr handle);


signals:
	void getCSGOEvent(Game_Message type);
	
private slots:
	void recvData(bool isplay, bool isMaster, int weapon, int Killhs, int Kills, int Deaths);

private:
	int kills = 0;
	int deaths = 0;
	int killhs = 0;
	QString act = "";
	bool isDeath = false;
	int isK = 0;
};


class MySocket : public QTcpSocket
{
	Q_OBJECT
public:
	explicit MySocket(int sockDesc, QObject *parent = Q_NULLPTR);
	~MySocket();

signals:
	void dataReady(bool isplay, bool isMaster, int weapon, int Kills, int Killhs, int Deaths);

public slots:
	void recvData(void);
	void sendData();

private:
	int m_sockDesc;
	int pos;
};

class Socket;

class serverThread : public QThread
{
	Q_OBJECT
public:
	serverThread(qintptr sockDesc, QObject *parent = Q_NULLPTR);
	~serverThread();

private:
	void run(void);

signals:
	void dataReady(bool isplay, bool isMaster, int weapon, int Killhs, int Killss, int Deaths);

private slots:
	void recvDataSlot(bool isplay, bool isMaster, int weapon, int Killhs, int Kills, int Deaths);
	void disconnectToHost(void);

private:
	MySocket *m_socket;
	qintptr m_sockDesc;
};


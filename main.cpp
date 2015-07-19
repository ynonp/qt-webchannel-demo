#include <QCoreApplication>
#include <QWebChannel>
#include <QWebSocket>
#include <QWebSocketServer>
#include "shared/websocketclientwrapper.h"
#include "shared/websockettransport.h"

#include "hasher.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // setup the QWebSocketServer
    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"), QWebSocketServer::NonSecureMode);
    if (!server.listen(QHostAddress::LocalHost, 12345)) {
        qFatal("Failed to open web socket server.");
        return 1;
    }

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper clientWrapper(&server);

    // setup the channel
    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    // setup the dialog and publish it to the QWebChannel
    Hasher hasher;
    channel.registerObject(QStringLiteral("hasher"), &hasher);

    return app.exec();
}

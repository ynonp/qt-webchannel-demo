# Qt WebChannel Demo

Qt 5.5 has added a cool new feature letting developers connect any existing C++ code with any web based frontend UI. The connection is made through a QWebChannel class.  

This repository shows a simple example of that connection based on the example in Qt documentation. Here's the important bits of code you need to understand to get started.

## Setup

Setting up the code requires running a Socket Server on the Qt/C++ side and connecting to it from JS. The code to run the socket server is found in main. After server is up, we register a C++ class on the channel, so JS code can call methods on the object:

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

From JavaScript we need to connect to the web server. Notice the example uses localhost:

		var ws = new WebSocket("ws://localhost:12345");
		ws.onopen = function() {
			el.status.innerHTML = "Connected";

			new QWebChannel(ws, function(channel) {
				// make dialog object accessible globally
				api = channel.objects.hasher;

				api.notifyResult.connect(function(method, hex) {
					el[method].value = hex;
				});
			});
		};

## Running Code
After everythin's set up calling methods is easy. Each object registered on the channel is available to JS using channel.objects.objectName. The example uses an object named hasher so it is accessed from JS with channel.object.hasher  

On the C++ side, the object is just a normal QObject with signals and slots. Every slot of the object is available for JS side to call as a normal function call, and every signal is an object that JS can "connect" to.

The lines:

		api.notifyResult.connect(function(method, hex) {
				el[method].value = hex;
		});

Start to listen on notifyResult signal and whenever it is emitted runs the callback. The lines:

		api.md5(txt);
		api.sha256(txt);
		api.sha3(txt);

Call the slots `md5`, `sha256` and `sha3` of the C++ hasher object.


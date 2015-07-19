var ws = new WebSocket("ws://localhost:12345");
var api;

var el = {
	status: document.querySelector('#conn-status'),
	go: document.querySelector('#btn-go'),
	inp: document.querySelector('#inp-text'),
	md5: document.querySelector('#res-md5'),
	sha2: document.querySelector('#res-sha256'),
	sha3: document.querySelector('#res-sha3')
};	

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

ws.onerror = function() {
	el.status.innerHTML = "Error";
};

ws.onclose = function() {
	el.status.innerHTML = "Closed";
};

el.go.addEventListener('click', function() {
	if (! api ) { return; }

	var txt = el.inp.value;
	api.md5(txt);
	api.sha256(txt);
	api.sha3(txt);
});


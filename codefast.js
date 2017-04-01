let Keyboard = require('node-keylogger');
let request = require("request");
 
let k = new Keyboard('event0'); // 'event0' is the file corresponding to my keyboard in /dev/input/
k.on('keypress', count);
k.on('error', console.error);

let counter = 0;

setInterval(function () {
	let power = counter * 12;
	console.log(power + '%');
	
	request("http://192.168.130.223/on?left=" + power, function(error, response, body) {
		// console.log(body);
	});

	counter = 0;
}, 1000);

function count() {
	counter++;
}

let Keyboard = require('node-keylogger');
 
let k = new Keyboard('event0'); // 'event0' is the file corresponding to my keyboard in /dev/input/ 
k.on('keyup', count);
k.on('keydown', count);
k.on('keypress', count);
k.on('error', console.error);

let counter = 0;

setInterval(function () {
	console.log(counter);
}, 5000);

function count() {
	counter++;
}
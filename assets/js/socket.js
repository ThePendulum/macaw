'use strict';

import config from 'config';

let ws;

ws = new WebSocket(config.socket);

const socket = {};

socket.init = function(channels, sync) {
    ws.addEventListener('message', message => {
        const data = JSON.parse(message.data);

        Object.keys(data).forEach(key => {
            channels[key] = data[key];

            sync();
        });
    });
}

socket.emit = function(property, value) {
    const msg = {};
    msg[property] = value;

    if(ws) {
        ws.send(JSON.stringify(msg));
    }
};

export default socket;
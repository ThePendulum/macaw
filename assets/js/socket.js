'use strict';

import config from 'config';

let ws;

ws = new WebSocket(config.socket);

ws.addEventListener('message', message => {
    const data = JSON.parse(message.data);

    Object.keys(data).forEach(key => {
        store.commit(key, data[key]);
    });
});

const socket = {};

socket.emit = function(property, value) {
    const msg = {};
    msg[property] = value;

    if(ws) {
        ws.send(JSON.stringify(msg));
    }
};

export default socket;
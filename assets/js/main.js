'use strict';

import '../css/style.scss';

import socket from './socket.js';

const hue = document.querySelector('#hue');
const saturation = document.querySelector('#saturation');
const value = document.querySelector('#value');

const channels = {
    hue: {
        mode: 0,
        value: 0
    },
    saturation: {
        mode: 0,
        value: 1
    },
    value: {
        mode: 0,
        value: 1
    }
};

hue.addEventListener('input', event => {
    channels.hue.value = parseInt(event.target.value);
    socket.emit('hue', channels.hue.value);

    sync();
});

saturation.addEventListener('input', event => {
    channels.saturation.value = parseInt(event.target.value);
    socket.emit('saturation', channels.saturation.value);

    sync();
});

value.addEventListener('input', event => {
    channels.value.value = parseInt(event.target.value);
    socket.emit('value', channels.value.value);

    sync();
});

function sync() {
    hue.value = channels.hue.value;
    saturation.value = channels.saturation.value;
    value.value = channels.value.value;
}
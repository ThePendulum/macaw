'use strict';

import '../css/style.scss';

import socket from './socket.js';
import {hsvToRgb} from './hsvToRgb.js';

const hue = document.querySelector('#hue');
const hueMode = document.querySelector('#hueMode');

const saturation = document.querySelector('#saturation');
const saturationMode = document.querySelector('#saturationMode');

const value = document.querySelector('#value');
const valueMode = document.querySelector('#valueMode');

const channels = {
    hue: {
        mode: 0,
        value: 0
    },
    saturation: {
        mode: 0,
        value: 255
    },
    value: {
        mode: 0,
        value: 255
    }
};

hue.addEventListener('input', event => {
    channels.hue.value = parseInt(event.target.value);
    socket.emit('hue', channels.hue.value);

    sync();
});

hueMode.addEventListener('change', event => {
    channels.hue.mode = parseInt(event.target.value);
    socket.emit('hueMode', channels.hue.mode);

    sync();
});

saturation.addEventListener('input', event => {
    channels.saturation.value = parseInt(event.target.value);
    socket.emit('saturation', channels.saturation.value);

    sync();
});

saturationMode.addEventListener('change', event => {
    channels.saturation.mode = parseInt(event.target.value);
    socket.emit('saturationMode', channels.saturation.mode);

    sync();
});

value.addEventListener('input', event => {
    channels.value.value = parseInt(event.target.value);
    socket.emit('value', channels.value.value);

    sync();
});

valueMode.addEventListener('change', event => {
    channels.value.mode = parseInt(event.target.value);
    socket.emit('valueMode', channels.value.mode);

    sync();
});


function sync(channel) {
    const fixedHue = Array.from({length: 7}, (value, index) => {
        return hsvToRgb(index * (255 / 6), channels.saturation.value, channels.value.value).toString();
    });

    const fixedSaturation = hsvToRgb(channels.hue.value, 255, channels.value.value);
    const fixedValue = hsvToRgb(channels.hue.value, channels.saturation.value, 255);
    
    hue.parentElement.style = `background: linear-gradient(to right, ${fixedHue[0]}, ${fixedHue[1]}, ${fixedHue[2]}, ${fixedHue[3]}, ${fixedHue[4]}, ${fixedHue[5]}, ${fixedHue[6]})`;
    saturation.parentElement.style = `background: linear-gradient(to right, rgb(255, 255, 255), rgb(${fixedSaturation.red}, ${fixedSaturation.green}, ${fixedSaturation.blue}))`;
    value.parentElement.style = `background: linear-gradient(to right, rgb(0, 0, 0), rgb(${fixedValue.red}, ${fixedValue.green}, ${fixedValue.blue}))`;
}

sync();
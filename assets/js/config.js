const config = {};

config.socket = window.location.hostname ? 'ws://' + window.location.hostname + ':81' : 'ws://192.168.178.33:81';

export default config;
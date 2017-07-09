/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// identity function for calling harmony imports with the correct context
/******/ 	__webpack_require__.i = function(value) { return value; };
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, {
/******/ 				configurable: false,
/******/ 				enumerable: true,
/******/ 				get: getter
/******/ 			});
/******/ 		}
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = 3);
/******/ })
/************************************************************************/
/******/ ([
/* 0 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_config__ = __webpack_require__(2);




var ws = void 0;

ws = new WebSocket(__WEBPACK_IMPORTED_MODULE_0_config__["a" /* default */].socket);

ws.addEventListener('message', function (message) {
    var data = JSON.parse(message.data);

    Object.keys(data).forEach(function (key) {
        store.commit(key, data[key]);
    });
});

var socket = {};

socket.emit = function (property, value) {
    var msg = {};
    msg[property] = value;

    if (ws) {
        ws.send(JSON.stringify(msg));
    }
};

/* harmony default export */ __webpack_exports__["a"] = (socket);

/***/ }),
/* 1 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 2 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
var config = {};

config.socket = window.location.hostname ? 'ws://' + window.location.hostname + ':81' : 'ws://192.168.178.33:81';

/* harmony default export */ __webpack_exports__["a"] = (config);

/***/ }),
/* 3 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__css_style_scss__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__css_style_scss___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0__css_style_scss__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__socket_js__ = __webpack_require__(0);






var hue = document.querySelector('#hue');
var saturation = document.querySelector('#saturation');
var value = document.querySelector('#value');

var channels = {
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

hue.addEventListener('input', function (event) {
    channels.hue.value = parseInt(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('hue', channels.hue.value);

    sync();
});

saturation.addEventListener('input', function (event) {
    channels.saturation.value = parseInt(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('saturation', channels.saturation.value);

    sync();
});

value.addEventListener('input', function (event) {
    channels.value.value = parseInt(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('value', channels.value.value);

    sync();
});

function sync() {
    hue.value = channels.hue.value;
    saturation.value = channels.saturation.value;
    value.value = channels.value.value;
}

/***/ })
/******/ ]);
//# sourceMappingURL=bundle.js.map
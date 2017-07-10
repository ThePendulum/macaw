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
/******/ 	return __webpack_require__(__webpack_require__.s = 4);
/******/ })
/************************************************************************/
/******/ ([
/* 0 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return hsvToRgb; });
/* unused harmony export hsvToHex */


var hsvToRgb = function hsvToRgb(h, s, v) {
    var r = void 0,
        g = void 0,
        b = void 0;

    h = Math.abs(h % 256) / 256;
    s = Math.max(0, Math.min(255, s)) / 255;
    v = Math.max(0, Math.min(255, v)) / 255;

    var i = Math.floor(h * 6);
    var f = h * 6 - i;
    var p = v * (1 - s);
    var q = v * (1 - f * s);
    var t = v * (1 - (1 - f) * s);

    switch (i % 6) {
        case 0:
            r = v, g = t, b = p;break;
        case 1:
            r = q, g = v, b = p;break;
        case 2:
            r = p, g = v, b = t;break;
        case 3:
            r = p, g = q, b = v;break;
        case 4:
            r = t, g = p, b = v;break;
        case 5:
            r = v, g = p, b = q;break;
    }

    return {
        red: Math.round(r * 255),
        green: Math.round(g * 255),
        blue: Math.round(b * 255),
        toString: function toString() {
            return 'rgb(' + this.red + ', ' + this.green + ', ' + this.blue + ')';
        }
    };
};

var hsvToHex = function hsvToHex(h, s, v) {
    var rgb = hsvToRgb(h, s, v);

    return '#' + ('0' + Math.round(rgb.r).toString(16)).slice(-2) + ('0' + Math.round(rgb.g).toString(16)).slice(-2) + ('0' + Math.round(rgb.b).toString(16)).slice(-2);
};



/***/ }),
/* 1 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_config__ = __webpack_require__(3);




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
/* 2 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 3 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
var config = {};

config.socket = window.location.hostname ? 'ws://' + window.location.hostname + ':81' : 'ws://192.168.178.33:81';

/* harmony default export */ __webpack_exports__["a"] = (config);

/***/ }),
/* 4 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__css_style_scss__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__css_style_scss___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0__css_style_scss__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__socket_js__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__hsvToRgb_js__ = __webpack_require__(0);







var hue = document.querySelector('#hue');
var hueMode = document.querySelector('#hueMode');
var hueSpeed = document.querySelector('#hueSpeed');

var saturation = document.querySelector('#saturation');
var saturationMode = document.querySelector('#saturationMode');
var saturationSpeed = document.querySelector('#saturationSpeed');

var value = document.querySelector('#value');
var valueMode = document.querySelector('#valueMode');
var valueSpeed = document.querySelector('#valueSpeed');

var channels = {
    hue: {
        mode: 0,
        value: 0,
        speed: 0
    },
    saturation: {
        mode: 0,
        value: 255,
        speed: 0.1
    },
    value: {
        mode: 0,
        value: 255,
        speed: 0.1
    }
};

hue.addEventListener('input', function (event) {
    channels.hue.value = parseInt(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('hue', channels.hue.value);

    sync();
});

hueMode.addEventListener('change', function (event) {
    channels.hue.mode = parseInt(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('hueMode', channels.hue.mode);

    sync();
});

hueSpeed.addEventListener('input', function (event) {
    channels.hue.speed = parseFloat(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('hueSpeed', channels.hue.speed);

    sync();
});

saturation.addEventListener('input', function (event) {
    channels.saturation.value = parseInt(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('saturation', channels.saturation.value);

    sync();
});

saturationMode.addEventListener('change', function (event) {
    channels.saturation.mode = parseInt(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('saturationMode', channels.saturation.mode);

    sync();
});

saturationSpeed.addEventListener('input', function (event) {
    channels.saturation.speed = parseFloat(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('saturationSpeed', channels.saturation.speed);

    sync();
});

value.addEventListener('input', function (event) {
    channels.value.value = parseInt(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('value', channels.value.value);

    sync();
});

valueMode.addEventListener('change', function (event) {
    channels.value.mode = parseInt(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('valueMode', channels.value.mode);

    sync();
});

valueSpeed.addEventListener('input', function (event) {
    channels.value.speed = parseFloat(event.target.value);
    __WEBPACK_IMPORTED_MODULE_1__socket_js__["a" /* default */].emit('valueSpeed', channels.value.speed);

    sync();
});

function sync(channel) {
    hue.value = channels.hue.value;
    hueMode.value = channels.hue.mode;
    hueSpeed.value = channels.hue.speed;

    saturation.value = channels.saturation.value;
    saturationMode.value = channels.saturation.mode;
    saturationSpeed.value = channels.saturation.speed;

    value.value = channels.value.value;
    valueMode.value = channels.value.mode;
    valueSpeed.value = channels.value.speed;

    var fixedHue = Array.from({ length: 7 }, function (value, index) {
        return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__hsvToRgb_js__["a" /* hsvToRgb */])(index * (255 / 6), channels.saturation.value, channels.value.value).toString();
    });

    var fixedSaturation = __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__hsvToRgb_js__["a" /* hsvToRgb */])(channels.hue.value, 255, channels.value.value);
    var fixedValue = __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__hsvToRgb_js__["a" /* hsvToRgb */])(channels.hue.value, channels.saturation.value, 255);

    hue.parentElement.style = 'background: linear-gradient(to right, ' + fixedHue[0] + ', ' + fixedHue[1] + ', ' + fixedHue[2] + ', ' + fixedHue[3] + ', ' + fixedHue[4] + ', ' + fixedHue[5] + ', ' + fixedHue[6] + ')';
    saturation.parentElement.style = 'background: linear-gradient(to right, rgb(255, 255, 255), rgb(' + fixedSaturation.red + ', ' + fixedSaturation.green + ', ' + fixedSaturation.blue + '))';
    value.parentElement.style = 'background: linear-gradient(to right, rgb(0, 0, 0), rgb(' + fixedValue.red + ', ' + fixedValue.green + ', ' + fixedValue.blue + '))';
}

sync();

/***/ })
/******/ ]);
//# sourceMappingURL=bundle.js.map
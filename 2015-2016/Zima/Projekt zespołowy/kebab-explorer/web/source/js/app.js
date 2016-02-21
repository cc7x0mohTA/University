'use strict';

require('angular');
require('angular-cookies');
require('angular-resource');

window._ = require('lodash');
require('angular-simple-logger');
require('angular-google-maps');

var MainController = require('./controllers/MainController.js'),
    CommentController = require('./controllers/CommentController.js'),
    AuthenticationController = require('./controllers/AuthenticationController.js'),
    RestaurantController = require('./controllers/RestaurantController.js'),
    AuthenticationService = require('./services/AuthenticationService.js'),
    RestaurantService = require('./services/RestaurantService.js'),
    CommentService = require('./services/CommentService.js'),
    UserService = require('./services/UserService.js'),
    InfoPanelDirective = require('./directives/InfoPanelDirective.js'),
    StarRatingDirective = require('./directives/StarRating.js'),
    GalleryDirective = require('./directives/GalleryDirective.js'),
    UserPanelDirective = require('./directives/UserPanelDirective.js'),
    RegistrationPanelDirective = require('./directives/RegistrationPanelDirective.js');

angular
    .module('kebabExplorer', [
        'ngCookies',
        'ngResource',
        'uiGmapgoogle-maps'
    ])
    .factory('Authentication', AuthenticationService)
    .factory('Restaurant', RestaurantService)
    .factory('Comment', CommentService)
    .factory('User', UserService)
    .controller('MainController', MainController)
    .controller('CommentController', CommentController)
    .controller('AuthenticationController', AuthenticationController)
    .controller('RestaurantController', RestaurantController)
    .directive('restaurantInfoPanel', InfoPanelDirective)
    .directive('starRating', StarRatingDirective)
    .directive('gallery', GalleryDirective)
    .directive('userPanel', UserPanelDirective)
    .directive('registrationPanel', RegistrationPanelDirective);

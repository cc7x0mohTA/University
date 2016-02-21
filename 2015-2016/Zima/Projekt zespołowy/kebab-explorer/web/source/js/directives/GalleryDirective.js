'use strict';

// @ngInject
module.exports = function() {
    return {
        restrict: 'E',
        templateUrl: './js/directives/GalleryDirective.html',
        scope: {
            photos: "=ngModel",
            extras: "=?",
            galleryid: "@"
        },
        link: function(scope, element, attributes) {
            scope.getPhotoUrl = function(_photo) {
                return (scope.extras ? _photo.image : _photo);
            };
        }
    }
};
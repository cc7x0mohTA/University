'use strict';

// @ngInject
module.exports = function () {
    return {
        restrict: 'E',
        templateUrl: './js/directives/StarRating.html',
        scope: {
            rating: "=ngModel",
            max: "@",
            readonly: "=?"
        },
        link: function (scope, element, attributes) {
            if(scope.rating == undefined) {
                scope.rating = 1;
            }

            function updateStars() {
                scope.stars = [];
                for (var i = 0; i < scope.max; i++) {
                    scope.stars.push({
                        filled: i < scope.rating
                    });
                }
            };

            scope.toggle = function(index) {
                if(scope.readonly == undefined || scope.readonly == false) {
                    scope.rating = index + 1;
                }
            };

            scope.$watch('rating', function(oldValue, newValue){
                if(newValue) {
                    updateStars();
                }
            });
        }
    }
};
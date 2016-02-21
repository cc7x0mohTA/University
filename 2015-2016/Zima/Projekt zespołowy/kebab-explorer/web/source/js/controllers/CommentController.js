'use strict';

// @ngInject
module.exports = function ($scope, Comment) {
    this.comments = Comment.query();

    this.currentRestaurantName = "";

    this.getCommentsForRestaurant = function (myRestaurantName) {

        if (myRestaurantName == undefined || myRestaurantName == "") {
            return [];
        } else if (myRestaurantName == this.currentRestaurantName) {
            return this.comments;
        } else {
            this.currentRestaurantName = myRestaurantName;
            this.comments = Comment.query({restaurantName: myRestaurantName});
            return this.comments;
        }
    }.bind(this);

    this.addComment = function (ratingValue, ratingText, author) {
        var queryBody = {
            "text": ratingText,
            "restaurant": this.currentRestaurantName,
            "author": author,
            "rating": ratingValue
        };
        Comment.save({restaurantName: this.currentRestaurantName}, queryBody);
        this.comments.push(queryBody);
        $scope.$apply();
    }.bind(this);
};

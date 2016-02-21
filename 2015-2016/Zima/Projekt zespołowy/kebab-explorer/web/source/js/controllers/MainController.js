'use strict';

// @ngInject
module.exports = function ($scope, Restaurant) {

    this.restaurants = Restaurant.query();

    this.shouldShowInfoPanel = false;
    this.currentRestaurantInfo = [];
    this.currentTab = 0;

    this.setTab = function(tabId) {
        this.currentTab = tabId;
    };

    this.isTabSet = function(tabId) {
        return this.currentTab == tabId;
    };

    this.showInfoPanel = function (restaurant) {
        this.shouldShowInfoPanel = true;
        this.currentRestaurantInfo = restaurant;
        $scope.$apply();
    };

    this.hideInfoPanel = function () {
        this.shouldShowInfoPanel = false;
        this.currentRestaurantInfo = [];
        $scope.$apply();
    };

    this.initialMapCenter = {
        latitude: 51.111651,
        longitude: 17.058095
    };

    this.myPosition = {
        latitude: 51.111651,
        longitude: 17.058095
    };

    if (navigator.geolocation) {
        navigator.geolocation.getCurrentPosition(function (position) {
            this.myPosition.latitude = position.coords.latitude;
            this.myPosition.longitude = position.coords.longitude;

            $scope.$apply();
        }.bind(this));
    }

    this.map = {
        center: this.initialMapCenter,
        zoom: 12,
        options: {
            disableDefaultUI: false,
            disableDoubleClickZoom: false,
            draggable: true,
            scrollwheel: true,
            panControl: true,
            enableHighAccuracy: true,
            styles: [{"featureType":"all","elementType":"labels.text.fill","stylers":[{"saturation":36},{"color":"#000000"},{"lightness":40}]},{"featureType":"all","elementType":"labels.text.stroke","stylers":[{"visibility":"on"},{"color":"#000000"},{"lightness":16}]},{"featureType":"all","elementType":"labels.icon","stylers":[{"visibility":"off"}]},{"featureType":"administrative","elementType":"geometry.fill","stylers":[{"color":"#000000"},{"lightness":20}]},{"featureType":"administrative","elementType":"geometry.stroke","stylers":[{"color":"#000000"},{"lightness":17},{"weight":1.2}]},{"featureType":"landscape","elementType":"geometry","stylers":[{"color":"#000000"},{"lightness":20}]},{"featureType":"poi","elementType":"geometry","stylers":[{"color":"#000000"},{"lightness":21}]},{"featureType":"road.highway","elementType":"geometry.fill","stylers":[{"color":"#000000"},{"lightness":17}]},{"featureType":"road.highway","elementType":"geometry.stroke","stylers":[{"color":"#000000"},{"lightness":29},{"weight":0.2}]},{"featureType":"road.arterial","elementType":"geometry","stylers":[{"color":"#000000"},{"lightness":18}]},{"featureType":"road.local","elementType":"geometry","stylers":[{"color":"#000000"},{"lightness":16}]},{"featureType":"transit","elementType":"geometry","stylers":[{"color":"#000000"},{"lightness":19}]},{"featureType":"water","elementType":"geometry","stylers":[{"color":"#0f252e"},{"lightness":17}]}]
        },
        events: {
            click : function (mapModel, eventName, originalEventArgs) {
                this.hideInfoPanel();
                this.setTab(0);
            }.bind(this)
        },
        control: {}
    };


    var directionsDisplay = new google.maps.DirectionsRenderer({suppressMarkers: true});

    this.showDriveInfo = function(_endPosition) {
        this.setTab(3);
        var startPosition = new google.maps.LatLng(this.myPosition.latitude, this.myPosition.longitude);
        var endPosition = new google.maps.LatLng(_endPosition[1], _endPosition[0]);

        var request = {
            origin : startPosition,
            destination : endPosition,
            travelMode : google.maps.TravelMode.DRIVING
        };

        var mapInstance = this.map.control.getGMap();
        var detailedInfo = document.getElementById("drive-info");
        directionsDisplay.setMap(mapInstance);
        directionsDisplay.setPanel(detailedInfo);


        var directionsService = new google.maps.DirectionsService();
        directionsService.route(request, function (response, status) {
            if(status == google.maps.DirectionsStatus.OK) {
                directionsDisplay.setDirections(response);
            }
        });
    }.bind(this);

    $scope.myRadius = 15;
    this.setRadius = function() {
        this.restaurants = Restaurant.query({
            longitude: this.myPosition.longitude,
            latitude: this.myPosition.latitude,
            radius: (1000 * $scope.myRadius)
        });
    };
};

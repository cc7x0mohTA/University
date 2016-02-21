'use strict';

// @ngInject
module.exports = function($http, $timeout, Restaurant, Authentication) {
    var vm = this;

    vm.currentTab = 0;
    vm.dishes = [];
    vm.restaurants = Restaurant.query();

    vm.isTabSet = isTabSet;
    vm.setTab = setTab;
    vm.submitForm = submitForm;
    vm.addDish = addDish;
    vm.addUserPhotos = addUserPhotos;

    init();

    function init() {
        addDish();
    }

    function isTabSet(_id) {
        return vm.currentTab == _id;
    }

    function setTab(_id) {
        vm.currentTab = _id;
    }

    function submitForm() {
        var images = $("#images")[0].files;
        uploadImages(images, sendImgSuccessFn);

        function sendImgSuccessFn(response) {
            addRestaurant(response.data);
        }

    }

    function addRestaurant(_pictures) {
        var location = getLocationFromAddress();
        var name = getNameFromFullname(vm.fullname);

        var newRestaurantData = {
            "address" : {
                "city" : vm.city,
                "postcode" : vm.postcode,
                "street" : vm.street
            },
            "email" : vm.email,
            "location" : location,
            "fullname" : vm.fullname,
            "name" : name,
            "phone" : [vm.phone],
            "menu" : vm.dishes,
            "pictures" : _pictures
        };

        $timeout(function() {

            $http.post('/api/restaurant/' + name, newRestaurantData).then(
                addSuccessFn,
                addErrorFn
            );

            function addSuccessFn() {
                window.location.reload();
            }

            function addErrorFn(response) {
                alert('Wprowadzono błędne dane!');
                console.log('RESTAURANT ADD ERROR', response);
            }
        }, 1500);
    }

    function getLocationFromAddress() {
        var geocoder = new google.maps.Geocoder();
        var address = vm.street + ',' + vm.city + ', Poland';
        var mylocation = {
            "coordinates" : [],
            "type" : "Point"
        };

        geocoder.geocode({"address" : address}, function(results, status){
            if(status == google.maps.GeocoderStatus.OK) {
                var coords = results[0].geometry.location;

                mylocation.coordinates.push(coords.lng());
                mylocation.coordinates.push(coords.lat());
            }
        });

        return mylocation;
    }

    function getNameFromFullname(_fullname) {
        return _fullname.toLowerCase().split(' ').join('_');
    }

    function addDish() {
        vm.dishes.push({
            "dishName" : "",
            "dishPrice" : ""
        });
    }

    function addUserPhotos() {
        uploadImages($("#userImage")[0].files, success);

        function success(response) {

            var updateData = getUpdateData(response.data[0]);

            $http.put('/api/restaurant/' + vm.chosenRestaurant, updateData).then(
                function () {
                    window.location.reload();
                },
                function(response) {
                    console.log('error', response);
                }
            );
        }
    }

    function getUpdateData(_imageToAdd) {
        var restaurantInfo = vm.restaurants.filter(function(obj) {
            return obj.name == vm.chosenRestaurant;
        })[0];

        var currentData = restaurantInfo.userGallery;

        var newData = [{
            "username" : Authentication.getAuthenticatedAccountLogin(),
            "description" : vm.userPhotoDesc,
            "image" : _imageToAdd
        }];

        if(currentData == undefined) {
            return {"userGallery" : newData};
        }
        else {
            return {"userGallery" : currentData.concat(newData)};
        }
    }

    function uploadImages(__images, __successFn) {
        var fd = new FormData();

        for(var i = 0; i < __images.length; i++) {
            fd.append("images", __images[i]);
        }

        $http.post('/images/', fd, {
            withCredentials: true,
            transformRequest: angular.identity,
            headers: {'Content-Type': undefined}
        }).then(__successFn, function (response) {
            console.log('Error sending photos', response);
        });
    }

};
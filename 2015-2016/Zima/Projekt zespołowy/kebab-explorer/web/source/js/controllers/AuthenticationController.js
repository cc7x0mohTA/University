'use strict';

// @ngInject
module.exports = function ($location, Authentication, User, $q, $scope, $timeout) {
    var SUCCESS_URL = '/',
        PROFILE_URL = '/profile/',
        vm = this;

    vm.isAuthenticated = Authentication.isAuthenticated;
    vm.getLogin = Authentication.getAuthenticatedAccountLogin;
    vm.login = login;
    vm.logout = logout;
    vm.gotoProfile = gotoProfile;
    vm.showRegisterPanel = showRegisterPanel;
    vm.register = register;

    activate();

    function showRegisterPanel() {
        $('#registrationPanel').modal('show');
    }

    function register() {
        var newUserData = {
            login: vm.mylogin,
            password_hash: vm.password,
            fullname: vm.fullname,
            email: vm.email,
            city: vm.city,
            age: vm.age
        };

        function registerSuccessFn() {
            window.location.reload();
        }

        function registerErrorFn(response) {
            alert('Wprowadzono błędne dane!');
            console.log('REGISTER ERROR', response);
        }

        Authentication.register(vm.mylogin, newUserData).then(
            registerSuccessFn,
            registerErrorFn
        );
    }

    function login() {
        function loginSuccessFn() {
            $location.url(SUCCESS_URL);
            window.location.reload();
        }

        function loginErrorFn(response) {
            console.log('LOGIN CONTROLLER ERROR', response);
        }

        Authentication.login(vm.email, vm.password).then(
            loginSuccessFn,
            loginErrorFn
        );
    }

    function logout() {
        Authentication.logout();
        $location.url(SUCCESS_URL);
    }

    function activate() {
        $timeout(function () {
            getUserInfo();
        }, 1000);
    }

    function setInfo(_info) {
        $scope.userInfo = {
            login: _info.login,
            fullname: _info.fullname,
            email: _info.email,
            city: _info.city,
            age: _info.age
        };
    }

    function getUserInfo() {
        if (vm.isAuthenticated()) {
            var currentUserLogin = Authentication.getAuthenticatedAccountLogin();
            User.get({userLogin: currentUserLogin}).$promise.then(function (response) {
                return $q(function successInfoGet(resolve) {
                    setInfo(response);
                    resolve(response);
                });
            });
        }
    }

    function gotoProfile() {
        $location.url(PROFILE_URL);
        $('#userPanel').modal('show');
    }
};

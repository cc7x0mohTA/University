'use strict';

// @ngInject
module.exports = function ($cookies, $http, $q) {

    var TOKEN_COOKIE_KEY = 'kebab-explorer-login-cookie',
        LOGIN_COOKIE_KEY = 'kebab-explorer-user-info-cookie',
        DEFAULT_EXPIRE_TIME = 1;

    function setAuthenticatedAccountDetails(_account) {
        var now = new Date(), expires = new Date();

        expires.setDate(now.getDate() + DEFAULT_EXPIRE_TIME);

        $cookies.put(LOGIN_COOKIE_KEY, _account.login, {
            expires: expires
        });
    }

    function unauthenticate() {
        $cookies.remove(TOKEN_COOKIE_KEY);
        $cookies.remove(LOGIN_COOKIE_KEY);
    }

    return {
        register: function (mylogin, queryBody) {
            return $http.post('/api/user/' + mylogin, queryBody);
            // TODO: Change API query params names
        },

        login: function (email, password) {
            function loginSuccessFn(response) {
                return $q(function (resolve) {
                    setAuthenticatedAccountDetails(response.data);
                    resolve(response);
                });
            }

            return $http.post(
                '/api/login/',
                {
                    // TODO: Change API to use POST data
                    userLogin: email,
                    passwordHash: password
                },
                {
                    params: {
                        userLogin: email,
                        passwordHash: password
                    }
                }
            ).then(loginSuccessFn);
        },

        logout: function () {
            function logoutSuccessFn(response) {
                return $q(function (resolve) {
                    unauthenticate();
                    resolve(response);
                });
            }

            return $http.post('/api/logout/', {})
                .then(logoutSuccessFn);
        },

        isAuthenticated: function () {
            return !!$cookies.get(TOKEN_COOKIE_KEY);
        },

        getAuthenticatedAccountLogin: function () {
            return $cookies.get(LOGIN_COOKIE_KEY);
        }
    };
};

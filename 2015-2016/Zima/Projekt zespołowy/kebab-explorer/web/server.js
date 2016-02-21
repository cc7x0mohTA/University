'use strict';

var _ = require('lodash'),
    express = require('express'),
    app = express(),
    bodyParser = require('body-parser');

var helpers = {
    generateRestaurant: (function () {
        var lat = 51.111651,
            lng = 17.058095,
            counter = 1;

        function randomDislocation() {
            return Math.sin(Math.random() * 100) / 100;
        }

        return function () {
            var number = counter++;
            return {
                id: 'restaurant-' + number,
                name: 'Restauracja ' + number,
                fullname: 'Restauracja ' + number,
                description: 'Opis ' + number,
                phone: ['123 456 789'],
                address: {
                    street: 'Plac Grunwaldzki',
                    postcode: '00-000',
                    city: 'Wrocław'
                },
                location: {
                    coordinates: [lng + randomDislocation(), lat + randomDislocation()]
                }
            }
        };
    }()),

    generateUser: (function () {
        var counter = 1;

        return function () {
            var number = counter++;
            return {
                email: 'user' + number + '@example.com',
                password: 'user' + number,
                name: 'Użytkownik ' + number
            }
        };
    })
};

var SERVER_PORT = 8080;

var DB = {
    'restaurants': {},
    'users': {},
    'comments': {}
};

// Populate database with dummy data
DB.restaurants = _.indexBy(Array.apply(null, new Array(7)).map(helpers.generateRestaurant), 'id');
DB.users = _.indexBy(Array.apply(null, new Array(3)).map(helpers.generateUser), 'email');


app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use('/', express.static(__dirname + '/dist'));

app.post('/api/user/', function (req, res) {
    var email = req.body.email,
        password = req.body.password;

    if (DB.users[email]) {
        res.status(409).json({
            'status': 'error',
            'message': 'Account already exists.'
        });
        return;
    }

    DB.users[email] = {
        'email': email,
        'password': password
    };

    res.status(201).json({
        'status': 'success',
        'message': 'Account successfully created.'
    });
});

app.post('/api/login/', function (req, res) {
    var email = req.body.login,
        password = req.body.password;

    if (DB.users[email]) {
        if (DB.users[email].password === password) {
            res.json({
                'status': 'success',
                'message': 'Successfuly logged in.',
                'account': DB.users[email]
            });
            return;
        }
    }

    res.status(401).json({
        'status': 'error',
        'message': 'Wrong user credentials.'
    });
});

app.get('/api/restaurant/', function (req, res) {
    res.json(_.values(DB.restaurants));
});

app.get('/api/comment/', function (req, res) {
    res.json(_.values(DB.comments));
});

app.post('/api/comment/', function (req, res) {
    var restaurantId = req.body.restaurantId,
        userId = req.body.userId,
        comment = req.body.comment;

    if (DB.comments[restaurantId] === undefined) {
        DB.comments[restaurantId] = [];
    }
    DB.comments[restaurantId].push({
        'user': userId,
        'comment': comment
    });

    res.status(201).json({
        'status': 'success',
        'message': 'Comment successfully added.'
    });
});

var server = app.listen(SERVER_PORT, function () {
    var host = server.address().address,
        port = server.address().port;

    console.log('Server listening at http://%s:%s', host, port);
});

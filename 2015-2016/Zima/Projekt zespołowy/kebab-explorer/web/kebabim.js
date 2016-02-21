'use strict';

var path = require('path'),
    _ = require('lodash'),
    uuid = require('node-uuid'),
    express = require('express'),
    app = express(),
    multer  = require('multer');

var SERVER_PORT = 8888,
    UPLOADS_DIR = __dirname + '/uploads';

var storage = multer.diskStorage({
        destination: function (req, file, cb) {
            cb(null, UPLOADS_DIR);
        },
        filename: function (req, file, cb) {
            cb(null, uuid.v4() + path.extname(file.originalname));
        }
    }),
    upload = multer({ storage: storage });

app.use('/images', express.static(UPLOADS_DIR));

app.post('/images', upload.array('images', 12), function (req, res) {
    var savedImages = _.map(req.files, function (file) {
        return '/images/' + file.filename;
    });

    res.status(200).json(savedImages);
});

var server = app.listen(SERVER_PORT, function () {
    var host = server.address().address,
        port = server.address().port;

    console.log('Server listening at http://%s:%s', host, port);
});

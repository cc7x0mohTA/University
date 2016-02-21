var gulp = require('gulp'),
    gulpUtil = require('gulp-util'),
    gulpIf = require('gulp-if'),
    gulpDebug  = require('gulp-debug'),
    gulpJshint = require('gulp-jshint'),
    gulpSourcemaps = require('gulp-sourcemaps'),
    gulpSass = require('gulp-sass'),
    gulpUglify = require('gulp-uglify'),
    gulpWebserver = require('gulp-webserver'),

    del = require('del'),
    vinylSourceStream = require('vinyl-source-stream'),
    vinylBuffer = require('vinyl-buffer'),

    browserify = require('browserify'),
    ngAnnotate = require('browserify-ngannotate'),

    config = {
        "build": {
            "directory": "dist"
        },
        "html": {
            "files": ["source/**/*.html"],
            "base": "source/",
            "dest": "dist/"
        },
        "img": {
            "directory": ["source/img/**"],
            "dest": "dist/img"
        },
        "vendor": {
            "directory": ["bower_components/**"],
            "dest": "dist/vendor"
        },
        "sass": {
            "files": ["source/scss/**/*.scss"],
            "base": "source/scss/",
            "dest": "dist/css/"
        },
        "browserify": {
            "files": "source/js/**/*.js",
            "entries": "source/js/app.js",
            "paths": [
                "source/js/controllers",
                "source/js/services",
                "source/js/directives"
            ],
            "bundle": "app.js",
            "dest": "dist/js/"
        },
        "webserver": {
            "dest": "dist/",
            "host": "0.0.0.0",
            "port": 8000,
            "livereload": true,
            "apiUrl": (gulpUtil.env.API_URL || "http://127.0.0.1:8080").replace(/\/+$/, "")
        }
    };

var PRODUCTION = (gulpUtil.env.production === true),
    VERBOSE = true;


gulp.task('clean', function () {
    return del.sync([config.build.directory]);
});

gulp.task('install', function () {
    var install = require('gulp-install');

    return gulp.src(['./bower.json', './package.json'])
        .pipe(install({production: PRODUCTION}));
});

gulp.task('jshint', function () {
    return gulp.src(config.browserify.files)
        .pipe(gulpJshint())
        .pipe(gulpJshint.reporter('default'));
});

gulp.task('html', function () {
    return gulp.src(config.html.files, {base: config.html.base})
        .pipe(gulpIf(VERBOSE, gulpDebug({title: 'html:'})))
        .pipe(gulp.dest(config.html.dest));
});

gulp.task('html:watch', function () {
    return gulp.watch(config.html.files, ['html']);
});

gulp.task('img', function () {
    return gulp.src(config.img.directory)
        .pipe(gulpIf(VERBOSE, gulpDebug({title: 'img:'})))
        .pipe(gulp.dest(config.img.dest));
});

gulp.task('sass', function () {
    return gulp.src(config.sass.files, {base: config.sass.base})
        .pipe(gulpIf(VERBOSE, gulpDebug({title: 'sass:'})))
        .pipe(gulpIf(!PRODUCTION, gulpSourcemaps.init()))
            .pipe(gulpSass().on('error', gulpSass.logError))
        .pipe(gulpIf(!PRODUCTION, gulpSourcemaps.write()))
        .pipe(gulp.dest(config.sass.dest));
});

gulp.task('sass:watch', function () {
    return gulp.watch(config.sass.files, ['sass']);
});

gulp.task('browserify', function () {
    var b = browserify({
        entries: config.browserify.entries,
        debug: true,
        paths: config.browserify.paths,
        transform: [ngAnnotate]
    });

    return b.bundle()
        .pipe(vinylSourceStream(config.browserify.bundle))
        .pipe(vinylBuffer())
        .pipe(gulpSourcemaps.init({loadMaps: true}))
            .pipe(gulpUglify())
            .on('error', gulpUtil.log)
        .pipe(gulpSourcemaps.write('./'))
        .pipe(gulp.dest(config.browserify.dest));
});

gulp.task('browserify:watch', function () {
    return gulp.watch(config.browserify.files, ['browserify']);
});

gulp.task('vendor', function () {
    return gulp.src(config.vendor.directory)
        .pipe(gulpIf(VERBOSE, gulpDebug({title: 'vendor:'})))
        .pipe(gulp.dest(config.vendor.dest));
});

gulp.task('build', ['clean', 'html', 'img', 'sass', 'browserify', 'vendor']);

gulp.task('watch', ['html:watch', 'sass:watch', 'browserify:watch']);

gulp.task('webserver', function () {
    return gulp.src(config.webserver.dest)
        .pipe(gulpWebserver({
            host: config.webserver.host,
            port: config.webserver.port,
            livereload: config.webserver.livereload,
            proxies: [
                {source: '/api/user/', target: config.webserver.apiUrl + '/user/'},
                {source: '/api/login/', target: config.webserver.apiUrl + '/login/'},
                {source: '/api/logout/', target: config.webserver.apiUrl + '/logout/'},
                {source: '/api/restaurant/', target: config.webserver.apiUrl + '/restaurant/'},
                {source: '/api/user/', target: config.webserver.apiUrl + '/user/'},
                {source: '/api/comment/', target: config.webserver.apiUrl + '/comment/'},
                {source: '/images/', target: 'http://127.0.0.1:8888/images/'}
            ]
        }));
});

gulp.task('webserver:live', ['watch', 'webserver']);

gulp.task('default', ['build']);

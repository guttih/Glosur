#How to minify ecmascript 6 files and jshint them
Jubb


## install gulp and requred modules
cd into you project
```
npm init
npm install -g gulp
npm install --save-dev gulp gulp-babel babel-preset-es2015 gulp-concat gulp-uglify gulp-jshint jshint jshint-stylish

```

#####Files in project folder before beginning
```
.
+--src/
    +--barn.js
    +--main.js
    +--pabbi.js
+--js/
    +--app.js
    +--objects.js
+--index.html
```

#####Gulp file
This gulpfile will run two tasks by default "jshint" and "makeBuild"
jshint uses the jshint-stylish reporter, which colorcodes errors making them more readable.
```
var gulp = require('gulp');
    jshint = require('gulp-jshint');
    uglify = require('gulp-uglify'),
    babel = require('gulp-babel'),
    concat = require('gulp-concat');

var sourceFiles = ['src/*.js', '!node_modules/**/*'];

var jsHintOptions = {
        esversion: 6
    };

gulp.task('makeBuild', function () {
    gulp.src(sourceFiles)
        .pipe(babel({
            presets: ['es2015']
        }))
        .pipe(uglify())
        .pipe(concat('js/paint.js'))
        .pipe(gulp.dest('build'))
});

gulp.task('oldjshint', function () {
    gulp.src(sourceFiles)
    .pipe(jshint(jsHintOptions))
    .pipe(jshint.reporter('default'))
});

gulp.task('jshint', () =>
    gulp.src(sourceFiles)
        .pipe(jshint(jsHintOptions))
        .pipe(jshint.reporter('jshint-stylish'))
);

gulp.task('jsHintAndMakebuild', ['jshint', 'makeBuild'])
gulp.task('default', ['jsHintAndMakebuild']);
```

#### Also checkout
#### gulp-load-plugins
[gulp-load-plugins] (https://www.npmjs.com/package/gulp-load-plugins)
example:
```
var gulp = require('gulp'),
	gulpLoadPlugins = require('gulp-load-plugins'),
	plugins = gulpLoadPlugins();

gulp.task('buildit', function () {
	return gulp.src('src/*.js')
		.pipe(plugins.jshint({
			esversion: 6,
			globals: {
				jQuery: true,
				"$": true
			}
		}))
		.pipe(plugins.jshint.reporter('default'))
		.pipe(plugins.babel({
			presets: ['es2015']
		}))
		.pipe(plugins.uglify())
		.pipe(plugins.concat('app.js'))
		.pipe(gulp.dest('build'));
});

gulp.task('default', ['buildit']);
```

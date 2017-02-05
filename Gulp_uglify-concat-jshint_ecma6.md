#How use Gulp to minify, concatenate and verify ecmascript 6 code.
Here is an example on how you could use gulp to verify and combine, your source code files (written in es6 javascript) into one file.


## install gulp and requred modules
cd into you project
```
npm init
npm install -g gulp
npm install --save-dev gulp gulp-babel babel-preset-es2015 gulp-concat gulp-uglify gulp-jshint jshint jshint-stylish

```

#####Project folder structure
I will assume that all your code is in a subfolder called "src" which is located.
```
.
+--gulpfile.js
+--src/
    +--barn.js
    +--main.js
    +--pabbi.js

```

####Gulp file
In the gulpfile listed here belowwill run two tasks by default "jshint" and "makeBuild"
jshint uses the jshint-stylish reporter, which colorcodes errors making them more readable.
- To make jshint check your code type type `gulp jshint`
- To minify and combine all your source files into one file located in the build folder type `gulp makeBuild`
- To run both tasks type `gulp`

#####gulpfile.js
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
        .pipe(concat('js/app.js'))
        .pipe(gulp.dest('build'));
});

gulp.task('oldjshint', function () {
    gulp.src(sourceFiles)
    .pipe(jshint(jsHintOptions))
    .pipe(jshint.reporter('default'));
});

gulp.task('jshint', () =>
    gulp.src(sourceFiles)
        .pipe(jshint(jsHintOptions))
        .pipe(jshint.reporter('jshint-stylish'))
);

gulp.task('jsHintAndMakebuild', ['jshint', 'makeBuild']);
gulp.task('default', ['jsHintAndMakebuild']);
```


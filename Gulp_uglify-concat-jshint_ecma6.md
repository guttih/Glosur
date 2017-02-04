#How to minify ecmascript 6 files
Jubb


## install gulp and requred modules
cd into you project
```
npm install -g gulp
npm install --save-dev gulp

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
```
var gulp = require('gulp');
    jshint = require('gulp-jshint');
    uglify = require('gulp-uglify'),
    babel = require('gulp-babel'),
    concat = require('gulp-concat');

gulp.task('minify', function () {
    gulp.src(['js/*.js', '!node_modules/**/*'])
        .pipe(babel({
            presets: ['es2015']
        }))
        .pipe(uglify())
        .pipe(concat('js/paint.js'))
        .pipe(gulp.dest('build'))
});
```


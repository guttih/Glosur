#How use Gulp to tslint your typescript code
Here is an example on how you could use gulp to verify your typescript source code files.


## install gulp and requred modules
cd into you project
```
npm init
npm install -g gulp
npm install gulp-tslint --save-dev

```

#####Project folder structure
I will assume that all your code is in a subfolder called "src" which is located.
```
.
+--gulpfile.js
+--src/
    +--barn.ts
    +--main.ts
    +--pabbi.ts

```

####Gulp file
The gulpfile shown below has one task called "tslint".
- To make tslint check your code type type `gulp tslint` or just `gulp`

#####gulpfile.js
```
var tslint = require("gulp-tslint");
var gulp = require('gulp');

var sourceFiles = ['src/**/*.ts', '!node_modules/**/*'];

gulp.task("tslint", () =>
    gulp.src(sourceFiles)
        .pipe(tslint({
            formatter: "verbose"
        }))
        .pipe(tslint.report())
);

gulp.task('default', ['tslint']);
```

### tslint.json
In the same directory as the gulpfile.js you will need to have your tslint.json 
file which will contain the rules you want to check your code by.  Below is an example of a content in that file.
```
{
  "rulesDirectory": [
    "node_modules/codelyzer"
  ],
  "rules": {
    "callable-types": true,
    "class-name": true,
    "comment-format": [
      true,
      "check-space"
    ],
    "curly": true,
    "eofline": true,
    "forin": true,
    "import-blacklist": [true, "rxjs"],
    "import-spacing": true,
    "indent": [
      true,
      "spaces"
    ],
    "interface-over-type-literal": true,
    "label-position": true,
    "max-line-length": [
      true,
      140
    ],
    "member-access": false,
    "member-ordering": [
      true,
      "static-before-instance",
      "variables-before-functions"
    ],
    "no-arg": true,
    "no-bitwise": true,
    "no-console": [
      true,
      "debug",
      "info",
      "time",
      "timeEnd",
      "trace"
    ],
    "no-construct": true,
    "no-debugger": true,
    "no-duplicate-variable": true,
    "no-empty": false,
    "no-empty-interface": true,
    "no-eval": true,
    "no-inferrable-types": [true],
    "no-shadowed-variable": true,
    "no-string-literal": false,
    "no-string-throw": true,
    "no-switch-case-fall-through": true,
    "no-trailing-whitespace": true,
    "no-unused-expression": true,
    "no-use-before-declare": true,
    "no-var-keyword": true,
    "object-literal-sort-keys": false,
    "one-line": [
      true,
      "check-open-brace",
      "check-catch",
      "check-else",
      "check-whitespace"
    ],
    "prefer-const": true,
    "quotemark": [
      true,
      "single"
    ],
    "radix": true,
    "semicolon": [
      "always"
    ],
    "triple-equals": [
      true,
      "allow-null-check"
    ],
    "typedef-whitespace": [
      true,
      {
        "call-signature": "nospace",
        "index-signature": "nospace",
        "parameter": "nospace",
        "property-declaration": "nospace",
        "variable-declaration": "nospace"
      }
    ],
    "typeof-compare": true,
    "unified-signatures": true,
    "variable-name": false,
    "whitespace": [
      true,
      "check-branch",
      "check-decl",
      "check-operator",
      "check-separator",
      "check-type"
    ],

    "directive-selector": [true, "attribute", "app", "camelCase"],
    "component-selector": [true, "element", "app", "kebab-case"],
    "use-input-property-decorator": true,
    "use-output-property-decorator": true,
    "use-host-property-decorator": true,
    "no-input-rename": true,
    "no-output-rename": true,
    "use-life-cycle-interface": true,
    "use-pipe-transform-interface": true,
    "component-class-suffix": true,
    "directive-class-suffix": true,
    "no-access-missing-member": true,
    "templates-use-public": true,
    "invoke-injectable": true
  }
}

```


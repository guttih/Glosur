#Grunt#

##jsHint
Quick setup guide to make jsHint review the javascript code in your project.  In order to be able to use grunt you will need to have Nodejs installed.  You can download nodejs from [Here](https://nodejs.org/en/download/)
#####Files in project folder before beginning
```
.
+--css/
    +--style.css
+--js/
    +--app.js
    +--objects.js
+--index.html
```

1. Create the packet.jason file
  * In the root of the project type `npm init` and answer all the questions, note that pressing return will select the default option, and that should be OK for most of the time.
2. Create the Gruntfile.js
  * type `echo " ">>Gruntfile.js`
3. Paste this into the newly created Gruntfile.js
    ```js
    module.exports = function(grunt) {
      // Project configuration.
      grunt.initConfig({
        pkg: grunt.file.readJSON('package.json'),
      jshint: {
        all: ['Gruntfile.js', 'js/*.js', 'test/**/*.js']
      }
      });
      grunt.loadNpmTasks('grunt-contrib-jshint');
    
      // Default task(s).
      grunt.registerTask('default', ['jshint']);
    };
    ```
4. Install grunt into the folder and the jshint plugin
    ```shell
    npm install -g grunt-cli
    npm install grunt-contrib-jshint --save-dev
    npm install grunt --save-dev
    ```    
   
   
    
5. Run grunt with jshint
  * Type `grunt`
  
And lastly here you find a gruntfile with jshint options
```js
module.exports = function(grunt) {
  // Project configuration.
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
  jshint: {
    all: ['Gruntfile.js', 'js/**/*.js'],
	 options: {
				curly:  true,
				immed:  true,
				newcap: true,
				noarg:  true,
				sub:    true,
				boss:   true,
				eqnull: true,
				node:   true,
				undef:  true,
				globals: {
					_:       false,
					jQuery:  false,
					angular: false,
					moment:  false,
					console: false,
					$:       false,
					io:      false
				}
    }
  }
  });
  grunt.loadNpmTasks('grunt-contrib-jshint');

  // Default task(s).
  grunt.registerTask('default', ['jshint']);
};
```

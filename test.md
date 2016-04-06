#Ace project folder
This project could be independent from the centrislms project but it is not.  
To figure out it’s dependencies, you should view the link and script elements in the files index.html and view/index.html.  
Neither a npm nor a bower package has been created because I was unsure on how this project would be simulated to the centrislms.  
When developing the project, the approach was to download the minified versions of external components, 
add them to the bower_components folder and link to them from the html.
###Starting both projects
The same way as you start the centrislms. Go to the root of the centrislms folder and type `gulp`.

###Ace editor - the code viewer.
[The Ace editor](https://ace.c9.io) is a open source project to be able to view and edit code online.  This editor is the core component in these two project to present code. An [angular directive]( https://github.com/angular-ui/ui-ace) was also made and we are using that directive in these projects.

####External Dependencies already imported to centrislms.
This project depends on some dependencies already imported to the centrislms, like "angular", "ui-bootstrap" and "ui-bootstrap-tpls".  
They are imported from the centrislms\src\vendor folder.  
I used these to reduce number of files downloaded to the end user’s browser.

####Two projects – shared files
There are in fact two projects in this folder. "Mooshak code viewer" and the "Code reviewer".  
These two project have different index.html files one located int the root folder and the other one in the "view" subfolder.  
Source code for both projects is located in the src subfolder.  Both projects share the same app called aceApp.  
The subfolders src/view and src/mooshak contain the code specific to each project.  
Code common to both project is in the subfolder src/common.  Both project share files in the subfolder src/styles.

#####Import to Mooshak code viewer into Code reviewer?
Please note that the project Mooshak code viewer was developed before the Code reviewer project so the appearance of 
the Mooshak code viewer will need updating.  Maybe these two projects could be combined to one.  
That is, add the Mooshak part to the Code reviewer project.  And if there is no report to view nothing is shown.  
After all the mooshak-report directive was developed exactly to do things like that.

###Files shared by both projects
####src\app.js
The main application used by both projects.
####src\common\AceFactory.js
A factory with helper function when using the ui-ace directive.  This factory will help you configure and set values to the ace editor it self.  
####src\common\CentrisAceResource.js
This factory has helper function to be used when communication with the centrisApi.
####src\styles\style.css
Styles for both projects.

####notes
The AceFactory.js has a function called supportedFileType which is copied and used by the centrislms when determining 
if an attachment file type is supported or not.

##Mooshak code viewer
This project was created to view code and run-reports from assignments which students hand in to Mooshak.  Mooshak is a server which can be used to verify correct code, review it using predefined programming rules and grade handins from students.  It is not always enough to make Mooshak handle the grading blindly.  A human is usually needed to do the final code review.  This project was created to help with one aspect of that.  The viewing itself.  Three other components were developed before this one could be developed.  CentMoose, a node server running on the Mooshak server.  A plugin-controller on in the the CentrisApi project and a plugin in the cetrislms which talks to the CentrisAPI.

##Launch the Mooshak code viewer
This project will be used by teachers and assistance teachers.  So to use this project you could sign in as dabs.
```
Click the following buttons/links:
  1. "My Courses"
  2. "Human Computer Interaction" (name of a course which dabs teaches)
  3. "Assignments"
  4. "Mooshak vattið" (name of a assignment)
  5. "Grading"
  6. "right arrow" for a group
  7. "Fetch grade"
  8. "Skoða kóða" (forgot translate the button text).
```
##Route and parameters
Example path:
`http://localhost:9000/ace/?contest=lab1&problem=000_vat&groupssn=0207892209,1809873209&courseinstance=24858`

This route will fetch a code and a report from mooshak submitted from a group who has two members with the social security numbers 0207892209 and 1809873209.  This code was submitted to a contest with the name "lab1" and the problem is named 000_vat.  The courseinstance has the id 24858.

###Files specific to the Mooshak code viewer
####src/mooshak/MooshakCodeReview.js 
The controller used to fetch and view code and report from Mooshak about a specific submission.  Controller supplies the report from Mooshak to the mooshak-report directive 	using the $scope variable {{report}}
####src/mooshak/mooshakReport.js
Contains a directive used to display a report automatically generated by Mooshak.  The directive will watch changes on the htmlreport attribute and display data supplied to that attribute.
####src/mooshak/styleMoosakReport.css
Styles to style the actual report from Mooshak, styles can be done better but I would have to get more report examples to be able to do this well.
####index.html
This is a single page app.  One call to this page with parameters will load the code and report.

##Code reviewer
This project was developed to be able to view code handed in by students.  The project will also allow teachers to comment on that code and allow the student to view those comments.  There are many files supported files with syntax highlighting.  You can see the supported file type in thec function supportedFileType located in the AceFactory.js.

##Launch the Mooshak code viewer
This project will be used by teachers and assistance teachers.  So to be able to use this project you could sign in as dabs.
```
Click the following buttons/links:
  1. "My Courses"
  2. "Human Computer Interaction" (name of a course which dabs teaches)
  3. "Assignments"
  4. "Mooshak vattið" (name of a assignment)
  5. "Grading"
  6. "right arrow" for a group
  7. "click one of the red pen buttons.
```
##Route and parameters
Example path:
`http://localhost:9000/ace/view/?courseID=24858&assignmentID=38311&attachmentID=160&handinID=808301`

The query variable names describe the values needed to view an attachment.  But there is one variable name which is worth mentioning and that value is named theme.  By adding &theme=cobalt to the end of the example path above, will select the theme cobalt and show the file with that theme selected.  This variable can be used when a user can save a preferred view to the user settings.  This has not been implemented to centris yet, but when that is done someone should add the users preferred view to the button launching the Code reviewer.

###Files files in the AceFactory.getMode function.
####src/view/CodeReview.js
The controller used to fetch and display code from attachments saved to centris.  The controller also allows teachers to save and load comments about each line.  The student will be able to view these comments also.
####view/index.html
This is a single page app.  One call to this page with parameters will load the code and saved comments about the loaded code.

##All files in the Ace folder.

The codeview project is located in a subfolder of the centrislms (client) part of centris project

```
CENTRIS\CENTRISLMS\ACE
│
├───bower_components
│   ├───ace-builds
│   │   └───src-min-noconflict
│   │           ace.js
│   │         + 28 files assosiated with the ace editor.
│   │
│   ├───angular-toastr
│   │       angular-toastr.min.css
│   │       angular-toastr.min.js
│   │       angular-toastr.tpls.min.js
│   │
│   └───angular-ui-ace
│           ui-ace.min.js
│
├───src
│   │   app.js
│   │
│   ├───common
│   │       AceFactory.js
│   │       CentrisAceResource.js
│   │
│   ├───mooshak
│   │       MooshakCodeReview.js
│   │       mooshakReport.js
│   │       styleMoosakReport.css
│   │
│   ├───styles
│   │       style.css
│   │
│   └───view
│           CodeReview.js
│
└───view
        index.html
```

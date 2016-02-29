#Notes about Markdown 
#Heading \#heading
##Subtitle \#\# subtitle
###second subtitle \#\#\#second subtitle
####third sub \#\#\#\#third sub
#####fourth \#\#\#\#\#fourth sub

##Force linebreak
\<br\>

##Links
\[text\](link)<br>
[Mastering markdown](https://guides.github.com/features/mastering-markdown/)
 and
[Syntax highligting](https://support.codebasehq.com/articles/tips-tricks/syntax-highlighting-in-markdown)

##Escape
This: ``` \\ \` \* \_ \{ \} \[ \] \( \) \# \+ \- \. \! ``` returns this: \\ \` \* \_ \{ \} \[ \] \( \) \# \+ \- \. \!

##Code
For showing code for a specific language you start by adding<br>
\`\`\`language<br>
your code here<br>
and end by adding <br>
\`\`\`<br>

\`\`\`shell   <i>(For Command line linux and dos)</i><br>
```shell
cat file.txt
```
\`\`\`js <i>(For JavaScript)</i><br>
```js
var s = "JavaScript syntax highlighting";
for(int i = 0 ; i<10; i++){
 console.log("item " + i + " = " + arr[i]);
}
```
\`\`\`cpp <i>(For cpp)</i>
```cpp
for(int i = 0 ; i<10; i++)
 printf("item %i = %s", i, arr[i]);

```
\`\`\`cs <i> or </i> \`\`\`csharp <i>(For C# )</i>
```cs
Console.WriteLine("Fenced code blocks ftw!");
private void index(){ MessageBox.Show("hello world"); }
```

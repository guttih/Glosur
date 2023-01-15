# RegEx notes

My notes about RegEx

Quick start
 - `[ ] ^ !-` are special characters which will need to be escaped when you want to match them.
 - `[` character, a-z, 0-9, a-... `]` , example `[a-z]` all that match lowercase
 character and `[A-Z]` or both `[a-zA-Z]` do not use `[A-z]` because it will
 include many other symbols.  See [ascii table](http://www.asciitable.com/)
 - `*`, example match all that has one upper case character and something after that: `[A-Z]*`




## RegEx and Glob in bash

Glob matches a filename or file path but RegEx matches any text.  
Don't confuse the both, even though expressions can look similar.

To explain the difference let's create four files in a new directory by running these commands from the terminal:
```shell
mkdir tmp
cd tmp
touch {f,F}ile{1..20}.{jpg,tgz,jpg,txt}
touch 'file^.txt' 'file[.txt' 'file^.txt' 'file .txt' 'file*.txt' 'file-.txt' 'file.txt'
```
Now, let's list three of these files, first with a *Glob* and then with *RegEx*.  
*Note `ls` command does not understand *RexEx* but `grep` does.*

listing three existing files in current directory:
- *Glob* command `ls file?[1-2].txt` will make the shell translate the following to the `ls` command:
    ```shell
    ls file11.txt  file12.txt
    ```
- *RegEx* command: `ls | grep 'file.[1-2].*\.txt'` will list all four files in 
current directory and then `grep` will execute the *RegEx* command on the output
from the `ls` command resulting in listing same two files as from the *Glob* command above.

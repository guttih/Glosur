# RegEx notes

My notes about RegEx

Quick start
 - `[ ] ^ !- \` are special characters which will need to be escaped when you want to match them.
 - `[` character set `]` , example `[a-z]` all that match lowercase
 character and `[A-Z]` or both `[a-zA-Z]` do not use `[A-z]` because it will
 include many other symbols.  See [ascii table](http://www.asciitable.com/)
 - `*`, example match all that has one upper case character and something after that: `[A-Z]*`
 - `[^` match `]`, negate everything inside the square brackets.  Example match
 everything that does not have one upper case character and something after that: `[A-Z]*`

 RegEx examples:
  - `file.\.txt`Match filenames that have one character between *file* and *.txt* 
  e.g. matching glob `file?.txt`.  Grep example: `ls|grep 'file.\.txt'`
  - `file[^a-z]\.txt` Match filenames that have one character between *file* and *.txt*
   that do not have lower case characters.


### Shorthand character sets

Warning, old expressions do not support all these shorthands.

| Shorthand | Meaning            | Equivalent    |
|----------:| ------------------ | --------------|
|       \d  | Digit              | [0-9]         |
|       \D  | Not digit          | [^0-9]        |
|       \w  | Word character     | [a-zA-Z0-9_]  |
|       \W  | Not word character | [^a-zA-Z0-9_] |
|       \s  | Whitespace         | [\t\r\n]      |
|       \S  | Not whitespace     | [^\t\r\n]     |

### Repetition meta characters

| meta character | Meaning                            |
|---------------:| -----------------------------------|
|              * | Preceding item, zero or more times |
|              + | Preceding item, one or more times  |
|              ? | Preceding item, zero or one times  |

Examples:
 - `.+` - Matches any string of characters except a line return.
 



## RegEx and Glob in bash

Glob matches a filename or file path but RegEx matches any text.  
Don't confuse the both, even though the expressions can look similar.

To explain the difference let's create four files in a new directory by running these commands from the terminal:
```shell
mkdir tmp
cd tmp
touch {f,F}ile{1..22}.{jpg,tgz,jpg,txt}
touch 'file^.txt' 'file[.txt' 'file^.txt' 'file .txt' 'file*.txt' 'file-.txt' 'file.txt'
```
Now, let's list four of these files, first with a *Glob* and then with *RegEx*.  
*Note `ls` command does not understand *RexEx* but `grep` does.*

listing two existing files in current directory:
- *Glob* command: `ls file?[1-2].txt` will make the shell translate the following to the `ls` command:
    ```shell
    ls file11.txt  file12.txt  file21.txt  file22.txt
    ```
- *RegEx* command: `ls | grep 'file.[1-2].*\.txt'` will list all files in 
current directory and then, will `grep` execute the *RegEx* command on the output
from the `ls` command,  resulting in listing same four files as from the *Glob* command above.

## Glob in bash

File Globs: Character classes
- `[:lower:]`  - Lower case characters
- `[:upper:]`  - Upper case characters
- `[:digit:]`  - Numbers
- `[:alpha:]`  - Upper and low case
- `[:alnum:]`  - Upper and lower case plus numbers
- `[:space:]`  - spaces, tabs and newline
- `[:graph:]`  - Printable characters *NOT* including spaces
- `[:print:]`  - Printable characters including spaces
- `[:punct:]`  - Punctuation (a set of symbols used to separate and clarify the 
                 meaning of sentences and written elements)
- `[:cntrl:]`  - Non-printable control characters
- `[:xdigit:]` - Hexadecimal characters

Examples:
- `file[[:alnum:][:punct:]].txt`:Match filenames have the following between
    *file* and *.txt* : 
     - one *character or a letter* or
     - is a punctuation
- `file[![:alnum:][:punct:]].txt`:Does not match filenames have the following between
    *file* and *.txt* : 
     - one *character or a letter* or
     - is a punctuation

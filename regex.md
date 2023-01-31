# RegEx notes

My notes about RegEx

Quick start
 - `[ ] ^ !- \` are special characters which will need to be escaped when you want to match them.
 - `[` character set `]` , example `[a-z]` all that match lowercase
 character and `[A-Z]` or both `[a-zA-Z]` do not use `[A-z]` because it will
 include many other symbols.  See [ascii table](http://www.asciitable.com/)
 - `*`, example match all that has one upper case character and something after that: `[A-Z]*`
 - `[^` match `]`, negate everything inside the square brackets.  Example match
 everything that does not have one upper case character and something after that: `[^A-Z]*`

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

| Meta character | Meaning                            |
|---------------:| -----------------------------------|
|              * | Preceding item, zero or more times |
|              + | Preceding item, one or more times  |
|              ? | Preceding item, zero or one times  |

**Example**:
 - `.+` Matches any string of characters except a line return.


### Anchors
#### Start and End Anchors

 Reference a position, not an actual character

| Meta character | Meaning                            | Suppored by      |
|---------------:| -----------------------------------| :--------------: |
|              ^ | Start of string/line               | Javascript,*PCRE* |
|              $ | End of a string/line               | Javascript,*PCRE* |
|             \A | Start of string, never end of line | Javascript       |
|             \Z | End of string, never end of line   | Javascript       |

*PCRE* - Perl compatible regular expression
*Examples*
 - `^[aA]pple`   - Would match string/line starting with *apple* or *Apple*
 - `\A[aA]pple`   - Would match string starting with *apple* or *Apple* 

#### Word Boundaries Anchors

 Reference a position, not an actual character.

| Meta character | Meaning                                 |
|---------------:| ----------------------------------------|
|              \b | Word boundary (start/end of word)      |
|              \B | Not a world boundary (opposite to \b ) |

Word boundaries exist:
 - Before the first word character in the string
 - After the last word character in the string
 - Between a word character and a non-word character

 **Example**:

 - `\b\w+es\b` Match words that end with **es**.

Where word character are: `[A-Za-z0-9_]`

 ### Quantified Repetition
 `{min,max}` Where min and max are positive numbers.  *Min* must always be included and can be zero.  *Max* is optional.

 **Three syntaxes**
  - `\d{4,8}` - Matches numbers with four to eight digits.
  - `\d{4}`   - Matches numbers with excactly four digits. (min is max).
  - `\d{4,}` - Matches numbers with four or more digits. (max is infinite).


 ### Lookahead and Lookbehind Assertions

Think of this as more detailed search but you cannot use selected groups.
Remember that most engines do not allow lookbehind assertions of variable width.


| Shorthand | Meaning                      |
|:---------- | --------------------------- |
| (?=match)  | Look ahead match            |
| (?!match)  | Negative Look ahead match   |
| (?<=match)  | Look behind match          |
| (?<!match)  | Negative Look behind match |


**Examples**
- Check if a string has at least- one upper case, one lower case, one digit and one 
  symbol and 10 characters long.
  - `\A(?=.*[A-Z])(?=.*[a-z])(?=.*\d)(?=.*[!@#$%^&*]).{10,}\Z`


------------------------------------------------------------------------------------

<center>                                  BASH                             </center>

------------------------------------------------------------------------------------

## RegEx and Glob in bash

Glob matches a filename or file path but RegEx matches any text.  
Don't confuse the both, even though the expressions can look similar.

To explain the difference let's create 132+4=138 files files in a new directory by running these commands from the terminal:
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


### Glob in bash

#### File Globs: Character classes
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


### References

- [Comparison of regular expression engines]
- [RegexBuddy]
- Cources
    - [Learning Regular Expressions]
    - [Bash Patterns and Regular Expressions]

[Comparison of regular expression engines]:https://en.wikipedia.org/wiki/Comparison_of_regular_expression_engines
[Bash Patterns and Regular Expressions]:   https://www.linkedin.com/learning/bash-patterns-and-regular-expressions/
[Learning Regular Expressions]:https://www.linkedin.com/learning/learning-regular-expressions-15586553
[RegexBuddy]: https://www.regular-expressions.info/refbasic.html
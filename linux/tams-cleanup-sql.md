# MySql notes

Some notes on MySql for linux

## Shell commands

**Directly from the shell**
- `su -` Be user root to execute MySql commands 
- `mysql;` Launch MySql editor
- `mysql -uroot -D tamsLog -e "select * from ConnectionStatus where time >= '2023-01-09';"`


## Inside sql editor
- `show databases;` Show all MySql databases
- `use <database_name>;` Select database to do actions on
- `show tables;` Show all tables in selected database
- `show tables;` Show all tables in selected database
- `select * from ConnectionStatus where time < "2023-01-09";` list records before 2023-01-09


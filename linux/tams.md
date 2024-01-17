# Linux commands

## Monitor files
Monitor changes in all files and subdirectories of a specific folder
```shell
sudo find /var/log/tams -type f -print0 | xargs -0 sudo tail -f
```

Monitor the journalctl for a spesific application
```shell
journalctl | grep 'workstation'
```

## MySql notes

Some notes on MySql for linux

### Shell commands

**Directly from the shell**
- `su -` Be user root to execute MySql commands 
- `mysql;` Launch MySql editor
- `mysql -uroot -D tamsLog -e "select * from ConnectionStatus where time >= '2023-01-09';"`


### Inside sql editor
- `show databases;` Show all MySql databases
- `use <database_name>;` Select database to do actions on
- `show tables;` Show all tables in selected database
- `show tables;` Show all tables in selected database
- `select * from ConnectionStatus where time < "2023-01-09";` list records before 2023-01-09


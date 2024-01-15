### My Sql commands

- `show databases;` List all databases
- `show tables;` List all tables in seleccted database
- `select * from users limit 30` - List first 30 records in users table

### some mysql examples
### shell examples

##### List top 20 records in messages table as root user in database tamsLog
```shell
mysql -D tamsLog -e "select * from Message LIMIT 20"
```


You ust always start the mysql (here as root user)
```shell
su -
mysql
```

then you can give some of these commands
```sql
show databases;
use tamsConfig;
show tables;
select * from UploadSettings;
select * from UploadSettings where hostAddressList in ("tams-server-2", "tams-server-amhs-3");
delete from UploadSettings where hostAddressList in ("tams-server-2", "tams-server-amhs-3");
quit
```

### Open a spesific database
```shell
su -
mysql -D tamsConfig;
```

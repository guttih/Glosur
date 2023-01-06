# Chron notes

Notes on chron jobs

### Adding a job

#### Using Crontab

**Adding a job**

1. Open the editor with `crontab -e`
2. Add the job, one job, one line using the chron job syntax described below

**Other Crontab actions**

 - List cron jobs for current logged in user `crontab -l`
 - List cron jobs for specific user `crontab -l -u <username>`
 - Remove cron jobs for current logged in user `crontab -r`
 - Remove cron jobs for a specific user : `crontab -r -u <username>`



### Chron job syntax


#### M H D Mo W format
```
M H D Mo W /path/to/script
| | | |  | 
| | | |   \
| | |  \   W = Day of week (0 to 6 .. 0 = Sunday)  
| |  \  Mo = Month (01 to 12)
|  \  D = Day of month (01 to 31)
 \  H = Hour (00 to 23)
  M = Minute (00 to 59)
```

**Further more** 
 - Use * to imply every hour, day, etc.
 - Use - to span hours, days, etc.


#### variables

or refix path to script with these keywords
- @yearly - execute script every year
- @monthly - execute script every month
- @weekly - execute script every week
- @daily - execute script every day
- @hourly - execute script every hour
- @reboot - execute script every reboot

#### Examples using chron job syntax

Using the **variables** or the **M H D Mo W format**
 
 - Executes '/root/scriptfile.sh' on June 15th at 2:30AM
   ```
   30 02 15 6 * /root/scriptfile.sh
   ```
- Executes '/root/scriptfile.sh' every Sunday at 2:30AM
   ```
   30 02 * * 0 /root/scriptfile.sh
   ```
- Executes '/root/scriptfile.sh' on June 15th at 2:30AM and 2:30PM
   ```
   30 02,14 15 6 * /root/scriptfile.sh
   ```
- Executes '/root/scriptfile.sh' every Sunday at 2:30AM, 3:30AM, 4:30AM, and 5:30AM
   ```
   30 02-05 * * 0 /root/scriptfile.sh
   ```
- Executes '/root/scriptfile.sh' every weekday ath midnight
   ```
   0 0 * * 1-5 /root/scriptfile.sh
   ```

- Executes '/root/scriptfile.sh' on the first day of every month
   ```
   @monthly /root/scriptfile.sh
   ```





See also about cron: 
[IBM], [dell support], [admins choice]


[IBM]: https://www.ibm.com/docs/en/db2oc?topic=task-unix-cron-format
[dell support]: https://www.dell.com/support/kbdoc/en-is/000177157/how-to-configure-cron-jobs-on-redhat-enterprise-linux-rhel-6#issue1
[admins choice]: https://www.adminschoice.com/crontab-quick-reference
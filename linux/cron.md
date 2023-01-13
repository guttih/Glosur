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
 - Remove cron jobs for a specific user `crontab -r -u <username>`
 - cat the actual file for current user `sudo cat /var/spool/cron/$USER`
 - cat the actual file for a specific user `sudo cat /var/spool/cron/<username>`

### Chron job syntax


**Calculate interval of jobs** [Online Expression](https://cronexpressiontogo.com/every-odd-minute)

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
 - Use `*` to imply every hour, day, etc.
 - Use `-` to span hours, days, etc.
 - Use `1-59/2` for every odd something
 - Use `*/2` for every even something


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
 
 - Executes `/root/scriptfile.sh` on June 15th at 2:30AM
   ```
   30 02 15 6 * /root/scriptfile.sh
   ```
- Executes `/root/scriptfile.sh` every Sunday at 2:30AM
   ```
   30 02 * * 0 /root/scriptfile.sh
   ```
- Executes `/root/scriptfile.sh` on June 15th at 2:30AM and 2:30PM
   ```
   30 02,14 15 6 * /root/scriptfile.sh
   ```
- Executes `/root/scriptfile.sh` every Sunday at 2:30AM, 3:30AM, 4:30AM, and 5:30AM
   ```
   30 02-05 * * 0 /root/scriptfile.sh
   ```
- Executes `/root/scriptfile.sh` every weekday ath midnight
   ```
   0 0 * * 1-5 /root/scriptfile.sh
   ```
- Executes `/root/scriptfile.sh` every odd minutes
   ```
   1-59/2 * * * * /root/scriptfile.sh
   ```
- Executes `/root/scriptfile.sh` every even minutes
   ```
   */2 * * * * /root/scriptfile.sh
   ```

- Executes `/root/scriptfile.sh` on the first day of every month
   ```
   @monthly /root/scriptfile.sh
   ```
- Executes `/root/scriptfile.sh` last day of each month at 15:20
   ```
   20 15 28-31 * * [ "$(date +\%d -d tomorrow)" = "01" ]  && /root/scriptfile.sh
   ```
- Log time and text to a file every odd and even minute
   ```
   DATEVAR=date +%Y-%m-%dT%H:%M:%S
   1-59/2 * * * * echo "$($DATEVAR) every other odd  minute">>$HOME/cron.log 
   */2    * * * * echo "$($DATEVAR) every other even minute">>$HOME/cron.log 
   ```
   - Example of a text that would be added to the file `cron.log`
      ```
      2023-01-13T11:23:01 every other odd  minute
      2023-01-13T11:24:01 every other even minute
      ```
- A number of jobs which add text to a log file to test how things work
   ```
   DATEVAR=date +%Y-%m-%dT%H:%M:%S
   1-59/2    *  * * * echo "$($DATEVAR) every other odd  minute"                 >>$HOME/cron.log 
   */2       *  * * * echo "$($DATEVAR) every other even minute"                 >>$HOME/cron.log 
   *         *  * * 1 echo "$($DATEVAR) every monday, every minute"              >>$HOME/cron.log
   00       10  * * 2 echo "$($DATEVAR) every tuesday at 10:00                   >>$HOME/cron.log 
   *        13  * * 3 echo "$($DATEVAR) every wednesday, every minute at 13:xx"  >>$HOME/cron.log
   10       13  * * 3 echo "$($DATEVAR) every thursday at 13:10"                 >>$HOME/cron.log
   0-59/5 8-18/2 * * 1-5 echo "$($DATEVAR) every 5 minute where first minute is 0 and last minute is 55 on even hour on workdays where first hour is 8 and last hour is 18">>$HOME/cron.log
   10  8-18/2 * * 0,6 echo "$($DATEVAR) every even hour on minute 10, on saturdays and sundays where first hour is 8 and last hour is 18">>$HOME/cron.log
   10    13 28-31 * * [[ "$(date --date=tomorrow +\%d)" == "01" ]] &&  echo "$($DATEVAR) Last day of month at 13:10">>$HOME/cron.log
   ```




See also about cron: 
[IBM], [dell support], [admins choice]


[IBM]: https://www.ibm.com/docs/en/db2oc?topic=task-unix-cron-format
[dell support]: https://www.dell.com/support/kbdoc/en-is/000177157/how-to-configure-cron-jobs-on-redhat-enterprise-linux-rhel-6#issue1
[admins choice]: https://www.adminschoice.com/crontab-quick-reference
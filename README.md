# Prismatik_Daemon
This daemon application will read main.conf from C:\\Users\\user_name\\Prismatik\\ to get the configured COM port

Then the Prismatic_Deamon.exe will keep running in the backgroud to monitor the COM status.
When the COM becomes idle, probably after a system sleep/use power down(my LED is powered by my monitor, for example), the daemon will sense that and then automatically restart Prismatik to reconnect your LED.

the Prismatik_Damon_debug.exe version will show the console window for your information.

User "taskkill /im Prismatik_Daemon.exe /F" to kill the background task

Thanks to @Benhoyt 's ini parser.

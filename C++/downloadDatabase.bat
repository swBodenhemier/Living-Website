REM MySQL Connection Details
set DB_HOST=
set DB_PORT=3306
set DB_USER=
set DB_PASS=
set DB_NAME=

REM MySQL Query
set QUERY=SELECT * FROM Object;

REM Output File
set OUTPUT_FILE=output.csv

REM Change directories
cd Database Files

REM MySQL Command
mysql -h %DB_HOST% --port=%DB_PORT% -u %DB_USER% -p%DB_PASS% -D %DB_NAME% -e "%QUERY%" | sed s/\t/","/g;s/^/"/;s/$/"/;s/\n//g > output.csv

REM Change directories back to original
cd ..

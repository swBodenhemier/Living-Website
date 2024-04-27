REM MySQL Connection Details
set DB_HOST=mysql.ac.nau.edu
set DB_PORT=3306
set DB_USER=livingwebsite
set DB_PASS=Vv_dckUVIn
set DB_NAME=livingwebsite

REM MySQL Query
set QUERY=SELECT * FROM Object;

REM Output File
set OUTPUT_FILE=output.csv

REM Change directories
cd Database Files

REM MySQL Command
rem mysql -h mysql.ac.nau.edu --port=3306 -u livingwebsite -pVv_dckUVIn -D livingwebsite -e "SELECT * FROM Object;" | sed "s/\t/\",\"/g;s/^/\"/;s/$/\"/;s/\n//" > output.csv
mysql -h %DB_HOST% --port=%DB_PORT% -u %DB_USER% -p%DB_PASS% -D %DB_NAME% -e "%QUERY%" | sed s/\t/","/g;s/^/"/;s/$/"/;s/\n//g > output.csv

REM Change directories back to original
cd ..
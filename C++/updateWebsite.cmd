@echo off
rem Place this file in the same folder as the exe file
echo Generate new HTML files
Living-Website.exe
rem Set the above call to the name of the exe file
echo ======================================================
echo Checking if deployed_website repository exists
cd ../../../../..
rem Change to directory where you want to make the repository
IF exist deployed_website (echo Repo exists) ELSE (echo Repo does not exists, cloning && git clone https://github.com/jk2429/deployed_website)
echo Copying files to deployed_website repository
copy /y source\repos\New HTML Files\* deployed_website
rem Set source filepath
echo -----------------------------------------
cd deployed_website
echo Commit HTML file changes
git checkout pending_changes
git add *.html
git commit -m "Update Nav Bar. AUTOMATIC UPDATE, CHECK FOR ERRORS BEFORE MERGING"
git push origin
echo -----------------------------------------
echo Changes pushed to remote repsitory, changes must be manually merged.

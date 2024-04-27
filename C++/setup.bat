rem Set up all the directories to be ready to download databse items, html files and upload directory to github
if not exist "HTMLFiles" (mkdir "HTMLFiles")
if not exist "deployed_website" (git clone https://github.com/jk2429/deployed_website)
if not exist "Database Files" (mkdir "Database Files")

rem Download HTML files to update into HTMLFiles folder
updateHTMLFiles.bat

rem Download Database items
downloadDatabase.bat
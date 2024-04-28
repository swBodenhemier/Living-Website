rem Change directories to deployed_website
cd deployed_website

rem Commit HTML file changes
echo Pushing updated files to GitHub
git checkout pending_changes
git add *.html
git commit -m "Update navigation bar. AUTOMATIC UPDATE: Check forr errors before merging."
git push origin

cd ..
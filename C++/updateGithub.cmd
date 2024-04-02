@echo off
echo Sync local Living-Website repository
git pull origin
echo TODO: Run C++ Code here to generate new html documents
echo -----------------------------------------
echo Checking if deployed_website repository exists
cd ../..
IF exist deployed_website (echo Repo exists) ELSE (echo Repo does not exists, cloning && git clone https://github.com/jk2429/deployed_website)
echo Copying files to deployed_website repository
copy /y Living-Website\HTML\*.html deployed_website
echo -----------------------------------------
cd deployed_website
echo Commit HTML file changes
git checkout pending_changes
git add *.html
git commit -m "Update Nav Bar. AUTOMATIC UPDATE, CHECK FOR ERRORS BEFORE MERGING"
git push origin
echo -----------------------------------------
echo Changes pushed to remote repsitory, changes must be manually merged.
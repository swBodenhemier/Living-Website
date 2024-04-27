rem Update all HTML files inside HTMLFiles directory
rem Check for HTMLFiles directory
if exist "HTMLFiles" (
	rem Clear Everything in directory
	del /Q /F "HTMLFiles\*"
	cd HTMLFiles
	git clone https://github.com/jk2429/deployed_website
	cd deployed_website
	rem copy all HTML files into previous directory
	copy "*.html" "..\"
	cd ..
	rem delete deployed_website directory
	rd /s /q deployed_website
)
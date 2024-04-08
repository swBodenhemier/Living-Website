# D5.Design

## Description
We provide a backend framework for creating an adaptable navigation system for websites that updates links automatically based on popularity.  Our product aims to provide a personalized backend to website owners to provide their customers with a better experience online.
## Architecture

## Class Diagram

## Sequence diagram


Use Case: As a product owner, I want the ability to easily update my website so that I can 	efficiently push out changes that I want.

## Design Patterns
### Blackboard design pattern (Behavioral Pattern):

While our system does not include the advanced AI incorporated into most blackboard systems, it still follows the same design pattern. The downloadDatabase script serves as the knowledge source, reading information from the database. The DatabaseConnection class serves as the blackboard, compiling and organizing the information read from the cmd script. Lastly the controller serves as the control object compiling the information from the blackboard and using it to fulfill other functions.
Controller: https://github.com/jk2429/Living-Website/blob/main/C%2B%2B/Controller.cpp  
DatabaseConnection: https://github.com/jk2429/Living-Website/blob/main/C%2B%2B/databaseConnection.cpp  
downloadDatabase.cmd: https://github.com/jk2429/Living-Website/blob/main/C%2B%2B/downloadDatabase.cmd   
### Singleton design pattern (Creational Pattern):

If we chose to refactor our code into classes, we will use the singleton pattern for ChangeHTML to prevent multiple instances of the class from being created, potentially causing problems in file creation.
Controller: https://github.com/jk2429/Living-Website/blob/main/C%2B%2B/Controller.cpp
ChangeHTML: https://github.com/jk2429/Living-Website/blob/main/C%2B%2B/HTMLChange.cpp 
## Design principles
Our project is designed to be open to add-ons and adapting to future implementations of this software across all platforms. There are some requirements such as having access to github and accessibility to the database, but besides these two necessities, the website is designed to expand based on how big or small the website and its functionality is.  
Our code follows The Single Responsibility Principle because each class only has a single reason to change, for example, the HTMLChange class only generates new HTML files, it is not responsible for reading from the database or interpreting the information held there.  
Our code also follows the Open/Closed Principle as our classes are open for extension, but closed for modification. Because we followed the Single Responsibility Principle, our classes have been spread out to only perform their specific functionality. This allows us to build our project in a way that follows SOLID’s Open/Closed Principle. For example, in order to change the html code our “Controller” needs to connect to the database. Instead of having it connect to the database and then connect to the html file, it instead calls that data is needed in order to change the website. We extend this functionality to “Database Connection” as it is in charge of grabbing data from the database and giving it to the “Controller”. Once the “Controller” has the information it needs it calls that the html file for the website needs to be changed. This functionally is extended to “Change HTML” as it is in charge of making the specific changes needed in the HTML file. These classes only ever perform one functionality and extend anything extra to fellow classes.

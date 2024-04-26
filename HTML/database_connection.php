<?php
$servername = "mysql.ac.nau.edu:3306";
$username = "livingwebsite";
$password = "Vv_dckUVIn";
$dbname = "livingwebsite";

// Connect to the database
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) 
    {
     die("Connection failed: " . $conn->connect_error);
    }

else  
   {
    echo "Connected successfully";
   }
?>
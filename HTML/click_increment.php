<?php
include 'database_connection.php';

// Get the link parameter from the URL
$link = isset($_GET['link']) ? $_GET['link'] : '';

// Map links to their respective HTML pages
$pageMap = [
    'SCP-081' => 'scp_081_page.html',
    'SCP-8012' => 'scp_8012_page.html',
    'SCP-999' => 'scp_999_page.html',
    'SCP-2006' => 'scp_2006_page.html',
    'SCP-1990' => 'scp_1990_page.html',
    'SCP-2161' => 'scp_2161_page.html'
];

// Check if the link is valid
if (!array_key_exists($link, $pageMap)) 
    {
     echo "Invalid link";
     exit;
    }

// Update the times_accessed count in the database
$sql = "UPDATE `Object` SET times_accessed = times_accessed + 1 WHERE link = ?";

if ($stmt = $conn->prepare($sql)) 
    {
     $stmt->bind_param("s", $link);

     if (!$stmt->execute()) 
        {
         error_log("Error updating record: " . $stmt->error);
        }

     $stmt->close();
    } 

else 
    {
     error_log("Error preparing statement: " . $conn->error);
    }

// Redirect to the actual page
header('Location: ' . $pageMap[$link]);
exit;
?>

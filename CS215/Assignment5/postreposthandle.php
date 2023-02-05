<?php
	session_start();
    if (isset($_SESSION["email"])) {
        if(isset($_POST['newpost'])){
            $_SESSION["method"] = "post";
        }
        else{
            $_SESSION["method"] = "repost";
        }
        header("Location: tiles_postrepostform.php");
        exit();
    }
    else {
        header("Location: tiles_homepage.php");
    }
?>

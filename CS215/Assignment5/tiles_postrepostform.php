<?php session_start();?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
	    <meta charset="utf-8"/>
        <title>Tiles - Post/Repost Form</title>    
        <link rel="stylesheet" type="text/css" href="style.css">
        <script type="text/javascript" src="post_validation.js"></script>
    </head>
    <body>
        <header>
            <table>
                <td><a href="tiles_homepage.php"><img src="logo.png" alt="logo" /></a></td>
                <td><h1>Post/Repost Form</h1></td>
            </table>
        </header>
        <section>
            <article>
                <h2>Post/Repost</h2>
                <p>Number of characters: <span id="charactercounter">250</span></p>
                <!----------------- POST/REPOST FORM ----------------------------->
                <form action="tiles_postrepostform.php" id="pr_form" method="post">
                    <div id="post_err">
                        <label id="post_msg" class="err_msg"></label>
                        <textarea id="post_content" name="post_content" placeholder="Write you post here (your post/repost should be no longer than 250 character) ..."></textarea>
                    </div>

                    <button id="post_button" type="submit" name="post_button">Post</button>
                </form>
                
                <hr/>
                <a href="tiles_homepage.php">Back to my home page</a>
            </article>
        </section>
        <script type="text/javascript" src="post_events.js"></script>
        
        
        
        <!--------------------- PHP CODE FOR POST/REPOST FORM ----------------------->
        <?php
            if(isset($_POST['post_button'])) {
                
                // Create database connection
                $db = new mysqli("localhost", "caoba200", "Anne123", "caoba200");
                if ($db->connect_error) {
                    die ("Connection failed: " . $db->connect_error);
                }
                
                // Get user_id from $_SESSION["email"]
                $user_email = $_SESSION["email"];
                $q1 = "select user_id from UserInfo where email = '$user_email'";
                $r1 = $db->query($q1);
                $row = $r1->fetch_assoc();
                $user_id = $row["user_id"];
                
                $content = $_POST['post_content'];
                
                if (strlen($content) > 0 && strlen($content) <= 250) {
                    
                    if ($_SESSION["method"] == "post") {
                        // Insert into table post
                        $q2 = "insert into Post (user_id, content) values ('$user_id', '$content')";
                        $r2 = $db->query($q2);
                    }
                    else {
                        // Insert into table repost
                    }
                    
                    // Direct back to post list page
                    header("Location: tiles_homepage.php");
                    $db->close();
                    exit();
                }
                else {
                    $db->close();
                }
                
            }
        ?>
    </body>
</html>
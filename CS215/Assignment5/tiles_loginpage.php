<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
	    <meta charset="utf-8"/>
        <title>Tiles</title>    
        <link rel="stylesheet" type="text/css" href="style.css">
        <script type="text/javascript" src="form_validation.js"></script>
    </head>
    <body>
        <header>
            <table>
                <td><a href="tiles_homepage.php"><img src="logo.png" alt="logo" /></a></td>
                <td><h1>Login Page</h1></td>
            </table>
        </header>
        <section>
            <article>
                <h2>Login</h2>
                <form action="tiles_loginpage.php" id="form_validation" method="post">
                    <input type="hidden" name="submittedL" value="1"/>
                   <!-- Handle email format --> 
                    <div id="email_err">
                        <label>Email</label>
                        <label id="email_msg" class="err_msg"></label>
                        <input type="text" name="email" id="email" placeholder="Enter your email ..."/><br/>
                    </div>
                    
                    <!-- Handle password format -->
                    <div id="password_err">
                        <label>Password</label>
                        <label id="password_msg" class="err_msg"></label>
                        <input type="password" name="password" id="password" placeholder="Enter your password ..."/><br/>
                    </div>
                    
                    <input type="submit" name="login_button" value="Log In"/><br/>
                </form>
                <hr/>
                <a href="tiles_signuppage.php">New user? Click here to Sign Up</a>
            </article>
        </section>
        <script type="text/javascript" src="form_events.js"></script>
    </body>
</html>

<?php

    $validateL = true;
    $reg_EmailL = "/^\w+@[a-zA-Z_]+?\.[a-zA-Z]{2,3}$/";
    $reg_PswdL = "/^(?=.*[^a-zA-Z\s])(?=.*[\S]).{8,}$/";

    $emailL = "";
    $error = "";

    if (isset($_POST["submittedL"]) && $_POST["submittedL"])
    {
        $emailL = trim($_POST["email"]);
        $passwordL = trim($_POST["password"]);

        $db = new mysqli("localhost", "caoba200", "Anne123", "caoba200");
        if ($db->connect_error)
        {
            die ("Connection failed: " . $db->connect_error);
        }

        $q = "select * from UserInfo where email='$emailL' AND password='$passwordL'";
        $r = $db->query($q);
        $row = $r->fetch_assoc();
        if($emailL != $row["email"] && $passwordL != $row["password"])
        {
            $validateL = false;
        }
        else
        {
            $emailLMatch = preg_match($reg_EmailL, $emailL);
            if($emailL == null || $emailL == "" || $emailLMatch == false)
            {
                    $validateL = false;
            }

            $pswdLen = strlen($passwordL);
            $passwordLMatch = preg_match($reg_PswdL, $passwordL);
            if($passwordL == null || $passwordL == "" || $pswdLen < 8 || $passwordLMatch == false)
            {
                    $validateL = false;
            }
        }

        if($validateL == true)
        {

            session_start();
            $_SESSION["email"] = $row["email"];
	        $_SESSION["username"] = $row["username"];
	        $_SESSION["image"] = $row["image"];
            header("Location: tiles_homepage.php");
            $db->close();
            exit();
        }
        else 
        {
            $error = "The email/password combination was incorrect. Login failed.";
            $db->close();
        }
    }

?>

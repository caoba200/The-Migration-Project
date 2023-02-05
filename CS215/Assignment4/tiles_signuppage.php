<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
	    <meta charset="utf-8"/>
        <title>Sign-up Page</title>    
        <link rel="stylesheet" type="text/css" href="style.css">
        <script type="text/javascript" src="form_validation.js"></script>
    </head>
    <body>
        <header>
            <table>
                <td><a href="tiles_loginpage.php"><img src="logo.png" alt="logo" /></a></td>
                <td><h1>Sign-up Form</h1></td>
            </table>
        </header>
        <section>
            <article>
                <h2>Sign-up Form</h2>
                <form action="tiles_signuppage.php" id="form_validation" method="post">
                    <input type="hidden" name="submittedS" value="1"/>
                    <!--********************* EMAIL ****************************************-->
                    <div id="email_err">
                        <label>Email</label>
                        <label id="email_msg" class="err_msg"></label>
                        <input type="text" name="email" id="email" placeholder="Enter your email ..."/><br/>
                    </div>
                    <!--********************** USERNAME ************************************-->
                    <div id="usrname_err">
                        <label>Username</label>
                        <label id="usrname_msg" class="err_msg"></label>
                        <input type="text" name="username" id="username" placeholder="Enter your username ..."/><br/>
                    </div>
                    <!--*********************** PASSWORD ***********************************-->
                    <div id="password_err">
                        <label>Password</label>
                        <label id="password_msg" class="err_msg"></label>
                        <input type="password" name="password" id="password" placeholder="Enter your password ..."/><br/>
                    </div>
                    <!--************************ CONFIRM PASSWORD **************************-->
                    <div id="pwdr_err">
                        <label>Confirm Password</label>
                        <label id="pwdr_msg" class="err_msg"></label>
                    <input type="password" name="confirm_password" id="confirm_password" placeholder="Confirm your password ..."/><br/>
                    </div>
                    <!--************************ DATE OF BIRTH *****************************-->
                    <div id="birthday_err">
                        <label>Date of Birth</label>
                        <label id="birthday_msg" class="err_msg"></label>
                        <input type="text" name="date_of_birth" id="date_of_birth" placeholder="Enter your birthday with the format MM/DD/YYYY..."/><br/>
                    </div>
                    <!--************************ PROFILE PICTURE ***************************-->
                    <div id="propic_err">
                        <label>Profile Picture</label>
                        <label id="propic_msg" class="err_msg"></label>
                        <div id="upload_profile_picture">
                            <!--utton class="button">Upload</button-->
                            <input class="pp" type="file" name="profile_picture" id="profile_picture"/>
                        </div>
                        <br/>
                    </div>
                    
                    <!--************************ SUBMIT BUTTON *****************************-->
                    <input type="submit" name="signup_button" value="Sign-up"/><br/>
                </form>
                <hr/>
                <a href="tiles_loginpage.php">Already have an account? Click here to Log In</a>
            </article>
        </section>
        <script type="text/javascript" src="form_events.js"></script>
    </body>
</html>

<?php 

// ************************ Profile Picture Upload ****************************
    $target_dir = "uploads/";
    $target_file = $target_dir . basename($_FILES["profile_picture"]["name"]);
    $uploadOk = 1;
    $imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
    // Check if image file is a actual image or fake image
    if(isset($_POST["submit"])) {
        $check = getimagesize($_FILES["profile_picture"]["tmp_name"]);
        if($check !== false) {
            //echo "File is an image - " . $check["mime"] . ".";
            $uploadOk = 1;
        } else {
            //echo "File is not an image.";
            $uploadOk = 0;
        }
    }	
    // Check if file already exists
    //if (file_exists($target_file)) {
        //echo "Sorry, file already exists.";
      //  $uploadOk = 0;
    //}
    // Check file size
    //if ($_FILES["profile_picture"]["size"] > 500000) {
        //echo "Sorry, your file is too large.";
      //  $uploadOk = 0;
    //}
    // Allow certain file formats
    //if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
      //      && $imageFileType != "gif" ) {
        //echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
        //$uploadOk = 0;
    //}
    // Check if $uploadOk is set to 0 by an error
    if ($uploadOk == 0) {
        echo "Sorry, your file was not uploaded.";
        // if everything is ok, try to upload file
    } else {
        if (move_uploaded_file($_FILES["profile_picture"]["tmp_name"], $target_file)) {
            //echo "The file ". basename( $_FILES["fileToUpload"]["name"]). " has been uploaded.";
        } else {
            //echo "Sorry, there was an error uploading your file.";
        }
    }
// ************************* Form Validation *************************************

    $validateS = true;
    //$error = "";
    $reg_Email = "/^\w+@[a-zA-Z_]+?\.[a-zA-Z]{2,3}$/";
    $reg_Pswd = "/^(?=.*[^a-zA-Z\s])(?=.*[\S]).{8,}$/";
    $reg_Bday = "/^\d{1,2}\/\d{1,2}\/\d{4}$/";
    $reg_User = "/^\w+$/";
    $emailS = "";
    $dateS = "mm/dd/yyyy";

    if (isset($_POST["submittedS"]) && $_POST["submittedS"])
    {
        $emailS = trim($_POST["email"]);
        $dateS = trim($_POST["date_of_birth"]);
        $passwordS = trim($_POST["password"]);
        $usernameS = trim($_POST["username"]);

        $db = new mysqli("localhost", "caoba200", "Anne123", "caoba200");
        if ($db->connect_error)
        {
            die ("Connection failed: " . $db->connect_error);
        }

        $q1 = "SELECT * FROM UserInfo WHERE email = '$emailS'";
        $r1 = $db->query($q1);

        // if the email address is already taken.
        if($r1->num_rows > 0)
        {
            $validateS = false;
        }
        else
        {
            $emailMatch = preg_match($reg_Email, $emailS);
            if($emailS == null || $emailS == "" || $emailMatch == false)
            {
                $validateS = false;
            }


            $pswdLenS = strlen($passwordS);
            $pswdMatch = preg_match($reg_Pswd, $passwordS);
            if($passwordS == null || $passwordS == "" || $pswdLenS < 8 || $pswdMatch == false)
            {
                $validateS = false;
            }

            $bdayMatch = preg_match($reg_Bday, $dateS);
            if($dateS == null || $dateS == "" || $bdayMatch == false)
            {
                $validateS = false;
            }
            
            $unameMatch = preg_match($reg_User, $usernameS);
            if($usernameS == null || $usernameS == "" || $unameMatch == false)
            {
                $validate = false;
            }
        }

        if($validateS == true)
        {
            $dateFormatS = date("Y-m-d", strtotime($dateS));
            //add code here to insert a record into the table User;
            // table User attributes are: email, password, DOB
            // variables in the form are: emailS, passwordS, dateFormatS, 
            // start with $q2 =
            $q2 = "INSERT INTO UserInfo (email, password, username, DofB, image) VALUES ('$emailS', '$passwordS', '$usernameS','$dateFormatS', '$target_file')";
            $r2 = $db->query($q2);

            if ($r2 === true)
            {
                header("Location: tiles_loginpage.php");
                $db->close();
                exit();
            }
        }
        else
        {
            //$errorS = "email address is not available. Signup failed.";
            $db->close();
        }
    }

?>
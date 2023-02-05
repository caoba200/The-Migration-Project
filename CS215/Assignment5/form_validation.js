// Global variable for form validation
var validatedEmail = true;
var validatedUsername = true;
var validatedPasswd = true;
var validatedPasswdr = true;
var validatedDoB = true;

// Hidden error field and cleanup error message
function ErrorCleanUp(message, position) {
    // Clean up error message
    document.getElementById(message).innerHTML = "";
    // Set the error field to default 
    var display = document.getElementById(position);
    display.style.backgroundColor = "transparent";
    display.style.border = "none";
    display.style.padding = "0";
    display.style.margin = "0";
}

// Highlight error field
function DisplayError(position) {
    var display = document.getElementById(position);
    display.style.backgroundColor = "#99b3ff";
    display.style.border = "solid red";
    display.style.borderRadius = "5px";
    display.style.padding = "1%";
    display.style.margin = "1%";
}

// **************** CHECK EMAIL *********************************
function CheckEmail(event) {
    // Get the target
    var email = event.currentTarget;
    // Regular expression for email
    var email_v = /^\w+@[a-zA-Z_]+?\.[a-zA-Z]{2,3}$/;
    
    // Email validation
    if (email.value == null || email.value == "" || email.value.search(email_v) != 0) {
        // Highlight error field
        DisplayError("email_err");
        // Display error message
        document.getElementById("email_msg").innerHTML = "<br/>Email address empty or wrong format. Example: sample@places.ca";
        validatedEmail = false;
    }
    else {
        ErrorCleanUp("email_msg", "email_err");
        validatedEmail = true;
    }
}

// ***************** CHECK PASSWORD ******************************
function CheckPassword(event) {
    // Get the target
    var password = event.currentTarget;
    // Regex for password
    var pass_v = /^(?=.*[^a-zA-Z\s])(?=.*[\S]).{8,}$/;
    if (password.value == null || password.value == "" || password.value.search(pass_v) != 0) {
        // Highlight error field
        DisplayError("password_err");
        // Display error message
        document.getElementById("password_msg").innerHTML = "<br/>Password should be at least 8 characters and at least 1 non-letter character";
        validatedPasswd = false;
    }
    else {
        ErrorCleanUp("password_msg", "password_err");
        validatedPasswd = true;
    }
}

// ***************** CHECK USERNAME ******************************
function CheckUsername(event) {
    // Get the target
    var username = event.currentTarget;
    var username_v = /^\w+$/;
    
    if (username.value == null || username.value == "" || username.value.search(username_v) != 0) {
        // Highlight error field
        DisplayError("usrname_err");
        // Display error message
        document.getElementById("usrname_msg").innerHTML = "<br/>Username should contain only characters, numbers and underscore";
        validatedUsername = false;
    }
    else {
        ErrorCleanUp("usrname_msg", "usrname_err");
        validatedUsername = true;
    }
}

//******************* CHECK CONFIRM PASSWORD *************************
function CheckPwdr(event) {
    var pwdr = event.currentTarget;
    var pass = document.getElementById("password");
    // Compare the confirmed password with the original one
    if (pwdr.value != pass.value || pwdr.value == null || pwdr.value == "") {
        // Highlight error field
        DisplayError("pwdr_err");
        // Display error message
        document.getElementById("pwdr_msg").innerHTML = "<br/>Password must match the password entered above";
        validatedPasswdr = false;
    }
    else {
        ErrorCleanUp("pwdr_msg", "pwdr_err");
        validatedPasswdr = true;
    }
}

//******************** CHECK DATE OF BIRTH ***************************
function CheckBirthday(event) {
    var birthday = event.currentTarget;
    // Regex for birthday
    var birthday_v = /^(\d\d\/){2}\d{4}$/;
    if (birthday.value == null || birthday.value == "" || birthday.value.search(birthday_v) != 0) {
        // Highlight error field
        DisplayError("birthday_err");
        // Display error message
        document.getElementById("birthday_msg").innerHTML = "<br/>Birthday must be in the format MM/DD/YYYY";
        validatedDoB = false;
    }
    else {
        ErrorCleanUp("birthday_msg", "birthday_err");
        validatedDoB = true;
    }
}

function Validate(event) {
    if (!validatedEmail || !validatedUsername || !validatedPasswd || !validatedPasswdr || !validatedDoB) {
        event.preventDefault();
    }
}


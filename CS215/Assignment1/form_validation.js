// Clean up error message
function ErrorCleanUp(message, position) {
    document.getElementById(message).innerHTML = "";
    var display = document.getElementById(position);
    
    display.style.backgroundColor = "initial";
    display.style.opacity = 1;
    display.style.padding = "0";
}

function DisplayError(position) {
    var display = document.getElementById(position);
    display.style.backgroundColor = "#0000ff";
    display.style.opacity = 0.5;
    display.style.padding = "0.5%";
}

// Login Form valiadtion
function LoginValidation() {
    var email = document.getElementById("email");
    var paswd = document.getElementById("password");
    
    // Regular expression for email and password
    var email_v = /^\w+@[a-zA-Z_]+?\.[a-zA-Z]{2,3}$/;
    var paswd_v = /^\S{8,}$/
    
    // Email validation
    if (email.nodeValue == null || email.nodeValue == "" || email_v.test(email.nodeValue) == false) {
        
        // Change the format
        DisplayError("login_email_err");
        
        // Change the message
        document.getElementById("login_email_msg").innerHTML = "Email address empty or wrong format. Example: sample@places.domain";
    }
    else {
        ErrorCleanUp("login_email_msg", "login_email_err");
    }
}


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


//**************** CHECK NUMBER OF CHAR IN POST/REPOST FORM ***********************
function CheckPost(event) {
    var post = event.currentTarget;
    if (post.value == null || post.value == "" || post.value.length > 250) {
        // Highlight error field
        DisplayError("post_err");
        // Display error message
        document.getElementById("post_msg").innerHTML = "Post/Repost should be non-blank and less than 250 character";
    }
    else {
        ErrorCleanUp("post_msg", "post_err");
    }
}

function CheckCounter(event) {
    var post = event.currentTarget;
    var counter = 250 - post.value.length;
    ErrorCleanUp("post_msg", "post_err");
    document.getElementById("charactercounter").innerHTML = counter.toString();
}

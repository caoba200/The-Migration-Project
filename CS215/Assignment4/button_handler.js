function Update(event) {
    // Get the current target
    var info = event.currentTarget;
    // Initialize the number which represents for number of likes/dislikes/reposts
    var number = 0;
    // If the button is not clicked
    if (info.firstChild.style.backgroundColor != "rgb(169, 169, 169)") {
        // Change the background to indicate that it is clicked (gray background color)
        info.firstChild.style.backgroundColor = "#a9a9a9";
        // Increase the number of likes/dislikes/reposts 
        number = parseInt(info.lastChild.innerHTML) + 1;
        // Update the number of likes/dislikes/reposts
        info.lastChild.innerHTML = number;
    }
    // If the buttons is clicked and users click it again to undo it
    else {
        // Change the button background color back to blue
        info.firstChild.style.backgroundColor = "#6699ff";
        // Update the number (reduces it by 1)
        number = parseInt(info.lastChild.innerHTML) - 1;
        info.lastChild.innerHTML = number;
    }
}
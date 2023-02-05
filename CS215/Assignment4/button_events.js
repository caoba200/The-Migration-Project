var buttons = document.getElementsByClassName("footerbuttonposition");

// Add event listener for each element in the array buttons
for(i = 0; i < buttons.length; i++) {
    buttons[i].addEventListener("click", Update, false);
}
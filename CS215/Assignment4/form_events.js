var emailNode = document.getElementById("email");
var passNode = document.getElementById("password");
var usrnameNode = document.getElementById("username");
var passrNode = document.getElementById("confirm_password");
var bdayNode = document.getElementById("date_of_birth");

document.getElementById("form_validation").addEventListener("submit", Validate, false);

emailNode.addEventListener("blur", CheckEmail, false);
passNode.addEventListener("blur", CheckPassword, false);
usrnameNode.addEventListener("blur", CheckUsername, false);
passrNode.addEventListener("blur", CheckPwdr, false);
bdayNode.addEventListener("blur", CheckBirthday, false);


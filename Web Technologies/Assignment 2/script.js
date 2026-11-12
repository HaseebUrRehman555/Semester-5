const overlay = document.getElementById("signupOverlay");
const form = document.getElementById("signupForm");

if (sessionStorage.getItem("signedUp") !== "yes") {
  overlay.classList.add("show");
}

form.addEventListener("submit", function (event) {
  event.preventDefault();

  const name = document.getElementById("name").value.trim();
  const email = document.getElementById("email").value.trim().toLowerCase();
  const address = document.getElementById("address").value.trim();
  const password = document.getElementById("password").value;

  if (name === "") {
    alert("Please enter your name.");
    return;
  }

  if (!email.endsWith("@gmail.com") || email.length <= 10) {
    alert("Wrong email! Your email must end with @gmail.com");
    return;
  }

  if (address === "") {
    alert("Please enter your address.");
    return;
  }

  if (password.length < 8) {
    alert("Wrong password! Your password must be at least 8 characters.");
    return;
  }

  sessionStorage.setItem("signedUp", "yes");
  alert("Registration successful! Welcome to Badminton Hub.");
  overlay.classList.remove("show");
});
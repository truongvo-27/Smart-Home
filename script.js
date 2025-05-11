// Toggle sidebar visibility and adjust content width
document.getElementById("hamburger").addEventListener("click", function () {
  const sidebar = document.getElementById("sidebar");
  const content = document.getElementById("content");
  sidebar.classList.toggle("show-sidebar");

  // Shift content to the right when the sidebar is visible
  if (sidebar.classList.contains("show-sidebar")) {
    content.classList.add("shifted");
    this.setAttribute("aria-expanded", "true");
  } else {
    content.classList.remove("shifted");
    this.setAttribute("aria-expanded", "false");
  }
});
// Update the clock every second
setInterval(() => {
  document.getElementById("current-time").innerText =
    new Date().toLocaleTimeString();
  document.getElementById("current-date").innerText =
    new Date().toLocaleDateString();  
}, 1000);


/////////////


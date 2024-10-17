var izborniMeni = document.getElementById("izborniMeni");
var vidljiv = false;

function ucitajMeni() {
  if (vidljiv == true) {
    izborniMeni.style.display = "none";
  } 
  else {
    izborniMeni.style.display = "block";
  }

  vidljiv = !vidljiv;
}

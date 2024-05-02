let brojac = 0;

function addTask() {
  let vrijednost = document.getElementById("task-input").value;
  let container = document.getElementById("task-list");

  let novi = document.createElement("li");
  novi.id = `td-${brojac++}`;
  novi.innerHTML = vrijednost;
  novi.onclick = precrtaj;

  if (vrijednost) {
    container.appendChild(novi);
    document.getElementById("task-input").value = "";
  }
  inputFocus();
}

function precrtaj() {
  if (this.style.textDecoration != "line-through")
    this.style.textDecoration = "line-through";
  else this.style.textDecoration = "none";
}

function inputFocus() {
  document.getElementById("task-input").focus();
}

function pritisniEnter(event) {
  if (event.keyCode === 13) {
    // Check if Enter key was pressed
    addTask();
  }
}

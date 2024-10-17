let globalPodaci = [];
function ucitajRadnike() {
  let radnikKontejner = document.getElementById("RadnikKontejner");
  fetch("https://restapiexample.wrd.app.fit.ba/Ispit20210702/Get4Studenta").then((res) => {
    res.json().then((body) => {
      globalPodaci = body;
      for (let i = 0; i < globalPodaci.length; i++) {
        console.log(globalPodaci[i]);
        radnikKontejner.innerHTML += `<div>
                <img src="${globalPodaci[i].slikaUrl}"/>
                <div>
                    <h3>${globalPodaci[i].imeIPrezime}</h3>
                    <p>${globalPodaci[i].opis}</p>
                    <button onclick="pisiPoruku(${i})">Piši poruku</button>
                </div>
            </div>`;
      }
    });
  });
}

function pisiPoruku(rb) {
  document.getElementById("primaoc").value = globalPodaci[rb].imeIPrezime;
}

function validirajNaslov() {
  let naslov = document.getElementById("naslov");
  // -	Naslov – Minimalno dvije riječi. Prva riječ počinje velikim slovom.
  if (!/[A-Z]\w*\s\w+/.test(naslov.value)) {
    naslov.style.backgroundColor = "rgb(255, 68, 68)";
  } else {
    naslov.style.backgroundColor = "rgb(77, 255, 101)";
  }
}

function validirajTelefon() {
  let telefon = document.getElementById("telefon");
  // +111-11-111-1111
  if (!/^\+\d{3}\-\d{2}\-\d{3}\-\d{4}$/.test(telefon.value)) {
    telefon.style.backgroundColor = "rgb(255, 68, 68)";
  } else {
    telefon.style.backgroundColor = "rgb(77, 255, 101)";
  }
}

function posalji() {
  let obj = new Object();
  obj.imePrezime = document.getElementById("primaoc").value;
  obj.id = Number(0);
  for (let i = 0; i < globalPodaci.length; i++) {
    if (globalPodaci[i].imeIPrezime == obj.imePrezime) {
      obj.id = Number(globalPodaci[i].id);
    }
  }
  obj.naslov = document.getElementById("naslov").value;
  obj.poruka = document.getElementById("poruka").value;
  obj.datumVrijeme = String(new Date());
  obj.telefon = document.getElementById("telefon").value;

  //   if (!obj.imeIPrezime || !obj.poruka || !validirajTelefon() || !validirajNaslov()) return;

  let jsonObj = JSON.stringify(obj);

  fetch("https://restapiexample.wrd.app.fit.ba/Ispit20210925/Add", {
    method: "POST",
    body: jsonObj,
    headers: {
      "Content-type": "application/json",
    },
  })
    .then((res) => {
      alert("Rezultat post zahtjeva: " + res.statusText + " \ncode: " + res.status);
      //   alert(res.statusText);
    })
    .catch((err) => {
      alert("GRESKA " + err);
    });
}

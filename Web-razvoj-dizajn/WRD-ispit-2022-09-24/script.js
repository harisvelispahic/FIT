// let preuzmi = () => {
//   //https://restapiexample.wrd.app.fit.ba/ -> Ispit20220924 -> GetPonuda

//   let url = `https://restapiexample.wrd.app.fit.ba/Ispit20220924/GetPonuda?travelfirma=${firma.value}`;

//   fetch(url).then((r) => {
//     if (r.status !== 200) {
//       //greska
//       return;
//     }
//     r.json().then((t) => {
//       destinacije.innerHTML = ""; //brisemo destinacije koje su hardkodirane (tj. nalaze se u HTML-u)
//       for (const x of t.podaci) {
//         destinacije.innerHTML += `
//                     <article class="offer">
//                         <div class="akcija">${x.akcijaPoruka}</div>
//                         <div  class="offer-image" style="background-image: url('${x.imageUrl}');" ></div>
//                         <div class="offer-details">
//                             <div class="offer-destination">${x.mjestoDrzava}</div>
//                             <div class="offer-price">$${x.cijenaDolar}</div>
//                             <div class="offer-description">${x.opisPonude}</div>
//                             <div class="offer-firma">${x.travelFirma.naziv}</div>
//                             <select class="offer-option">
//                                         ${generisiOpcije(x)}
//                                 </select>
//                         </div>
//                         <div class="ponuda-dugme-1">Odaberi za destinaciju 1</div>
//                         <div class="ponuda-dugme-2">Odaberi za destinaciju 2</div>
//                     </article>
//                 `;
//       }
//     });
//   });
// };
function generisiOpcije(x) {
  let s = "";
  for (const o of x.opcije) {
    s += `<option>${o}</option>`;
  }
  return s;
}

let podaci = [];
let destinacije = document.getElementById("destinacije");

let preuzmi = () => {
  //https://restapiexample.wrd.app.fit.ba/ -> Ispit20220924 -> GetPonuda

  let url = `https://restapiexample.wrd.app.fit.ba/Ispit20220924/GetPonuda?travelfirma=${firma.value}`;
  fetch(url).then((res) => {
    if (res.status != 200) {
      return;
    }
    res.json().then((pr) => {
      destinacije.innerHTML = "";
      for (let i = 0; i < pr.podaci.length; i++) {
        podaci.push(pr.podaci[i]);
        // console.log(pr.podaci[i]);
        let x = podaci[i];
        destinacije.innerHTML += `
                     <article class="offer">
                         <div class="akcija">${x.akcijaPoruka}</div>
                         <div  class="offer-image" style="background-image: url('${x.imageUrl}');" ></div>
                         <div class="offer-details">
                             <div class="offer-destination">${x.mjestoDrzava}</div>
                             <div class="offer-price">$${x.cijenaDolar}</div>
                             <div class="offer-description">${x.opisPonude}</div>
                             <div class="offer-firma">${x.travelFirma.naziv}</div>
                             <select class="offer-option" id="opcija${i}">
                                         ${generisiOpcije(x)}
                                 </select>
                         </div>
                         <div class="ponuda-dugme-1" onclick="odaberiDestinaciju1('${i}')">Odaberi za destinaciju 1</div>
                         <div class="ponuda-dugme-2" onclick="odaberiDestinaciju2('${i}')">Odaberi za destinaciju 2</div>
                     </article>
                 `;
      }
    });
  });
};

let odaberiDestinaciju1 = (redniBroj) => {
  let destinacija1 = document.getElementById("destinacija-1");
  let opcija = document.getElementById(`opcija${redniBroj}`);
  destinacija1.value = podaci[redniBroj].mjestoDrzava + " " + opcija.value;

  let cijena1 = document.getElementById("cijena-1");
  cijena1.value = podaci[redniBroj].cijenaDolar;
  izracunajUkupnuCijenu();
};
let odaberiDestinaciju2 = (redniBroj) => {
  let destinacija2 = document.getElementById("destinacija-2");
  let opcija = document.getElementById(`opcija${redniBroj}`);
  destinacija2.value = podaci[redniBroj].mjestoDrzava + " " + opcija.value;

  let cijena2 = document.getElementById("cijena-2");
  cijena2.value = podaci[redniBroj].cijenaDolar;
  izracunajUkupnuCijenu();
};

let izracunajUkupnuCijenu = () => {
  let ukupnaCijena = document.getElementById("cijena-ukupno");
  let cijena1 = Number(document.getElementById("cijena-1").value);
  let cijena2 = Number(document.getElementById("cijena-2").value);
  ukupnaCijena.value = cijena1 + cijena2;
};

let ErrorBackgroundColor = "#FE7D7D";
let OkBackgroundColor = "#DFF6D8";

let test_email = () => {
  let email = document.getElementById("email");
  if (!/^[A-Za-z]+\.[A-Za-z]+@edu\.fit\.ba$/.test(email.value)) {
    email.style.backgroundColor = ErrorBackgroundColor;
  } else {
    email.style.backgroundColor = OkBackgroundColor;
  }
  return /^[A-Za-z]+\.[A-Za-z]+@edu\.fit\.ba$/.test(email.value);
};

let test_phone = () => {
  let telefon = document.getElementById("phone");
  //  +000-00-000-000
  if (!/^\+\d{3}\-\d{2}\-\d{3}\-\d{3}$/.test(telefon.value)) {
    telefon.style.backgroundColor = ErrorBackgroundColor;
  } else {
    telefon.style.backgroundColor = OkBackgroundColor;
  }
  return /^\+\d{3}\-\d{2}\-\d{3}\-\d{3}$/.test(telefon.value);
};

let posalji = () => {
  //https://restapiexample.wrd.app.fit.ba/ -> Ispit20220924 -> Add
  /*
      {
    "destinacija1Soba": "string",
    "destinacija2Soba": "string",
    "imeGosta": "string",
    "prezimeGosta": "string",
    "poruka": "string",
    "email": "string",
    "telefon": "string"
  }
      */
  let object = new Object();
  object.destinacija1Soba = document.getElementById("destinacija-1").value;
  object.destinacija2Soba = document.getElementById("destinacija-2").value;
  object.imeGosta = document.getElementById("first-name").value;
  object.prezimeGosta = document.getElementById("last-name").value;
  object.poruka = document.getElementById("messagetxt").value;
  object.email = document.getElementById("email").value;
  object.telefon = document.getElementById("phone").value;

  if (!test_email(object.email) || !test_phone(object.telefon)) return;

  let jsonObj = JSON.stringify(object);

  fetch("https://restapiexample.wrd.app.fit.ba/Ispit20220924/Add", {
    method: "POST",
    body: jsonObj,
    headers: {
      "Content-Type": "application/json",
    },
  }).then((res) => {
    if (res.status != 200) console.log("GRESKA");
    res.json().then((pr) => {
      alert("Vasa rezervacija je poslana! Broj rezervacije: " + pr.brojRezervacije);
    });
  });
};

// haris.velispahic@edu.fit.ba

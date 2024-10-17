let globalPodaci = [];
let preuzmi = () => {
  //https://restapiexample.wrd.app.fit.ba/ -> Ispit20230715 -> GetPonuda
  //   let url = `https://wrd-fit.info/Ispit20230715/GetPonuda?travelfirma=${firma.value}`;
  //   destinacije.innerHTML = ""; //brisemo destinacije koje su hardkodirane (tj. nalaze se u HTML-u)
  //   fetch(url).then((r) => {
  //     if (r.status !== 200) {
  //       //greska
  //       return;
  //     }
  //     r.json().then((t) => {
  //       let b = 0;
  //       globalPodaci = t.podaci; //setujemo globalnu varijablu
  //       for (const x of t.podaci) {
  //         destinacije.innerHTML += `
  //                     <article class="offer">
  //                         <div class="akcija">Polazak za <br>${x.naredniPolazak.zaDana} dana</div>
  //                         <div class="offer-image" style="background-image: url('${x.imageUrl}');" ></div>
  //                         <div class="offer-details">
  //                             <div class="offer-destination">${x.mjestoDrzava}</div>
  //                             <div class="offer-description">${x.opisPonude} </div>
  //                             <div class="offer-description">${x.opisPonude} </div>
  //                             <div class="offer-price">${x.naredniPolazak.cijenaEUR} €</div>
  //                             <br>
  //                             <div class="offer-free">
  //                                 <label>
  //                                     Slobodno mjesta:
  //                                 </label>
  //                                 <span>
  //                                     ${x.naredniPolazak.brojSlobodnihMjesta}
  //                                 </span>
  //                             </div>
  //                         </div>
  //                         <div class="offer-footer">
  //                             <div class="ponuda-dugme" onclick="odaberiDestinaciju(${b})">Pogledaj</div>
  //                         </div>
  //                     </article>
  //                     `;
  //         b++;
  //       }
  //     });
  //   });
  fetch(`https://wrd-fit.info/Ispit20230715/GetPonuda?travelfirma=${firma.value}`).then((res) => {
    res.json().then((pr) => {
      console.log(pr);
      document.getElementById("destinacije").innerHTML = "";
      globalPodaci = pr.podaci;
      for (let i = 0; i < pr.podaci.length; i++) {
        let x = pr.podaci[i];
        document.getElementById("destinacije").innerHTML += `
                       <article class="offer">
                           <div class="akcija">Polazak za <br>${x.naredniPolazak.zaDana} dana</div>
                           <div class="offer-image" style="background-image: url('${x.imageUrl}');" ></div>
                           <div class="offer-details">
                               <div class="offer-destination">${x.mjestoDrzava}</div>
                               <div class="offer-description">${x.opisPonude} </div>
                               <div class="offer-description">${x.opisPonude} </div>
                               <div class="offer-price">${x.naredniPolazak.cijenaEUR} €</div>
                               <br>
                               <div class="offer-free">
                                   <label>
                                       Slobodno mjesta:
                                   </label>
                                   <span>
                                       ${x.naredniPolazak.brojSlobodnihMjesta}
                                   </span>
                               </div>
                           </div>
                           <div class="offer-footer">
                               <div class="ponuda-dugme" onclick="odaberiDestinaciju(${i})">Pogledaj</div>
                           </div>
                       </article>
                       `;
      }
    });
  });
};

let odaberiDestinaciju = (rb) => {
  // let destinacijObj = globalPodaci[rb];

  // let s = "";
  // for (const o of destinacijObj.planiranaPutovanja) {
  //   s += `
  //       <tr>
  //           <td>ID ${o.id}</td>
  //           <td>${o.datumPolaska}</td>
  //           <td>${o.datumPovratka}</td>
  //           <td>${o.hotelOpis}</td>
  //           <td>${o.vrstaPrevoza}</td>
  //           <td>${o.cijenaEUR} €</td>
  //           <td><button>Odaberi</button></td>
  //       </tr>`;
  // }
  // putovanjaTabela.innerHTML = s;

  console.log(globalPodaci[rb]);
  document.getElementById("putovanjaTabela").innerHTML = "";
  for (let i = 0; i < globalPodaci[rb].planiranaPutovanja.length; i++) {
    let o = globalPodaci[rb].planiranaPutovanja[i];
    document.getElementById("putovanjaTabela").innerHTML += `<tr>
             <td>ID ${o.id}</td>
             <td>${o.datumPolaska}</td>
             <td>${o.datumPovratka}</td>
             <td>${o.hotelOpis}</td>
             <td>${o.vrstaPrevoza}</td>
             <td>${o.cijenaEUR} €</td>
             <td><button onclick="popuniPolja('${rb}','${i}')">Odaberi</button></td>
         </tr>`;
  }
};

popuniPolja = (rb, i) => {
  promjenaBrojaGostiju();
  document.getElementById("destinacija").value = globalPodaci[rb].mjestoDrzava;
  document.getElementById("datumPolaska").value = globalPodaci[rb].planiranaPutovanja[i].datumPolaska;
  document.getElementById("cijenaPoGostu").value = globalPodaci[rb].planiranaPutovanja[i].cijenaEUR;
  document.getElementById("ukupnaCijena").value =
    document.getElementById("brojGostiju").value * document.getElementById("cijenaPoGostu").value;
};

let ErrorBackgroundColor = "#FE7D7D";
let OkBackgroundColor = "#DFF6D8";

let posalji = () => {
  //https://restapiexample.wrd.app.fit.ba/ -> Ispit20230715 -> Add

  // let jsObjekat = {};

  // console.log(jsObjekat);

  // let url = "https://wrd-fit.info/Ispit20230715/Add";

  // //fetch tipa "POST" i saljemo "jsObjekat"
  // fetch(url, {
  //   method: "POST",
  //   body: JSON.stringify(jsObjekat),
  //   headers: {
  //     "Content-Type": "application/json",
  //   },
  // }).then((r) => {
  //   if (r.status != 200) {
  //     alert("Greška");
  //     return;
  //   }

  //   r.json().then((t) => {
  //     if (t.idRezervacije > 0) {
  //       dialogSuccess(`Idi na placanje rezervacije broj ${t.idRezervacije} - iznos ${ukupnaCijena.value} EUR`, () => {
  //         window.location = `https://www.paypal.com/cgi-bin/webscr?business=adil.joldic@yahoo.com&cmd=_xclick&currency_code=EUR&amount=${ukupnaCijena.value}&item_name=Dummy invoice`;
  //       });
  //     } else {
  //       console.error("Greška: " + t.poruka);
  //     }
  //   });
  // });

  let object = new Object();
  object.travelFirma = document.getElementById("firma").value;
  object.destinacijaDrzava = document.getElementById("destinacija").value;
  object.brojIndeksa = document.getElementById("brojIndeksa").value;
  let gostiNiz = document.getElementsByClassName("imegostaklasa");
  object.gosti = [];
  for (let i = 0; i < gostiNiz.length; i++) {
    object.gosti.push(gostiNiz[i].value);
  }
  object.poruka = document.getElementById("messagetxt").value;
  object.telefon = document.getElementById("phone").value;
  object.datumPolaska = document.getElementById("datumPolaska").value;

  console.log(object);

  if (!object.travelFirma || !object.destinacijaDrzava || !object.datumPolaska) return false;
  for (let i = 0; i < object.gosti.length; i++) {
    if (!object.gosti[i]) return false;
  }
  if (!provjeriBrojIndeksa() || !provjeriTelefon()) return false;

  let jsonObj = JSON.stringify(object);

  fetch("https://wrd-fit.info/Ispit20230715/Add", {
    method: "POST",
    body: jsonObj,
    headers: {
      "Content-Type": "application/json",
    },
  }).then((res) => {
    res.json().then((pr) => {
      alert("Poruka: " + pr.poruka + "\nVrijeme: " + pr.vrijeme + "\nIP adresa: " + pr.ipAdresa);
    });
  });
};

let popuniFimeUCombox = () => {
  let urlFirme = "https://wrd-fit.info/Ispit20230715/GetTravelFirme";

  fetch(urlFirme)
    .then((obj) => {
      if (obj.status != 200) {
        window.alert("Greska pri komunikaciji sa serverom!");
        return;
      }
      obj.json().then((element) => {
        element.forEach((e) => {
          firma.innerHTML += `<option>${e.naziv}</option>`;
        });

        // preuzmi();
      });
    })
    .catch((error) => {
      window.alert("Greska!" + error);
    });
};
popuniFimeUCombox();

let promjenaBrojaGostiju = () => {
  gosti.innerHTML = "";
  for (let i = 0; i < document.getElementById("brojGostiju").value; i++) {
    gosti.innerHTML += `<div class="item-full">
                          <label>Ime gosta </label>
                          <input class="imegostaklasa" />
                      </div>`;
  }
  document.getElementById("ukupnaCijena").value =
    document.getElementById("brojGostiju").value * document.getElementById("cijenaPoGostu").value;
};
/* 
- Broj indeksa – stvarni broj indeksa koji počinje sa IB 
- Telefon – u formatu +000-00-000-000
*/
let provjeriBrojIndeksa = () => {
  if (!/^IB\d{6}$/.test(document.getElementById("brojIndeksa").value)) {
    document.getElementById("brojIndeksa").style.backgroundColor = ErrorBackgroundColor;
    return false;
  } else {
    document.getElementById("brojIndeksa").style.backgroundColor = OkBackgroundColor;
    return true;
  }
};

let provjeriTelefon = () => {
  if (!/^\+\d{3}\-\d{2}\-\d{3}\-\d{3}$/.test(document.getElementById("phone").value)) {
    document.getElementById("phone").style.backgroundColor = ErrorBackgroundColor;
    return false;
  } else {
    document.getElementById("phone").style.backgroundColor = OkBackgroundColor;
    return true;
  }
};

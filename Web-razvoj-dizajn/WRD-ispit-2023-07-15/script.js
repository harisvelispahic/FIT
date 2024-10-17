let globalPodaci = [];
let preuzmi = () => {
  //https://restapiexample.wrd.app.fit.ba/ -> Ispit20230715 -> GetPonuda ?travelfirma="nazivFirme"

  /*      
    Primjer generiranog html/css-a za prikaz destinacije
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
                            <div class="ponuda-dugme" onclick="odaberiDestinaciju(${b})">Pogledaj</div>
                        </div>
                    </article>
                    `*/

  let firmaSelect = document.getElementById("firma").value;
  fetch(`https://restapiexample.wrd.app.fit.ba/Ispit20230715/GetPonuda?travelfirma=${firmaSelect}`).then((res) => {
    // console.log(firmaSelect);
    res.json().then((body) => {
      // console.log(body);

      globalPodaci = body.podaci;
      let ponudePlaceholder = document.getElementById("destinacije");
      ponudePlaceholder.innerHTML = "";
      for (let i = 0; i < globalPodaci.length; i++) {
        // console.log(globalPodaci[i]);
        let x = globalPodaci[i];

        let ponuda = `<article class="offer">
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
            </article>`;

        ponudePlaceholder.innerHTML += ponuda;
      }
    });
  });
};

let odaberiDestinaciju = (rb) => {
  // console.log("odaberi dest funkcija");
  console.log(globalPodaci[rb]);
  document.getElementById("putovanjaTabela").innerHTML = "";
  for (let i = 0; i < globalPodaci[rb].planiranaPutovanja.length; i++) {
    console.log(globalPodaci[rb].planiranaPutovanja[i]);
    document.getElementById("putovanjaTabela").innerHTML += `
      <tr>
        <td>${globalPodaci[rb].planiranaPutovanja[i].id}</td>
        <td>${globalPodaci[rb].planiranaPutovanja[i].datumPolaska}</td>
        <td>${globalPodaci[rb].planiranaPutovanja[i].datumPovratka}</td>
        <td>${globalPodaci[rb].planiranaPutovanja[i].hotelOpis}</td>
        <td>${globalPodaci[rb].planiranaPutovanja[i].vrstaPrevoza}</td>
        <td>${globalPodaci[rb].planiranaPutovanja[i].cijenaEUR}</td>
        <td>
           <button onclick="odaberiPutovanje('${globalPodaci[rb].mjestoDrzava}','${globalPodaci[rb].planiranaPutovanja[i].datumPolaska}', '${globalPodaci[rb].planiranaPutovanja[i].cijenaEUR}')">Odaberi</button>
        </td>

        </tr>
      `;
  }
};

let odaberiPutovanje = (destinacija, datumPolaskaValue, cijenaEUR) => {
  promjenaBrojaGostiju();
  document.getElementById("destinacija").value = destinacija;
  document.getElementById("datumPolaska").value = datumPolaskaValue;
  document.getElementById("cijenaPoGostu").value = cijenaEUR;

  updateUkupnaCijena();
};

let updateUkupnaCijena = () => {
  document.getElementById("ukupnaCijena").value =
    Number(document.getElementById("cijenaPoGostu").value) * Number(document.getElementById("brojGostiju").value);
};

let ErrorBackgroundColor = "#FE7D7D";
let OkBackgroundColor = "#DFF6D8";

let posalji = () => {
  //https://restapiexample.wrd.app.fit.ba/ -> Ispit20230715 -> Add
  let uspjeh = true;

  if (
    !document.getElementById("destinacija").value ||
    !document.getElementById("datumPolaska").value ||
    !document.getElementById("cijenaPoGostu").value ||
    !document.getElementById("ukupnaCijena").value
  )
    uspjeh = false;

  for (let i = 0; i < Number(document.getElementById("brojGostiju").value); i++) {
    if (!document.getElementById(`gost${i + 1}`).value) uspjeh = false;
  }
  if (
    !/^\+\d{3}\-?\d{2}\-?\d{3}\-?\d{3,4}$/.test(document.getElementById("phone").value) ||
    !/^IB\d{6}$/.test(document.getElementById("brojIndeksa").value)
  )
    uspjeh = false;

  let obj = new Object();
  obj.travelFirma = document.getElementById("firma").value;
  obj.destinacijaDrzava = document.getElementById("destinacija").value;
  obj.brojIndeksa = document.getElementById("brojIndeksa").value;
  obj.telefon = document.getElementById("phone").value;
  obj.datumPolaska = document.getElementById("datumPolaska").value;
  obj.poruka = document.getElementById("messagetxt").value;

  let gostiNiz = [];
  for (let i = 0; i < Number(document.getElementById("brojGostiju").value); i++) {
    gostiNiz.push(document.getElementById(`gost${i + 1}`).value);
  }
  obj.gosti = gostiNiz;

  let jsonObj = JSON.stringify(obj);

  if (uspjeh) {
    fetch("https://restapiexample.wrd.app.fit.ba/Ispit20230715/Add", {
      method: "POST",
      body: jsonObj,
      headers: {
        "Content-type": "application/json",
      },
    }).then((res) => {
      // console.log(res);
      res.json().then((pr) => {
        console.log(pr);
        dialogSuccess("Uspješno kreirana rezervacija.", () => {});
      });
    });
  }
};

let popuniFimeUCombox = () => {
  let urlFirme = "https://restapiexample.wrd.app.fit.ba/Ispit20230624/GetTravelFirme";
  fetch("https://restapiexample.wrd.app.fit.ba/Ispit20230715/GetTravelFirme").then((res) => {
    if (res.status != 200) {
      alert("Greska -> " + res.statusText);
      return;
    }
    res.json().then((body) => {
      // console.log(body);
      let lista = document.getElementById("firma");
      for (let i = 0; i < body.length; i++) {
        lista.innerHTML += `<option>${body[i].naziv}</option>`;
      }
    });
  });
};
popuniFimeUCombox();

let promjenaBrojaGostiju = () => {
  let x = Number(document.getElementById("brojGostiju").value);
  if (x < 1 || x > 5) return;
  // console.log(x);
  updateUkupnaCijena();

  document.getElementById("gosti").innerHTML = "";
  for (let i = 0; i < x; i++) {
    document.getElementById("gosti").innerHTML += `<label>Ime gosta ${i + 1}</label>
      <input id='gost${i + 1}' class='gosti'/>`;
  }

  return x;
};

let provjeriTelefon = () => {
  // +000-00-000-000
  if (!/^\+\d{3}\-?\d{2}\-?\d{3}\-?\d{3,4}$/.test(document.getElementById("phone").value)) {
    document.getElementById("phone").style.backgroundColor = ErrorBackgroundColor;
  } else {
    document.getElementById("phone").style.backgroundColor = OkBackgroundColor;
  }
};

let provjeriBrojIndeksa = () => {
  if (!/^IB\d{6}$/.test(document.getElementById("brojIndeksa").value)) {
    document.getElementById("brojIndeksa").style.backgroundColor = ErrorBackgroundColor;
  } else {
    document.getElementById("brojIndeksa").style.backgroundColor = OkBackgroundColor;
  }
};

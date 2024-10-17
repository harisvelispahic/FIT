let destinacije = [];

preuzmi = () => {
  fetch("https://wrd-fit.info/Ispit20220625/Get6Ponuda").then((response) =>
    response.json().then((res) => {
      destinacije = res;
      document.getElementById("destinacije").innerHTML = "";
      for (let i = 0; i < res.length; i++) {
        console.log(res[i]);
        document.getElementById("destinacije").innerHTML += `
        <article class="offer">
            <img src="${destinacije[i].slikaUrl}" alt="offer" />
            <div class="offer-details">
              <h4 class="offer-destination">${destinacije[i].drzava}</h4>
              <h3 class="offer-price">$${destinacije[i].cijena}</h3>
            </div>
            <div class="ponuda-dugme" onclick=odaberiPonudu('${i}')>Odaberi ponudu</div>
          </article>`;
      }
    })
  );
};

odaberiPonudu = (index) => {
  document.getElementById("destinacija").value = destinacije[index].drzava;
};

/* Haris
Prije slanja podataka obavezno izvrsiti validaciju prema slijedecim pravilima: 
- Ime – jedna rijec, prvo slovo veliko 
- Prezime – jedna rijec, prvo slovo veliko 
- E-mail – prema pravilu e-mail formata 
- Telefonm – u formatu +000-00-000-000
 */

let opacity = 0.4;

validirajIme = () => {
  if (!/^[A-Z][a-z]+$/.test(document.getElementById("first-name").value)) {
    document.getElementById("first-name").style.backgroundColor = `rgb(255,0,0,${opacity})`;
    return false;
  } else {
    document.getElementById("first-name").style.backgroundColor = `rgb(0,255,0,${opacity})`;
    return true;
  }
};

validirajPrezime = () => {
  if (!/^[A-Z][a-z]+$/.test(document.getElementById("last-name").value)) {
    document.getElementById("last-name").style.backgroundColor = `rgb(255,0,0,${opacity})`;
    return false;
  } else {
    document.getElementById("last-name").style.backgroundColor = `rgb(0,255,0,${opacity})`;
    return true;
  }
};

validirajEmail = () => {
  if (!/^[A-Za-z]+(\.[A-Za-z]+)?@[A-Za-z]+\.(com|ba)$/.test(document.getElementById("email").value)) {
    document.getElementById("email").style.backgroundColor = `rgb(255,0,0,${opacity})`;
    return false;
  } else {
    document.getElementById("email").style.backgroundColor = `rgb(0,255,0,${opacity})`;
    return true;
  }
};

validirajTelefon = () => {
  if (!/^\+\d{3}\-\d{2}\-\d{3}\-\d{3}$/.test(document.getElementById("phone").value)) {
    document.getElementById("phone").style.backgroundColor = `rgb(255,0,0,${opacity})`;
    return false;
  } else {
    document.getElementById("phone").style.backgroundColor = `rgb(0,255,0,${opacity})`;
    return true;
  }
};

posalji = () => {
  let object = new Object();
  object.destinacijaID = document.getElementById("destinacija").value;
  object.ime = document.getElementById("first-name").value;
  object.prezime = document.getElementById("last-name").value;
  object.poruka = document.getElementById("poruka").value;
  object.email = document.getElementById("email").value;
  object.telefon = document.getElementById("phone").value;
  if (!validirajEmail() || !validirajTelefon() || !validirajIme() || !validirajPrezime() || !object.destinacijaID)
    return;
  console.log(object);

  let jsonObj = JSON.stringify(object);

  fetch("https://wrd-fit.info/Ispit20220625/Add", {
    method: "POST",
    body: jsonObj,
    headers: {
      "Content-Type": "application/json",
    },
  }).then((res) => {
    res.json().then((pr) => {
      alert(pr.poruka + "\n" + pr.vrijeme + "\nBroj rezervacije: " + pr.brojRezervacije);
    });
  });
};

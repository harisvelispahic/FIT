let nizGradova = [];
let preuzmiGradove = () => {
  fokusirajSearch();
  fetch("https://api.vaktija.ba/vaktija/v1/lokacije").then((res) => {
    res.json().then((pr) => {
      let gradovi = document.getElementById("gradovi");
      for (let i = 0; i < pr.length; i++) {
        nizGradova.push(pr[i]);
      }
    });
  });
};

let pretraga = () => {
  let unos = document.getElementById("pretraga").value;

  let nadjeniGradovi = [];
  gradovi.innerHTML = "";
  for (let i = 0; i < nizGradova.length; i++) {
    if (nizGradova[i].toLowerCase().startsWith(unos.toLowerCase())) nadjeniGradovi.push(nizGradova[i]);
  }
  for (let i = 0; i < nadjeniGradovi.length; i++) {
    gradovi.innerHTML += `<p class="grad" onclick="odaberiGrad('${nadjeniGradovi[i]}')">${nadjeniGradovi[i]}</p>`;
  }
  if (unos == "") gradovi.innerHTML = "";
};

let odaberiGrad = (odabraniGrad) => {
  console.log("Odabrani grad: " + odabraniGrad);
  //   gradovi.innerHTML = odabraniGrad;
  pronadjiIdGrada(odabraniGrad);
  preuzmiVaktove(odabraniGrad);
  gradovi.innerHTML = "";
  document.getElementById("pretraga").value = odabraniGrad;
};

let pronadjiIdGrada = (odabraniGrad) => {
  for (let i = 0; i < nizGradova.length; i++) {
    if (odabraniGrad == nizGradova[i]) {
      console.log(i);
      return i;
    }
  }
};

let preuzmiVaktove = (odabraniGrad) => {
  let datum = new Date();
  let dan = datum.getDate();
  let mjesec = Number(datum.getMonth() + 1);
  let godina = Number(datum.getFullYear());
  console.log(dan + " " + mjesec + " " + godina);
  // https://api.vaktija.ba/vaktija/v1/77/2019/7/30
  fetch(`https://api.vaktija.ba/vaktija/v1/${pronadjiIdGrada(odabraniGrad)}/${godina}/${mjesec}/${dan}`).then((res) => {
    res.json().then((pr) => {
      console.log(pr);
      document.getElementById("zora").innerHTML = pr.vakat[0];
      document.getElementById("izlazak-sunca").innerHTML = pr.vakat[1];
      document.getElementById("podne").innerHTML = pr.vakat[2];
      document.getElementById("ikindija").innerHTML = pr.vakat[3];
      document.getElementById("aksam").innerHTML = pr.vakat[4];
      document.getElementById("jacija").innerHTML = pr.vakat[5];
    });
  });
};

let fokusirajSearch = () => {
  document.getElementById("pretraga").focus();
};

let selectText = () => {
  document.getElementById("pretraga").select();
};

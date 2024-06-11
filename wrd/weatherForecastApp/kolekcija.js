class Kolekcija {
  brojac = 0;
  podaci = [];
  storageName;

  constructor(storageName) {
    this.storageName = storageName;
    this.loadFromStorage();
  }

  getAll() {
    return this.podaci;
  }

  findById(taziId) {
    return this.podaci.find((x) => x.id == taziId);
  }

  removeOne(kriterij) {
    let obj = this.podaci.find(kriterij);

    if (obj) {
      let index = this.podaci.indexOf(obj);
      if (index !== -1) {
        this.podaci.splice(index, 1);
        this.saveToStorage();
        return true;
      }
    }
    return false;
  }

  removeRange(kriterij) {
    let objNiz = this.podaci.filter(kriterij);
    let indeksNiz = objNiz.map((obj) => this.podaci.indexOf(obj)).sort((a, b) => b - a);

    indeksNiz.forEach((index) => {
      this.podaci.splice(index, 1);
    });

    if (indeksNiz.length > 0) {
      this.saveToStorage();
    }
    return indeksNiz.length;
  }

  removeById(id) {
    return this.removeOne((x) => x.id == id);
  }

  add(novi) {
    let noviId = this.brojac++;
    let obj = { id: noviId, objekat: novi };
    this.podaci.push(obj);
    this.saveToStorage();
    return obj;
  }

  saveToStorage() {
    let str = JSON.stringify(this.podaci);
    localStorage.setItem(this.storageName, str);
    this.updateBrojac();
  }

  loadFromStorage() {
    let str = localStorage.getItem(this.storageName);
    if (str) {
      this.podaci = JSON.parse(str);
      this.updateBrojac();
      return true;
    }
    return false;
  }

  updateBrojac() {
    if (this.podaci.length > 0) {
      this.brojac = Math.max(...this.podaci.map((item) => item.id)) + 1;
    }
  }
}

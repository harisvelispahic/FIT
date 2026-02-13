import { platformBrowser } from '@angular/platform-browser';
import { registerLocaleData } from '@angular/common';
import localeBs from '@angular/common/locales/bs';
import { AppModule } from './app/app-module';

import 'zone.js'; // Razvoj softvera 1 setup, prethodno instalirati "npm install zone.js"

// Register Bosnian locale for currency and date formatting
registerLocaleData(localeBs, 'bs-BA');

platformBrowser().bootstrapModule(AppModule, {

})
  .catch(err => console.error(err));

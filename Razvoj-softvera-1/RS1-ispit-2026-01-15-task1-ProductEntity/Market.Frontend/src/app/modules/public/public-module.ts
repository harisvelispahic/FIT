import {NgModule} from '@angular/core';

import {PublicRoutingModule} from './public-routing-module';
import {PublicLayoutComponent} from './public-layout/public-layout.component';
import {PublicHomeComponent} from './public-home/public-home.component';
import {CartPageComponent} from './cart-page/cart-page.component';
import {SearchProductsComponent} from './search-products/search-products.component';
import {SharedModule} from '../shared/shared-module';


@NgModule({
  declarations: [
    PublicLayoutComponent,
    PublicHomeComponent,
    CartPageComponent,
    SearchProductsComponent
  ],
  imports: [
    SharedModule,
    PublicRoutingModule,
  ]
})
export class PublicModule { }

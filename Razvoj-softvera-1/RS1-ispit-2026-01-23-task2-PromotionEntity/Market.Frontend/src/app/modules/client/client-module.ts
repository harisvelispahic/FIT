import {NgModule} from '@angular/core';

import {ClientRoutingModule} from './client-routing-module';
import {ClientOrdersComponent} from './client-orders/client-orders.component';
import {ClientOrderDetailsComponent} from './client-order-details/client-order-details.component';
import {SharedModule} from '../shared/shared-module';


@NgModule({
  declarations: [
    ClientOrdersComponent,
    ClientOrderDetailsComponent
  ],
  imports: [
    SharedModule,
    ClientRoutingModule
  ]
})
export class ClientModule { }

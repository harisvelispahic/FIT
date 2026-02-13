import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ClientOrdersComponent } from './client-orders/client-orders.component';
import { ClientOrderDetailsComponent } from './client-order-details/client-order-details.component';

const routes: Routes = [
  { path: '', redirectTo: 'orders', pathMatch: 'full' },
  { path: 'orders', component: ClientOrdersComponent },
  { path: 'orders/:id', component: ClientOrderDetailsComponent }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class ClientRoutingModule { }

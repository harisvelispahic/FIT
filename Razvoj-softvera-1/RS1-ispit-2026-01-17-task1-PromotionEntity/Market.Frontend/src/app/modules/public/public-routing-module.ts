import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { PublicLayoutComponent } from './public-layout/public-layout.component';
import { PublicHomeComponent } from './public-home/public-home.component';
import { CartPageComponent } from './cart-page/cart-page.component';
import { SearchProductsComponent } from './search-products/search-products.component';

const routes: Routes = [
  {
    path: '',
    component: PublicLayoutComponent,
    children: [
      {
        path: '',
        component: PublicHomeComponent
      },
      {
        path: 'cart',
        component: CartPageComponent
      },
      {
        path: 'search',
        component: SearchProductsComponent
      },
      { path: '**', redirectTo: '' }
    ]
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class PublicRoutingModule {}

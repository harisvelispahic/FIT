import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { AdminLayoutComponent } from './admin-layout/admin-layout.component';
import { ProductsComponent } from './catalogs/products/products.component';
import { ProductsAddComponent } from './catalogs/products/products-add/products-add.component';
import { ProductsEditComponent } from './catalogs/products/products-edit/products-edit.component';
import { ProductCategoriesComponent } from './catalogs/product-categories/product-categories.component';
import { AdminOrdersComponent } from './orders/admin-orders.component';
import { OrderEditComponent } from './orders/order-edit/order-edit.component';
import { AdminSettingsComponent } from './admin-settings/admin-settings.component';
import { ProductCategories2Component } from './catalogs/product-categories-2/product-categories-2.component';
import { ProductCategories2UpsertComponent } from './catalogs/product-categories-2/product-categories-2-upsert/product-categories-2-upsert.component';

const routes: Routes = [
  {
    path: '',
    component: AdminLayoutComponent,
    children: [
      // PRODUCTS
      {
        path: 'products',
        component: ProductsComponent,
      },
      {
        path: 'products/add',
        component: ProductsAddComponent,
      },
      {
        path: 'products/:id/edit',
        component: ProductsEditComponent,
      },

      // PRODUCT CATEGORIES
      {
        path: 'product-categories',
        component: ProductCategoriesComponent,
      },

      // PRODUCT CATEGORIES 2
      {
        path: 'product-categories-2',
        component: ProductCategories2Component,
      },

      {
        path: 'product-categories-2/add',
        component: ProductCategories2UpsertComponent,
      },

      {
        path: 'product-categories-2/edit/:id',
        component: ProductCategories2UpsertComponent,
      },

      // ORDERS
      {
        path: 'orders',
        component: AdminOrdersComponent,
      },
      {
        path: 'orders/:id/edit',
        component: OrderEditComponent,
      },

      // SETTINGS
      {
        path: 'settings',
        component: AdminSettingsComponent,
      },

      // default admin route → /admin/products
      {
        path: '',
        redirectTo: 'products',
        pathMatch: 'full',
      },
    ],
  },
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class AdminRoutingModule {}

import { Component, inject } from '@angular/core';
import { FormControl } from '@angular/forms';
import { Router } from '@angular/router';
import { CartService } from '../../../core/services/cart/cart.service';
import { CurrentUserService } from '../../../core/services/auth/current-user.service';
import { OrdersApiService } from '../../../api-services/orders/orders-api.service';
import { CreateOrderCommand } from '../../../api-services/orders/orders-api.models';
import { ToasterService } from '../../../core/services/toaster.service';

@Component({
  selector: 'app-cart-page',
  standalone: false,
  templateUrl: './cart-page.component.html',
  styleUrl: './cart-page.component.scss'
})
export class CartPageComponent {
  cart = inject(CartService);
  private currentUser = inject(CurrentUserService);
  private ordersApi = inject(OrdersApiService);
  private router = inject(Router);
  private toaster = inject(ToasterService);

  noteControl = new FormControl('');
  checkingOut = false;

  incrementQuantity(productId: number, currentQty: number): void {
    this.cart.setQuantity(productId, Math.min(currentQty + 1, 999));
  }

  decrementQuantity(productId: number, currentQty: number): void {
    this.cart.setQuantity(productId, Math.max(currentQty - 1, 1));
  }

  onQuantityInput(productId: number, value: string): void {
    const qty = parseInt(value, 10);
    if (!isNaN(qty)) {
      this.cart.setQuantity(productId, qty);
    }
  }

  removeItem(productId: number): void {
    this.cart.remove(productId);
    this.toaster.success('Proizvod uklonjen iz korpe', 2000);
  }

  checkout(): void {
    if (this.checkingOut) return;

    // Check authentication
    if (!this.currentUser.isAuthenticated()) {
      this.router.navigate(['/auth/login'], {
        queryParams: { returnUrl: '/cart' }
      });
      return;
    }

    // Check if cart is empty
    if (this.cart.items().length === 0) {
      this.toaster.error('Korpa je prazna');
      return;
    }

    this.checkingOut = true;

    const payload: CreateOrderCommand = {
      note: this.noteControl.value || null,
      items: this.cart.items().map(item => ({
        productId: item.productId,
        quantity: item.quantity
      }))
    };

    this.ordersApi.create(payload).subscribe({
      next: (orderId) => {
        this.toaster.success('Narudžba uspješno kreirana', 2000);
        this.cart.clear();
        this.noteControl.setValue('');
        this.checkingOut = false;
        this.router.navigate(['/client/orders', orderId]);
      },
      error: (err) => {
        this.checkingOut = false;
        const message = err.error?.message || err.message || 'Greška pri kreiranju narudžbe';
        this.toaster.error(message);
      }
    });
  }

  getTotalQuantity(): number {
    return this.cart.items().reduce((total, item) => total + item.quantity, 0);
  }

  continueShopping(): void {
    this.router.navigate(['/']);
  }
}

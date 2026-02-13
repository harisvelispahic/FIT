import { Component, inject, computed } from '@angular/core';
import { CurrentUserService } from '../../../core/services/auth/current-user.service';
import { CartService } from '../../../core/services/cart/cart.service';

@Component({
  selector: 'app-public-layout',
  standalone: false,
  templateUrl: './public-layout.component.html',
  styleUrl: './public-layout.component.scss',
})
export class PublicLayoutComponent {
  private currentUserService = inject(CurrentUserService);
  private cartService = inject(CartService);

  currentUser = this.currentUserService.currentUser;
  isAuthenticated = this.currentUserService.isAuthenticated;
  cartCount = this.cartService.itemCount;
}

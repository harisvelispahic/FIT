import { Injectable, signal, computed } from '@angular/core';
import { CartItem } from './cart.models';

@Injectable({ providedIn: 'root' })
export class CartService {
  private readonly STORAGE_KEY = 'market_cart_v1';
  private cartItems = signal<CartItem[]>([]);

  constructor() {
    this.loadFromStorage();
  }

  /**
   * Add product to cart. If already exists, increment quantity.
   */
  add(product: { id: number; name: string; price: number }, qty = 1): void {
    const items = this.cartItems();
    const existing = items.find(i => i.productId === product.id);
    
    if (existing) {
      // Increment existing item quantity (clamp to max 999)
      existing.quantity = Math.min(existing.quantity + qty, 999);
    } else {
      // Add new item
      items.push({
        productId: product.id,
        name: product.name,
        price: product.price,
        quantity: Math.max(1, Math.min(qty, 999))
      });
    }
    
    this.cartItems.set([...items]);
    this.saveToStorage();
  }

  /**
   * Set exact quantity for a product (clamp 1-999)
   */
  setQuantity(productId: number, qty: number): void {
    const items = this.cartItems();
    const item = items.find(i => i.productId === productId);
    
    if (item) {
      item.quantity = Math.max(1, Math.min(qty, 999));
      this.cartItems.set([...items]);
      this.saveToStorage();
    }
  }

  /**
   * Remove product from cart
   */
  remove(productId: number): void {
    const items = this.cartItems().filter(i => i.productId !== productId);
    this.cartItems.set(items);
    this.saveToStorage();
  }

  /**
   * Clear entire cart
   */
  clear(): void {
    this.cartItems.set([]);
    localStorage.removeItem(this.STORAGE_KEY);
  }

  // Readonly signals for components
  items = this.cartItems.asReadonly();
  
  itemCount = computed(() => this.cartItems().length);
  
  total = computed(() => 
    this.cartItems().reduce((sum, item) => sum + (item.price * item.quantity), 0)
  );

  private loadFromStorage(): void {
    const data = localStorage.getItem(this.STORAGE_KEY);
    if (data) {
      try {
        const items = JSON.parse(data) as CartItem[];
        this.cartItems.set(items);
      } catch (error) {
        console.error('Failed to load cart from storage', error);
      }
    }
  }

  private saveToStorage(): void {
    localStorage.setItem(this.STORAGE_KEY, JSON.stringify(this.cartItems()));
  }
}

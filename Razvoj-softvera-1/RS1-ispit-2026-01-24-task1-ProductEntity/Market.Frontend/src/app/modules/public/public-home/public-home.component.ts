import { Component, OnInit, inject } from '@angular/core';
import { CatalogApiService } from '../../../api-services/catalog/catalog-api.service';
import { CatalogHomeDto } from '../../../api-services/catalog/catalog-api.model';
import { CartService } from '../../../core/services/cart/cart.service';
import { ToasterService } from '../../../core/services/toaster.service';

@Component({
  selector: 'app-public-home',
  standalone: false,
  templateUrl: './public-home.component.html',
  styleUrl: './public-home.component.scss'
})
export class PublicHomeComponent implements OnInit {
  private catalogApi = inject(CatalogApiService);
  private cart = inject(CartService);
  private toaster = inject(ToasterService);

  catalogHome: CatalogHomeDto | null = null;
  loading = true;
  error = false;

  ngOnInit(): void {
    this.loadCatalogHome();
  }

  loadCatalogHome(): void {
    this.loading = true;
    this.error = false;

    this.catalogApi.getHome().subscribe({
      next: (data) => {
        console.log('🔍 CATALOG HOME RESPONSE:', data);
        console.log('📦 Products:', data.newestProducts?.length || 0);
        console.log('🎯 Promotions:', data.promotions?.length || 0);
        console.log('📁 Categories:', data.categories?.length || 0);

        this.catalogHome = data;
        this.loading = false;
      },
      error: (err) => {
        console.error('❌ CATALOG HOME ERROR:', err);
        this.error = true;
        this.loading = false;
        this.toaster.error('Greška pri učitavanju kataloga');
      }
    });
  }

  addToCart(product: { id: number; name: string; price: number }): void {
    this.cart.add(product, 1);
    this.toaster.success('Proizvod dodan u korpu', 2000);
  }

  scrollToProducts(): void {
    const element = document.getElementById('products');
    if (element) {
      element.scrollIntoView({ behavior: 'smooth', block: 'start' });
    }
  }
}

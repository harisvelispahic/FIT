import { Injectable, inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { environment } from '../../../environments/environment';
import { CatalogHomeDto } from './catalog-api.model';

@Injectable({
  providedIn: 'root'
})
export class CatalogApiService {
  private readonly baseUrl = `${environment.apiUrl}/catalog`;
  private http = inject(HttpClient);

  /**
   * GET /catalog/home
   * Retrieve catalog home data with promotions, categories, newest products, and stats
   */
  getHome(categoryLimit = 8, productLimit = 12): Observable<CatalogHomeDto> {
    return this.http.get<CatalogHomeDto>(`${this.baseUrl}/home`, {
      params: {
        categoryLimit: categoryLimit.toString(),
        productLimit: productLimit.toString()
      }
    });
  }
}

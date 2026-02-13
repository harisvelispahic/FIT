import { inject, Injectable } from '@angular/core';
import { environment } from '../../../environments/environment';
import { HttpClient } from '@angular/common/http';
import {
  CreateProductCategory2Command,
  GetProductCategory2ByIdQueryDto,
  ListProductCategories2Query,
  ListProductCategories2Response,
  UpdateProductCategory2Command,
} from './product-categories-2-api.model';
import { Observable } from 'rxjs/internal/Observable';
import { buildHttpParams } from '../../core/models/build-http-params';

@Injectable({
  providedIn: 'root',
})
export class ProductCategories2ApiService {
  private readonly baseUrl = `${environment.apiUrl}/ProductCategories2`;
  private http = inject(HttpClient);

  /**
   * GET /Products
   * List products with optional query parameters.
   */
  list(request?: ListProductCategories2Query): Observable<ListProductCategories2Response> {
    const params = request ? buildHttpParams(request as any) : undefined;

    return this.http.get<ListProductCategories2Response>(this.baseUrl, {
      params,
    });
  }

  /**
   * GET /Products/{id}
   * Get a single product by ID.
   */
  getById(id: number): Observable<GetProductCategory2ByIdQueryDto> {
    return this.http.get<GetProductCategory2ByIdQueryDto>(`${this.baseUrl}/${id}`);
  }

  /**
   * POST /Products
   * Create a new product.
   * @returns ID of the newly created product
   */
  create(payload: CreateProductCategory2Command): Observable<number> {
    return this.http.post<number>(this.baseUrl, payload);
  }

  /**
   * PUT /Products/{id}
   * Update an existing product.
   */
  update(id: number, payload: UpdateProductCategory2Command): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}`, payload);
  }

  /**
   * DELETE /Products/{id}
   * Delete a product.
   */
  delete(id: number): Observable<void> {
    return this.http.delete<void>(`${this.baseUrl}/${id}`);
  }
}

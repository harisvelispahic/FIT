import { inject, Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { environment } from '../../../environments/environment';
import {
  ListProductCategories2Request,
  ListProductCategories2Response,
  GetProductCategory2ByIdQueryDto,
  CreateProductCategory2Command,
  UpdateProductCategory2Command,
} from './product-categories-2-api.models';
import { buildHttpParams } from '../../core/models/build-http-params';

@Injectable({
  providedIn: 'root',
})
export class ProductCategories2ApiService {
  private readonly baseUrl = `${environment.apiUrl}/ProductCategories2`;
  private http = inject(HttpClient);

  /**
   * GET /ProductCategories2
   * List ProductCategories2 with optional query parameters.
   */
  list(request?: ListProductCategories2Request): Observable<ListProductCategories2Response> {
    const params = request ? buildHttpParams(request as any) : undefined;

    return this.http.get<ListProductCategories2Response>(this.baseUrl, {
      params,
    });
  }

  /**
   * GET /ProductCategories2/{id}
   * Get a single product by ID.
   */
  getById(id: number): Observable<GetProductCategory2ByIdQueryDto> {
    return this.http.get<GetProductCategory2ByIdQueryDto>(`${this.baseUrl}/${id}`);
  }

  /**
   * POST /ProductCategories2
   * Create a new product.
   * @returns ID of the newly created product
   */
  create(payload: CreateProductCategory2Command): Observable<number> {
    return this.http.post<number>(this.baseUrl, payload);
  }

  /**
   * PUT /ProductCategories2/{id}
   * Update an existing product.
   */
  update(id: number, payload: UpdateProductCategory2Command): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}`, payload);
  }

  /**
   * DELETE /ProductCategories2/{id}
   * Delete a product.
   */
  delete(id: number): Observable<void> {
    return this.http.delete<void>(`${this.baseUrl}/${id}`);
  }

  /**
   * PUT /ProductCategories/{id}/disable
   * Disable a category.
   */
  disable(id: number): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}/disable`, {});
  }

  /**
   * PUT /ProductCategories/{id}/enable
   * Enable a category.
   */
  enable(id: number): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}/enable`, {});
  }
}

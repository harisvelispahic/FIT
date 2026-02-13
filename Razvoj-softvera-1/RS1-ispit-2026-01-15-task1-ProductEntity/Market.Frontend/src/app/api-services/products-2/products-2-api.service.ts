import { inject, Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { environment } from '../../../environments/environment';
import { buildHttpParams } from '../../core/models/build-http-params';
import {
  CreateProduct2Command,
  GetProduct2ByIdQueryDto,
  ListProducts2Request,
  ListProducts2Response,
  UpdateProduct2Command,
} from './products-2-api.model';

@Injectable({
  providedIn: 'root',
})
export class Products2ApiService {
  private readonly baseUrl = `${environment.apiUrl}/Products2`;
  private http = inject(HttpClient);

  /**
   * GET /ProductCategories
   * List categories with optional query parameters.
   */
  list(request?: ListProducts2Request): Observable<ListProducts2Response> {
    const params = request ? buildHttpParams(request as any) : undefined;

    return this.http.get<ListProducts2Response>(this.baseUrl, {
      params,
    });
  }

  /**
   * GET /ProductCategories/{id}
   * Get a single category by ID.
   */
  getById(id: number): Observable<GetProduct2ByIdQueryDto> {
    return this.http.get<GetProduct2ByIdQueryDto>(`${this.baseUrl}/${id}`);
  }

  /**
   * POST /ProductCategories
   * Create a new category.
   * @returns ID of the newly created category
   */
  create(payload: CreateProduct2Command): Observable<number> {
    return this.http.post<number>(this.baseUrl, payload);
  }

  /**
   * PUT /ProductCategories/{id}
   * Update an existing category.
   */
  update(id: number, payload: UpdateProduct2Command): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}`, payload);
  }

  /**
   * DELETE /ProductCategories/{id}
   * Delete a category.
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

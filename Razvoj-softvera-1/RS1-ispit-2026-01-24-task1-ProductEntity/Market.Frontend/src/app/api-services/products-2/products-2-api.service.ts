import { inject, Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { environment } from '../../../environments/environment';
import {
  ListProducts2Request,
  ListProducts2Response,
  GetProduct2ByIdQueryDto,
  CreateProduct2Command,
  UpdateProduct2Command,
} from './products-2-api.model';
import { buildHttpParams } from '../../core/models/build-http-params';

@Injectable({
  providedIn: 'root',
})
export class Products2ApiService {
  private readonly baseUrl = `${environment.apiUrl}/Products2`;
  private http = inject(HttpClient);

  /**
   * GET /Products2
   * List categories with optional query parameters.
   */
  list(request?: ListProducts2Request): Observable<ListProducts2Response> {
    const params = request ? buildHttpParams(request as any) : undefined;

    return this.http.get<ListProducts2Response>(this.baseUrl, {
      params,
    });
  }

  /**
   * GET /Products2/{id}
   * Get a single category by ID.
   */
  getById(id: number): Observable<GetProduct2ByIdQueryDto> {
    return this.http.get<GetProduct2ByIdQueryDto>(`${this.baseUrl}/${id}`);
  }

  /**
   * POST /Products2
   * Create a new category.
   * @returns ID of the newly created category
   */
  create(payload: CreateProduct2Command): Observable<number> {
    return this.http.post<number>(this.baseUrl, payload);
  }

  /**
   * PUT /Products2/{id}
   * Update an existing category.
   */
  update(id: number, payload: UpdateProduct2Command): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}`, payload);
  }

  /**
   * DELETE /Products2/{id}
   * Delete a category.
   */
  delete(id: number): Observable<void> {
    return this.http.delete<void>(`${this.baseUrl}/${id}`);
  }

  /**
   * PUT /Products2/{id}/disable
   * Disable a category.
   */
  disable(id: number): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}/disable`, {});
  }

  /**
   * PUT /Products2/{id}/enable
   * Enable a category.
   */
  enable(id: number): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}/enable`, {});
  }
}

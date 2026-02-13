import { inject, Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { environment } from '../../../environments/environment';
import {
  ListPromotionsRequest,
  ListPromotionsResponse,
  GetPromotionByIdQueryDto,
  CreatePromotionCommand,
  UpdatePromotionCommand,
} from './promotions-api.model';
import { buildHttpParams } from '../../core/models/build-http-params';

@Injectable({
  providedIn: 'root',
})
export class PromotionsApiService {
  private readonly baseUrl = `${environment.apiUrl}/Promotions`;
  private http = inject(HttpClient);

  /**
   * GET /Promotions
   * List categories with optional query parameters.
   */
  list(request?: ListPromotionsRequest): Observable<ListPromotionsResponse> {
    const params = request ? buildHttpParams(request as any) : undefined;

    return this.http.get<ListPromotionsResponse>(this.baseUrl, {
      params,
    });
  }

  /**
   * GET /Promotions/{id}
   * Get a single category by ID.
   */
  getById(id: number): Observable<GetPromotionByIdQueryDto> {
    return this.http.get<GetPromotionByIdQueryDto>(`${this.baseUrl}/${id}`);
  }

  /**
   * POST /Promotions
   * Create a new category.
   * @returns ID of the newly created category
   */
  create(payload: CreatePromotionCommand): Observable<number> {
    return this.http.post<number>(this.baseUrl, payload);
  }

  /**
   * PUT /Promotions/{id}
   * Update an existing category.
   */
  update(id: number, payload: UpdatePromotionCommand): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}`, payload);
  }

  /**
   * DELETE /Promotions/{id}
   * Delete a category.
   */
  delete(id: number): Observable<void> {
    return this.http.delete<void>(`${this.baseUrl}/${id}`);
  }

  /**
   * PUT /Promotions/{id}/disable
   * Disable a category.
   */
  disable(id: number): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}/disable`, {});
  }

  /**
   * PUT /Promotions/{id}/enable
   * Enable a category.
   */
  enable(id: number): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}/enable`, {});
  }
}

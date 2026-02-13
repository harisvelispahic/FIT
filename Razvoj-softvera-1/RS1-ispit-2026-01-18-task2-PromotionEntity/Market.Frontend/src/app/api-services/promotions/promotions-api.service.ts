import { inject, Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { environment } from '../../../environments/environment';
import {
  ListPromotionsRequest,
  ListPromotionsResponse,
  ListPromotionsWithItemsRequest,
  ListPromotionsWithItemsResponse,
  GetPromotionByIdQueryDto,
  CreatePromotionCommand,
  UpdatePromotionCommand,
} from './promotions-api.models';
import { buildHttpParams } from '../../core/models/build-http-params';

@Injectable({
  providedIn: 'root',
})
export class PromotionsApiService {
  private readonly baseUrl = `${environment.apiUrl}/Promotions`;
  private http = inject(HttpClient);

  /**
   * GET /Promotions
   * List Promotions with optional query parameters.
   * Returns basic Promotion info without items.
   */
  list(request?: ListPromotionsRequest): Observable<ListPromotionsResponse> {
    const params = request ? buildHttpParams(request as any) : undefined;

    return this.http.get<ListPromotionsResponse>(this.baseUrl, {
      params,
    });
  }

  /**
   * GET /Promotions/with-items
   * List Promotions with items included.
   * Use this when you need to display Promotion items in the list.
   */
  listWithItems(
    request?: ListPromotionsWithItemsRequest,
  ): Observable<ListPromotionsWithItemsResponse> {
    const params = request ? buildHttpParams(request as any) : undefined;

    return this.http.get<ListPromotionsWithItemsResponse>(`${this.baseUrl}/with-items`, {
      params,
    });
  }

  /**
   * GET /Promotions/{id}
   * Get a single Promotion by ID with full details including items.
   */
  getById(id: number): Observable<GetPromotionByIdQueryDto> {
    return this.http.get<GetPromotionByIdQueryDto>(`${this.baseUrl}/${id}`);
  }

  /**
   * POST /Promotions
   * Create a new Promotion.
   * @returns ID of the newly created Promotion
   */
  create(payload: CreatePromotionCommand): Observable<number> {
    return this.http.post<number>(this.baseUrl, payload);
  }

  /**
   * PUT /Promotions/{id}
   * Update an existing Promotion.
   * Can update Promotion note and items.
   */
  update(id: number, payload: UpdatePromotionCommand): Observable<void> {
    return this.http.put<void>(`${this.baseUrl}/${id}`, payload);
  }

  delete(id: number): Observable<void> {
    return this.http.delete<void>(`${this.baseUrl}/${id}`);
  }
}

import { PageResult } from '../../core/models/paging/page-result';
import { BasePagedQuery } from '../../core/models/paging/base-paged-query';

// === QUERIES (READ) ===

/**
 * Query parameters for GET /Promotions
 * Corresponds to: ListPromotionsQuery.cs
 */
export class ListPromotionsRequest extends BasePagedQuery {
  search?: string | null;
  isActive?: boolean | null;
  // Future filters: status?, dateFrom?, dateTo?, userId?
  constructor() {
    super();
  }
}

/**
 * Query parameters for GET /Promotions/with-items
 * Corresponds to: ListPromotionsWithItemsQuery.cs
 */
export class ListPromotionsWithItemsRequest extends BasePagedQuery {
  search?: string | null;
}

/**
 * Response item for GET /Promotions
 * Corresponds to: ListPromotionsQueryDto.cs
 */
export interface ListPromotionsQueryDto {
  id: number;
  title: string;
  imageUrl: string;
  targetUrl: string;
  isActive: boolean;
  startsAtUtc: Date;
  endsAtUtc: Date;
  sortOrder: number;
}

/**
 * Promotion item in list with items
 */
export interface ListPromotionsWithItemsQueryDtoItem {
  id: number;
  productId: number;
  productName: string;
  productCategoryName: string;
  discountPercent: number;
}

/**
 * Response item for GET /Promotions/with-items
 * Corresponds to: ListPromotionsWithItemsQueryDto.cs
 */
export interface ListPromotionsWithItemsQueryDto {
  id: number;
  title: string;
  imageUrl: string;
  targetUrl: string;
  isActive: boolean;
  startsAtUtc: Date;
  endsAtUtc: Date;
  sortOrder: number;

  items: ListPromotionsWithItemsQueryDtoItem[];
}

/**
 * Promotion item in GetById response
 */
export interface GetPromotionByIdQueryDtoItem {
  id: number;
  productId: number;
  productName: string;
  productCategoryName: string;
  discountPercent: number;
}

/**
 * Response for GET /Promotions/{id}
 * Corresponds to: GetPromotionByIdQueryDto.cs
 */
export interface GetPromotionByIdQueryDto {
  id: number;
  title: string;
  imageUrl: string;
  targetUrl: string;
  isActive: boolean;
  startsAtUtc: Date;
  endsAtUtc: Date;
  sortOrder: number;

  promotionItems: GetPromotionByIdQueryDtoItem[];
}

/**
 * Paged response for GET /Promotions
 */
export type ListPromotionsResponse = PageResult<ListPromotionsQueryDto>;

/**
 * Paged response for GET /Promotions/with-items
 */
export type ListPromotionsWithItemsResponse = PageResult<ListPromotionsWithItemsQueryDto>;

// === COMMANDS (WRITE) ===

/**
 * Promotion item for create command
 */
export interface CreatePromotionCommandItem {
  productId: number;
  discountPercent: number;
}

/**
 * Command for POST /Promotions
 * Corresponds to: CreatePromotionCommand.cs
 */
export interface CreatePromotionCommand {
  title: string;
  imageUrl: string;
  targetUrl: string;
  isActive: boolean;
  startsAtUtc: Date;
  endsAtUtc: Date;
  sortOrder: number;

  promotionItems: CreatePromotionCommandItem[];
}

/**
 * Promotion item for update command
 */
export interface UpdatePromotionCommandItem {
  id?: number; // Optional - if present, updates existing item
  productId: number;
  discountPercent: number;
}

/**
 * Command for PUT /Promotions/{id}
 * Corresponds to: UpdatePromotionCommand.cs
 */
export interface UpdatePromotionCommand {
  title: string;
  imageUrl: string;
  targetUrl: string;
  isActive: boolean;
  startsAtUtc: Date;
  endsAtUtc: Date;
  sortOrder: number;

  promotionItems?: UpdatePromotionCommandItem[];
}

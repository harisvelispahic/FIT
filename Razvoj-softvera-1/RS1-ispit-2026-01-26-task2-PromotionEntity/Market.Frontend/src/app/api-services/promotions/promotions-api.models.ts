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
 * Product info in Promotion items
 */
export interface ListPromotionsWithItemsQueryDtoProduct {
  productId: number;
  productName: string;
  productCategoryName: string;
}

/**
 * Promotion item in list with items
 */
export interface ListPromotionsWithItemsQueryDtoPromotionItem {
  id: number;
  productId: number;
  product: ListPromotionsWithItemsQueryDtoProduct;
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

  promotionItems: ListPromotionsWithItemsQueryDtoPromotionItem[];
}

/**
 * Product info in GetById Promotion item
 */
export interface GetByIdPromotionQueryDtoProduct {
  productId: number;
  productName: string | null;
  productCategoryName: string | null;
}

/**
 * Promotion item in GetById response
 */
export interface GetByIdPromotionQueryDtoPromotionItem {
  id: number;
  productId: number;
  product: GetByIdPromotionQueryDtoProduct;
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

  promotionItems: GetByIdPromotionQueryDtoPromotionItem[];
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
export interface CreatePromotionCommandPromotionItem {
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

  promotionItems: CreatePromotionCommandPromotionItem[];
}

/**
 * Promotion item for update command
 */
export interface UpdatePromotionCommandPromotionItem {
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

  promotionItems?: UpdatePromotionCommandPromotionItem[];
}

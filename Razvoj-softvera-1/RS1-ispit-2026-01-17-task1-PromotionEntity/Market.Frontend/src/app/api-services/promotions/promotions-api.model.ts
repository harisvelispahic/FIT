import { BasePagedQuery } from '../../core/models/paging/base-paged-query';
import { PageResult } from '../../core/models/paging/page-result';

// === QUERIES (READ) ===

/**
 * Query parameters for GET /Promotions
 * Corresponds to: ListPromotionsQuery.cs
 */
export class ListPromotionsRequest extends BasePagedQuery {
  search?: string | null;
  onlyActive?: boolean | null;
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
}

/**
 * Paged response for GET /Promotions
 */
export type ListPromotionsResponse = PageResult<ListPromotionsQueryDto>;

// === COMMANDS (WRITE) ===

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
}

/**
 * Command for PUT /Promotions/{id}
 * Corresponds to: UpdatePromotionCommand.cs
 */
export interface UpdatePromotionCommand {
  id: number;
  title: string;
  imageUrl: string;
  targetUrl: string;
  isActive: boolean;
  startsAtUtc: Date;
  endsAtUtc: Date;
  sortOrder: number;
}

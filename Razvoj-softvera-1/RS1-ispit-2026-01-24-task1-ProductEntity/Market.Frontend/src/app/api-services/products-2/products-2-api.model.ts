import { BasePagedQuery } from '../../core/models/paging/base-paged-query';
import { PageResult } from '../../core/models/paging/page-result';

// === QUERIES (READ) ===

/**
 * Query parameters for GET /Products2
 * Corresponds to: ListProducts2Query.cs
 */
export class ListProducts2Request extends BasePagedQuery {
  search?: string | null;
  onlyEnabled?: boolean | null;
}

/**
 * Response item for GET /Products2
 * Corresponds to: ListProducts2QueryDto.cs
 */
export interface ListProducts2QueryDto {
  id: number;
  name: string;
  description: string;
  price: number;
  stockQuantity: number;
  categoryId: number;
  categoryName: string;
  isEnabled: boolean;
}

/**
 * Response for GET /Products2/{id}
 * Corresponds to: GetProduct2ByIdQueryDto.cs
 */
export interface GetProduct2ByIdQueryDto {
  id: number;
  name: string;
  description: string;
  price: number;
  stockQuantity: number;
  categoryId: number;
  categoryName: string;
  isEnabled: boolean;
}

/**
 * Paged response for GET /Products2
 */
export type ListProducts2Response = PageResult<ListProducts2QueryDto>;

// === COMMANDS (WRITE) ===

/**
 * Command for POST /Products2
 * Corresponds to: CreateProduct2Command.cs
 */
export interface CreateProduct2Command {
  name: string;
  description: string;
  price: number;
  stockQuantity: number;
  categoryId: number;
  isEnabled: boolean;
}

/**
 * Command for PUT /Products2/{id}
 * Corresponds to: UpdateProduct2Command.cs
 */
export interface UpdateProduct2Command {
  id: number;
  name: string;
  description: string;
  price: number;
  stockQuantity: number;
  categoryId: number;
  isEnabled: boolean;
}

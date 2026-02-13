import { BasePagedQuery } from '../../core/models/paging/base-paged-query';
import { PageResult } from '../../core/models/paging/page-result';

// === QUERIES (READ) ===

/**
 * Query parameters for GET /ProductCategories
 * Corresponds to: ListProductCategoriesQuery.cs
 */
export class ListProducts2Request extends BasePagedQuery {
  search?: string | null;
  onlyEnabled?: boolean | null;
}

/**
 * Response item for GET /ProductCategories
 * Corresponds to: ListProductCategoriesQueryDto.cs
 */
export interface ListProducts2QueryDto {
  id: number;
  name: string;
  description: string;
  price: number;
  stockQuantity: number;
  categoryName: string;
  isEnabled: boolean;
}

/**
 * Response for GET /ProductCategories/{id}
 * Corresponds to: GetProductCategoryByIdQueryDto.cs
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
 * Paged response for GET /ProductCategories
 */
export type ListProducts2Response = PageResult<ListProducts2QueryDto>;

// === COMMANDS (WRITE) ===

/**
 * Command for POST /ProductCategories
 * Corresponds to: CreateProductCategoryCommand.cs
 */
export interface CreateProduct2Command {
  name: string;
  description: string;
  price: number;
  categoryId: number;
}

/**
 * Command for PUT /ProductCategories/{id}
 * Corresponds to: UpdateProductCategoryCommand.cs
 */
export interface UpdateProduct2Command {
  id: number;
  name: string;
  description: string;
  price: number;
  categoryId: number;
}

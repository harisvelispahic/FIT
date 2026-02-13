import { PageResult } from '../../core/models/paging/page-result';
import { BasePagedQuery } from '../../core/models/paging/base-paged-query';

// === QUERIES (READ) ===

/**
 * Query parameters for GET /ProductCategories
 * Corresponds to: ListProductCategoriesQuery.cs
 */
export class ListProductCategories2Request extends BasePagedQuery {
  search?: string | null;
  onlyEnabled?: boolean;
  // Future filters: categoryId?, isEnabled?, priceMin?, priceMax?
}

/**
 * Response item for GET /ProductCategories
 * Corresponds to: ListProductCategoriesQueryDto.cs
 */
export interface ListProductCategories2QueryDto {
  id: number;
  name: string;
  isEnabled: boolean;
}

/**
 * Response for GET /ProductCategories/{id}
 * Corresponds to: GetProductByIdQueryDto.cs
 */
export interface GetProductCategory2ByIdQueryDto {
  id: number;
  name: string;
  isEnabled: boolean;
}

/**
 * Paged response for GET /ProductCategories
 */
export type ListProductCategories2Response = PageResult<ListProductCategories2QueryDto>;

// === COMMANDS (WRITE) ===

/**
 * Command for POST /ProductCategories
 * Corresponds to: CreateProductCategoryCommand.cs
 */
export interface CreateProductCategory2Command {
  name: string;
  isEnabled: boolean;
}

/**
 * Command for PUT /ProductCategories/{id}
 * Corresponds to: UpdateProductCategoryCommand.cs
 */
export interface UpdateProductCategory2Command {
  // id: number;
  name: string;
  isEnabled: boolean;
}

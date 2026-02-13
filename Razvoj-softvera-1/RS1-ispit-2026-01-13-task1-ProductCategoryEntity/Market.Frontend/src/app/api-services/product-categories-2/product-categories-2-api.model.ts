import { BasePagedQuery } from '../../core/models/paging/base-paged-query';
import { PageResult } from '../../core/models/paging/page-result';

export class ListProductCategories2Query extends BasePagedQuery {
  search?: string | null;
  onlyEnabled?: boolean | null;
}

export interface ListProductCategories2QueryDto {
  id: number;
  name: string;
  isEnabled: boolean;
}

export type ListProductCategories2Response = PageResult<ListProductCategories2QueryDto>;

export interface GetProductCategory2ByIdQueryDto {
  id: number;
  name: string;
  isEnabled: boolean;
}

export interface CreateProductCategory2Command {
  name: string;
  isEnabled: boolean;
}

export interface UpdateProductCategory2Command {
  name: string;
  isEnabled: boolean;
}

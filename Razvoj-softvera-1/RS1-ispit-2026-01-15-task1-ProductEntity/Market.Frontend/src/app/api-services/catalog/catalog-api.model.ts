// DTOs matching backend CatalogHomeDto structure

export interface CatalogHomeDto {
  promotions: CatalogPromotionDto[];
  categories: CatalogCategoryDto[];
  newestProducts: CatalogProductDto[];
  stats: CatalogHomeStatsDto;
}

export interface CatalogPromotionDto {
  id: number;
  title: string;
  imageUrl: string;
  targetUrl: string | null;
  sortOrder: number;
}

export interface CatalogCategoryDto {
  id: number;
  name: string;
}

export interface CatalogProductDto {
  id: number;
  name: string;
  description: string | null;
  price: number;
  categoryId: number;
  categoryName: string;
}

export interface CatalogHomeStatsDto {
  totalCategories: number;
  totalProducts: number;
}

import { Component, inject, OnInit } from '@angular/core';
import { BaseListPagedComponent } from '../../../../core/components/base-classes/base-list-paged-component';
import {
  ListProductCategories2Query,
  ListProductCategories2QueryDto,
} from '../../../../api-services/product-categories-2/product-categories-2-api.model';
import { DialogHelperService } from '../../../shared/services/dialog-helper.service';
import { ProductCategoriesApiService } from '../../../../api-services/product-categories/product-categories-api.service';
import { MatDialog } from '@angular/material/dialog';
import { ToasterService } from '../../../../core/services/toaster.service';
import { ProductCategories2ApiService } from '../../../../api-services/product-categories-2/product-categories-2-api.service';
import { DialogButton } from '../../../shared/models/dialog-config.model';

@Component({
  selector: 'app-product-categories-2',
  standalone: false,
  templateUrl: './product-categories-2.component.html',
  styleUrl: './product-categories-2.component.scss',
})
export class ProductCategories2Component
  extends BaseListPagedComponent<ListProductCategories2QueryDto, ListProductCategories2Query>
  implements OnInit
{
  private api = inject(ProductCategories2ApiService);
  private dialog = inject(MatDialog);
  private toaster = inject(ToasterService);
  private dialogHelper = inject(DialogHelperService);

  public searchTerm?: string = '';
  public onlyAvailable: boolean = true;

  constructor() {
    super();
    this.request = new ListProductCategories2Query();
    this.request.onlyEnabled = true;
  }

  ngOnInit(): void {
    this.initList();
  }

  protected override loadPagedData(): void {
    this.startLoading();

    this.api.list(this.request).subscribe({
      next: (response) => {
        this.handlePageResult(response);
        this.stopLoading();
      },
      error: (err) => {
        console.error('Load categories error:', err);
        this.stopLoading('Failed to load categories');
      },
    });
  }

  searchCategories() {
    this.request.search = this.searchTerm ? this.searchTerm : undefined;
    this.request.onlyEnabled = this.onlyAvailable;
    this.request.paging.page = 1;
    this.loadPagedData();
  }

  onDelete(category: ListProductCategories2QueryDto): void {
    this.dialogHelper.productCategory.confirmDelete(category.name).subscribe((result) => {
      if (result && result.button === DialogButton.DELETE) {
        this.performDelete(category);
      }
    });
  }

  private performDelete(category: ListProductCategories2QueryDto): void {
    this.startLoading();

    this.api.delete(category.id).subscribe({
      next: () => {
        this.dialogHelper.productCategory.showDeleteSuccess().subscribe();
        this.loadPagedData();
      },
      error: (err) => {
        this.stopLoading();

        const errorMessage = this.extractErrorMessage(err);

        // Show error dialog instead of toast
        this.dialogHelper
          .showError('DIALOGS.TITLES.ERROR', 'PRODUCT_CATEGORIES.DIALOGS.ERROR_DELETE')
          .subscribe();

        console.error('Delete category error:', err);
      },
    });
  }

  private extractErrorMessage(err: any): string | null {
    if (err?.error) {
      if (typeof err.error === 'string') {
        return err.error;
      }

      if (err.error.message) {
        return err.error.message;
      }

      if (err.error.title) {
        return err.error.title;
      }

      if (err.error.errors && typeof err.error.errors === 'object') {
        const errors = Object.values(err.error.errors).flat();
        if (errors.length > 0) {
          return errors.join(', ');
        }
      }
    }

    if (err?.message) {
      return err.message;
    }

    if (err?.statusText && err.statusText !== 'Unknown Error') {
      return err.statusText;
    }

    return null;
  }
}

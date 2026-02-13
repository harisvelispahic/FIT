import { Component, inject, OnInit } from '@angular/core';
import {
  ListProductCategories2QueryDto,
  ListProductCategories2Request,
} from '../../../../api-services/product-categories-2/product-categories-2-api.models';
import { BaseListPagedComponent } from '../../../../core/components/base-classes/base-list-paged-component';
import { ProductCategories2ApiService } from '../../../../api-services/product-categories-2/product-categories-2-api.service';
import { Router } from '@angular/router';
import { ToasterService } from '../../../../core/services/toaster.service';
import { DialogHelperService } from '../../../shared/services/dialog-helper.service';
import { DialogButton } from '../../../shared/models/dialog-config.model';

@Component({
  selector: 'app-product-categories-2',
  standalone: false,
  templateUrl: './product-categories-2.component.html',
  styleUrl: './product-categories-2.component.scss',
})
export class ProductCategories2Component
  extends BaseListPagedComponent<ListProductCategories2QueryDto, ListProductCategories2Request>
  implements OnInit
{
  private api = inject(ProductCategories2ApiService);
  private router = inject(Router);
  private toaster = inject(ToasterService);
  private dialogHelper = inject(DialogHelperService);

  constructor() {
    super();
    this.request = new ListProductCategories2Request();
    this.request.onlyEnabled = true;
  }

  ngOnInit(): void {
    this.initList();
  }

  protected loadPagedData(): void {
    this.startLoading();

    this.api.list(this.request).subscribe({
      next: (response) => {
        this.handlePageResult(response);
        this.stopLoading();
      },
      error: (err) => {
        this.stopLoading('Failed to load product categories 2');
        console.error('Load product categories 2 error:', err);
      },
    });
  }

  onSearch(): void {
    this.request.paging.page = 1;
    this.loadPagedData();
  }

  onToggleEnabledFilter(): void {
    this.request.paging.page = 1;
    this.loadPagedData();
  }

  onCreate(): void {
    this.router.navigate(['/admin/product-categories-2/add']);
  }

  onEdit(product: ListProductCategories2QueryDto): void {
    this.router.navigate(['/admin/product-categories-2/edit/', product.id]);
  }

  onDelete(product: ListProductCategories2QueryDto): void {
    this.dialogHelper.product.confirmDelete(product.name).subscribe((result) => {
      if (result && result.button === DialogButton.DELETE) {
        this.performDelete(product);
      }
    });
  }

  private performDelete(product: ListProductCategories2QueryDto): void {
    this.startLoading();

    this.api.delete(product.id).subscribe({
      next: () => {
        this.dialogHelper.product.showDeleteSuccess().subscribe();
        this.loadPagedData();
      },
      error: (err) => {
        this.stopLoading();

        this.dialogHelper
          .showError('DIALOGS.TITLES.ERROR', 'PRODUCTS.DIALOGS.ERROR_DELETE')
          .subscribe();

        console.error('Delete product error:', err);
      },
    });
  }

  onToggleStatus(category: ListProductCategories2QueryDto): void {
    this.startLoading();

    const apiAction = category.isEnabled
      ? this.api.disable(category.id)
      : this.api.enable(category.id);

    apiAction.subscribe({
      next: () => {
        const status = category.isEnabled ? 'disabled' : 'enabled';
        this.toaster.success(`Category ${status} successfully`);
        this.loadPagedData();
      },
      error: (err) => {
        this.stopLoading();

        const errorMessage = this.extractErrorMessage(err);

        if (err.status === 409) {
          // Business rule conflict - show dialog for important errors
          this.dialogHelper
            .showWarning(
              'DIALOGS.TITLES.WARNING',
              errorMessage || 'PRODUCT_CATEGORIES.DIALOGS.ERROR_TOGGLE',
              { name: category.name },
            )
            .subscribe();
        } else {
          // Generic error - just toast
          this.toaster.error(errorMessage || 'Failed to change category status');
        }

        console.error('Toggle status error:', err);
        this.loadPagedData();
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

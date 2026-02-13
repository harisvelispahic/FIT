import { Component, inject, OnInit } from '@angular/core';
import {
  ListProducts2QueryDto,
  ListProducts2Request,
} from '../../../../api-services/products-2/products-2-api.model';
import { BaseListPagedComponent } from '../../../../core/components/base-classes/base-list-paged-component';
import { ToasterService } from '../../../../core/services/toaster.service';
import { DialogHelperService } from '../../../shared/services/dialog-helper.service';
import { MatDialog } from '@angular/material/dialog';
import { Products2ApiService } from '../../../../api-services/products-2/products-2-api.service';
import { ActivatedRoute, Router } from '@angular/router';
import { DialogButton } from '../../../shared/models/dialog-config.model';

@Component({
  selector: 'app-products-2',
  standalone: false,
  templateUrl: './products-2.component.html',
  styleUrl: './products-2.component.scss',
})
export class Products2Component
  extends BaseListPagedComponent<ListProducts2QueryDto, ListProducts2Request>
  implements OnInit
{
  private api = inject(Products2ApiService);
  private dialog = inject(MatDialog);
  private toaster = inject(ToasterService);
  private dialogHelper = inject(DialogHelperService);
  private route = inject(ActivatedRoute);
  private router = inject(Router);

  constructor() {
    super();
    this.request = new ListProducts2Request();
    this.request.onlyEnabled = true;
  }

  ngOnInit(): void {
    this.loadPagedData();
  }

  protected loadPagedData(): void {
    this.startLoading();

    this.api.list(this.request).subscribe({
      next: (response) => {
        this.handlePageResult(response);
        this.stopLoading();
      },
      error: (err) => {
        this.toaster.error('Load categories error:', err);
        this.stopLoading('Failed to load categories');
      },
    });
  }

  onCreate() {
    this.router.navigate(['/admin/products-2/add']);
  }

  onEdit(id: number) {
    this.router.navigate(['/admin/products-2/edit', id]);
  }

  onDelete(category: ListProducts2QueryDto): void {
    this.dialogHelper.productCategory.confirmDelete(category.name).subscribe((result) => {
      if (result && result.button === DialogButton.DELETE) {
        this.performDelete(category);
      }
    });
  }

  private performDelete(category: ListProducts2QueryDto): void {
    this.startLoading();

    this.api.delete(category.id).subscribe({
      next: () => {
        this.dialogHelper.productCategory.showDeleteSuccess().subscribe();
        this.loadPagedData();
        this.stopLoading();
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

  onToggleStatus(category: ListProducts2QueryDto): void {
    this.startLoading();

    const apiAction = category.isEnabled
      ? this.api.disable(category.id)
      : this.api.enable(category.id);

    apiAction.subscribe({
      next: () => {
        const status = category.isEnabled ? 'disabled' : 'enabled';
        this.toaster.success(`Category ${status} successfully`);
        this.loadPagedData();
        this.stopLoading();
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

  /**
   * Extract user-friendly error message from HTTP error response
   */
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

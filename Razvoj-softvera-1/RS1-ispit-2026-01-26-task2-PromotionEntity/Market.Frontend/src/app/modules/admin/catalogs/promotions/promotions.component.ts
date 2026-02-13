import { Component, inject, OnInit } from '@angular/core';
import {
  ListPromotionsQueryDto,
  ListPromotionsRequest,
} from '../../../../api-services/promotions/promotions-api.models';
import { ActivatedRoute, Router } from '@angular/router';
import { MatDialog } from '@angular/material/dialog';
import { PromotionsApiService } from '../../../../api-services/promotions/promotions-api.service';
import { BaseListPagedComponent } from '../../../../core/components/base-classes/base-list-paged-component';
import { ToasterService } from '../../../../core/services/toaster.service';
import { DialogHelperService } from '../../../shared/services/dialog-helper.service';
import { DialogButton } from '../../../shared/models/dialog-config.model';

@Component({
  selector: 'app-promotions',
  standalone: false,
  templateUrl: './promotions.component.html',
  styleUrl: './promotions.component.scss',
})
export class PromotionsComponent
  extends BaseListPagedComponent<ListPromotionsQueryDto, ListPromotionsRequest>
  implements OnInit
{
  private api = inject(PromotionsApiService);
  private dialog = inject(MatDialog);
  private toaster = inject(ToasterService);
  private dialogHelper = inject(DialogHelperService);
  private router = inject(Router);
  private route = inject(ActivatedRoute);

  constructor() {
    super();
    this.request = new ListPromotionsRequest();
    this.request.isActive = true;
  }

  ngOnInit(): void {
    // this.initList();
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
        this.stopLoading('Failed to load categories');
        this.toaster.error('Load categories error:', err);
      },
    });
  }

  // === CRUD Actions ===

  onCreate(): void {
    this.router.navigate(['/admin/promotions/add']);
  }

  onView(category: ListPromotionsQueryDto): void {
    this.router.navigate(['/admin/promotions/view', category.id]);
  }

  onEdit(category: ListPromotionsQueryDto): void {
    this.router.navigate(['/admin/promotions/edit', category.id]);
  }

  onDelete(category: ListPromotionsQueryDto): void {
    this.dialogHelper.productCategory.confirmDelete(category.title).subscribe((result) => {
      if (result && result.button === DialogButton.DELETE) {
        this.performDelete(category);
      }
    });
  }

  private performDelete(category: ListPromotionsQueryDto): void {
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

  onToggleStatus(category: ListPromotionsQueryDto): void {
    this.startLoading();

    this.api.changeStatus(category.id).subscribe({
      next: () => {
        const status = category.isActive ? 'disabled' : 'enabled';
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
              { title: category.title },
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

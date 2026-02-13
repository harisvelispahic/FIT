import { Component, inject, OnInit } from '@angular/core';
import { BasePagedQuery } from '../../../../core/models/paging/base-paged-query';
import { BaseListPagedComponent } from '../../../../core/components/base-classes/base-list-paged-component';
import {
  ListProducts2QueryDto,
  ListProducts2Request,
} from '../../../../api-services/products-2/products-2-api.model';
import { Products2ApiService } from '../../../../api-services/products-2/products-2-api.service';
import { DialogHelperService } from '../../../shared/services/dialog-helper.service';
import { ToasterService } from '../../../../core/services/toaster.service';
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
  private dialogHelper = inject(DialogHelperService);
  private toaster = inject(ToasterService);
  private router = inject(Router);
  private route = inject(ActivatedRoute);

  searchValue = '';

  constructor() {
    super();
    this.request = new ListProducts2Request();
    this.request.onlyEnabled = true;
    this.request.paging.pageSize = 100;
  }

  ngOnInit(): void {
    this.initList();
  }

  protected override loadPagedData(): void {
    this.startLoading();

    this.api.list(this.request).subscribe({
      next: (res) => {
        this.handlePageResult(res);
        this.stopLoading();
      },
      error: (err) => {
        this.stopLoading('There was an error loading products!');
      },
    });
  }

  searchAction() {
    this.api
      .list({
        paging: {
          page: 1,
          pageSize: 1000,
        },
        search: this.request.search,
      })
      .subscribe({
        next: (response) => {
          this.handlePageResult(response);
          //this.toaster.success("ok su podaci: " + this.productCategoriesList.length);
        },
        error: (error) => {
          this.toaster.error(error.message);
        },
      });
  }

  addNewProduct() {
    this.router.navigate(['/admin/products-2/add']);
  }

  editProduct(id: number) {
    this.router.navigate(['/admin/products-2/edit/', id]);
  }

  onDelete(product: ListProducts2QueryDto): void {
    this.dialogHelper.product2.confirmDelete(product.name).subscribe((result) => {
      if (result && result.button === DialogButton.DELETE) {
        this.performDelete(product);
      }
    });
  }

  private performDelete(product: ListProducts2QueryDto): void {
    this.startLoading();

    this.api.delete(product.id).subscribe({
      next: () => {
        this.dialogHelper.product2.showDeleteSuccess().subscribe();
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

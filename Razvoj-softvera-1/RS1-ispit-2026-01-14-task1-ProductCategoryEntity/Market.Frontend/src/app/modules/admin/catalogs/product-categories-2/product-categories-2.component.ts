import { Component, inject, OnInit } from '@angular/core';
import { BaseListPagedComponent } from '../../../../core/components/base-classes/base-list-paged-component';
import {
  ListProductCategories2QueryDto,
  ListProductCategories2Request,
  ListProductCategories2Response,
} from '../../../../api-services/product-categories-2/product-categories-2-api.model';
import { MatDialog } from '@angular/material/dialog';
import { ProductCategories2ApiService } from '../../../../api-services/product-categories-2/product-categories-2-api.service';
import { ToasterService } from '../../../../core/services/toaster.service';
import { DialogHelperService } from '../../../shared/services/dialog-helper.service';
import { Router } from '@angular/router';
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
  private dialog = inject(MatDialog);
  private toaster = inject(ToasterService);
  private dialogHelper = inject(DialogHelperService);
  private router = inject(Router);

  constructor() {
    super();
    this.request = new ListProductCategories2Request();
    this.request.onlyEnabled = true;
  }

  ngOnInit(): void {
    this.loadPagedData();
  }

  protected override loadPagedData(): void {
    this.startLoading();

    this.api.list(this.request).subscribe({
      next: (response) => {
        this.handlePageResult(response);
        this.stopLoading();
      },
      error: (err) => {
        this.toaster.error('Error loading product categories 2');
        this.stopLoading();
      },
    });
  }

  searchResults() {
    this.loadPagedData();
  }

  changeEnabledChoice() {
    this.loadPagedData();
  }

  createNewCategory() {
    this.router.navigate(['/admin/product-categories-2/add']);
  }

  editCategory(categoryId: number) {
    this.router.navigate(['/admin/product-categories-2/edit', categoryId]);
  }

  onDelete(category: ListProductCategories2QueryDto): void {
    this.startLoading();
    this.dialogHelper.productCategory.confirmDelete(category.name).subscribe({
      next: (result) => {
        if (result && result.button === DialogButton.DELETE) {
          this.api.delete(category.id).subscribe({
            next: (res) => {
              this.toaster.success(`Category ${category.name} deleted successfully!`);
              this.ngOnInit();
              this.stopLoading();
            },
            error: (err) => {
              this.toaster.error(`Category ${category.name} was not deleted!`);
              this.stopLoading();
            },
          });
        } else {
          this.ngOnInit();
        }
      },
      error: (error) => {},
    });
  }
}

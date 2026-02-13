import { Component, inject, OnInit } from '@angular/core';
import { Product2FormService } from '../services/product-2-form.service';
import { BaseComponent } from '../../../../../core/components/base-classes/base-component';
import { FormGroup } from '@angular/forms';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { Products2ApiService } from '../../../../../api-services/products-2/products-2-api.service';
import { ActivatedRoute, Router } from '@angular/router';
import {
  CreateProduct2Command,
  UpdateProduct2Command,
} from '../../../../../api-services/products-2/products-2-api.model';
import {
  ListProductCategoriesQueryDto,
  ListProductCategoriesResponse,
} from '../../../../../api-services/product-categories/product-categories-api.model';
import { ProductCategoriesApiService } from '../../../../../api-services/product-categories/product-categories-api.service';

@Component({
  selector: 'app-products-2-upsert',
  standalone: false,
  templateUrl: './products-2-upsert.component.html',
  styleUrl: './products-2-upsert.component.scss',
  providers: [Product2FormService],
})
export class Products2UpsertComponent extends BaseComponent implements OnInit {
  // private dialogRef = inject(MatDialogRef<ProductCategoryUpsertComponent>);
  // private data = inject<ProductCategoryDialogData>(MAT_DIALOG_DATA);
  private api = inject(Products2ApiService);
  private apiCategories = inject(ProductCategoriesApiService);
  private formService = inject(Product2FormService);
  private toaster = inject(ToasterService);
  private router = inject(Router);
  private route = inject(ActivatedRoute);

  form!: FormGroup;
  isEditMode = false;
  productId!: number;
  categories: ListProductCategoriesQueryDto[] = [];

  ngOnInit(): void {
    this.form = this.formService.createProduct2Form();

    this.productId = +this.route.snapshot.params['id'];
    this.isEditMode = !!this.productId;

    this.startLoading();

    this.apiCategories.list().subscribe({
      next: (categories) => {
        this.categories = categories.items;
        this.stopLoading();
      },
      error: (err) => {
        this.toaster.error('Failed to load category');
        console.error('Load category error:', err);
        this.stopLoading();
      },
    });

    if (this.isEditMode && this.productId) {
      this.loadProduct(this.productId);
    }
  }

  private loadProduct(id: number): void {
    this.startLoading();

    this.api.getById(id).subscribe({
      next: (product2) => {
        this.form = this.formService.createProduct2Form(product2);
        this.stopLoading();
      },
      error: (err) => {
        this.toaster.error('Failed to load category');
        console.error('Load category error:', err);
        this.stopLoading();
      },
    });
  }

  private createProduct(): void {
    this.startLoading();

    const command: CreateProduct2Command = this.form.getRawValue();

    this.api.create(command).subscribe({
      next: () => {
        this.toaster.success('Category created successfully');
        this.stopLoading();
      },
      error: (err) => {
        console.error('Create category error:', err);
        this.toaster.error('Create category error:', err);
        this.stopLoading();
      },
    });
  }

  private updateProduct(): void {
    this.startLoading();

    const command: UpdateProduct2Command = this.form.getRawValue();

    this.api.update(this.productId, command).subscribe({
      next: () => {
        this.toaster.success('Category updated successfully');
        this.stopLoading();
      },
      error: (err) => {
        console.error('Update category error:', err);
        this.toaster.error('Create category error:', err);
        this.stopLoading();
      },
    });
  }

  onSubmit(): void {
    if (this.form.invalid || this.isLoading) {
      this.form.markAllAsTouched();
      return;
    }

    console.log(this.form.value);

    this.startLoading();

    if (this.isEditMode && this.productId) {
      this.updateProduct();
    } else {
      this.createProduct();
    }

    this.router.navigate(['/admin/products-2']);
  }

  onCancel(): void {
    this.router.navigate(['/admin/products-2']);
  }

  getErrorMessage(controlName: string): string {
    return this.formService.getErrorMessage(this.form, controlName);
  }
}

import { Component, inject, OnInit } from '@angular/core';
import { BaseComponent } from '../../../../../core/components/base-classes/base-component';
import { Products2ApiService } from '../../../../../api-services/products-2/products-2-api.service';
import { Product2FormService } from '../services/product-2-form.service';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { Router, ActivatedRoute } from '@angular/router';
import { FormGroup } from '@angular/forms';
import {
  CreateProduct2Command,
  UpdateProduct2Command,
} from '../../../../../api-services/products-2/products-2-api.model';
import { ProductCategoriesApiService } from '../../../../../api-services/product-categories/product-categories-api.service';
import { ListProductCategoriesQueryDto } from '../../../../../api-services/product-categories/product-categories-api.model';
import { forkJoin } from 'rxjs';

@Component({
  selector: 'app-products-2-upsert',
  standalone: false,
  templateUrl: './products-2-upsert.component.html',
  styleUrl: './products-2-upsert.component.scss',
  providers: [Product2FormService],
})
export class Products2UpsertComponent extends BaseComponent implements OnInit {
  // private dialogRef = inject(MatDialogRef<ProductCategoryUpsertComponent>);
  private api = inject(Products2ApiService);
  private apiCategories = inject(ProductCategoriesApiService);
  private formService = inject(Product2FormService);
  private toaster = inject(ToasterService);
  private router = inject(Router);
  private route = inject(ActivatedRoute);

  form!: FormGroup;
  isEditMode = false;
  productId!: number;
  categories!: ListProductCategoriesQueryDto[];

  ngOnInit(): void {
    this.form = this.formService.createCategoryForm();

    this.productId = +this.route.snapshot.params['id'];
    this.isEditMode = !!this.productId;

    this.apiCategories.list().subscribe({
      next: (response) => {
        this.categories = response.items;
      },
      error: () => {
        this.toaster.error('nece da moze');
      },
    });

    if (this.isEditMode && this.productId) {
      this.loadCategory(this.productId);
    }
  }

  private loadCategory(id: number): void {
    this.isLoading = true;

    this.api.getById(id).subscribe({
      next: (category) => {
        this.form = this.formService.createCategoryForm(category);
        console.log(this.form.value);

        this.isLoading = false;
      },
      error: (err) => {
        this.toaster.error('Failed to load category');
        console.error('Load category error:', err);
        this.stopLoading();
      },
    });
    // forkJoin({
    //   product: this.api.getById(id),
    //   categories: this.apiCategories.list(),
    // }).subscribe({
    //   next: ({ product, categories }) => {
    //     this.form = this.formService.createCategoryForm(product);
    //     this.categories = categories.items;
    //     console.log(this.form.value);

    //     this.isLoading = false;
    //   },
    //   error: (err) => {
    //     this.toaster.error('Failed to load category');
    //     console.error('Load category error:', err);
    //     this.stopLoading();
    //   },
    // });
  }

  onSubmit(): void {
    if (this.form.invalid || this.isLoading) {
      this.form.markAllAsTouched();
      return;
    }

    this.isLoading = true;

    if (this.isEditMode && this.productId) {
      this.updateCategory();
    } else {
      this.createCategory();
    }
    this.router.navigate(['/admin/products-2']);
  }

  private createCategory(): void {
    const command: CreateProduct2Command = this.form.getRawValue();

    this.startLoading();
    this.api.create(command).subscribe({
      next: () => {
        this.toaster.success('Category created successfully');
        this.stopLoading();
      },
      error: (err) => {
        this.isLoading = false;
        console.error('Create category error:', err);
      },
    });
  }

  private updateCategory(): void {
    const command: UpdateProduct2Command = this.form.getRawValue();

    this.startLoading();
    this.api.update(this.productId!, command).subscribe({
      next: () => {
        this.toaster.success('Category updated successfully');
        this.stopLoading();
      },
      error: (err) => {
        this.isLoading = false;
        console.error('Update category error:', err);
      },
    });
  }

  onCancel(): void {
    this.router.navigate(['/admin/products-2']);
  }

  getErrorMessage(controlName: string): string {
    return this.formService.getErrorMessage(this.form, controlName);
  }
}

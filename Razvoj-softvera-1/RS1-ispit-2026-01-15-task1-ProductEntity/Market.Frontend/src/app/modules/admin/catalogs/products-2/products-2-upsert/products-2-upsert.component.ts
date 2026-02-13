import { Component, inject, OnInit } from '@angular/core';
import { Products2ApiService } from '../../../../../api-services/products-2/products-2-api.service';
import { Product2FormService } from '../services/products-2-form.service';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { FormGroup } from '@angular/forms';
import {
  CreateProduct2Command,
  UpdateProduct2Command,
} from '../../../../../api-services/products-2/products-2-api.model';
import { ActivatedRoute, Router } from '@angular/router';
import { ListProductCategoriesQueryDto } from '../../../../../api-services/product-categories/product-categories-api.model';
import { ProductCategoriesApiService } from '../../../../../api-services/product-categories/product-categories-api.service';
import { forkJoin } from 'rxjs';

@Component({
  selector: 'app-products-2-upsert',
  standalone: false,
  templateUrl: './products-2-upsert.component.html',
  styleUrl: './products-2-upsert.component.scss',
  providers: [Product2FormService],
})
export class Products2UpsertComponent implements OnInit {
  private api = inject(Products2ApiService);
  private categoriesApi = inject(ProductCategoriesApiService);
  private formService = inject(Product2FormService);
  private toaster = inject(ToasterService);
  private router = inject(Router);
  private route = inject(ActivatedRoute);

  categories: ListProductCategoriesQueryDto[] = [];
  productId!: number;

  form!: FormGroup;
  isLoading = false;
  isEditMode = false;
  title = '';

  ngOnInit(): void {
    this.form = this.formService.createProductForm();

    this.productId = +this.route.snapshot.params['id'];
    this.isEditMode = !!this.productId;
    this.title = this.isEditMode ? 'Edit Product' : 'New Product';
    this.isLoading = true;

    if (this.isEditMode && this.productId) {
      forkJoin({
        categories: this.categoriesApi.list(),
        product: this.api.getById(this.productId),
      }).subscribe({
        next: ({ categories, product }) => {
          this.categories = categories.items;
          this.form = this.formService.createProductForm(product);
          this.isLoading = false;
        },
        error: (err) => {
          this.toaster.error('Failed to load data');
          this.isLoading = false;
        },
      });
    } else {
      this.categoriesApi.list().subscribe({
        next: (res) => {
          this.categories = res.items;
          this.form = this.formService.createProductForm();
          this.isLoading = false;
        },
        error: (err) => {
          this.toaster.error("Couldn't get product categories");
          this.isLoading = false;
        },
      });
    }
  }

  onSubmit(): void {
    if (this.form.invalid || this.isLoading) {
      this.form.markAllAsTouched();
      return;
    }

    this.isLoading = true;

    if (this.isEditMode) {
      this.updateProduct();
    } else {
      this.createProduct();
    }
  }

  private createProduct(): void {
    const command: CreateProduct2Command = {
      name: this.form.value.name.trim(),
      description: this.form.value.description.trim(),
      price: this.form.value.price,
      categoryId: +this.form.value.categoryId,
    };

    this.api.create(command).subscribe({
      next: () => {
        this.toaster.success('Product created successfully');
        this.router.navigate(['/admin/products-2']);
      },
      error: (err) => {
        this.isLoading = false;
        this.toaster.error('Failed to create product');
      },
    });
  }

  private updateProduct(): void {
    const productId = +this.route.snapshot.params['id'];
    const command: UpdateProduct2Command = {
      id: productId,
      name: this.form.value.name.trim(),
      description: this.form.value.description.trim(),
      price: this.form.value.price,
      categoryId: +this.form.value.categoryId,
    };

    this.api.update(productId, command).subscribe({
      next: () => {
        this.toaster.success('Product updated successfully');
        this.router.navigate(['/admin/products-2']);
      },
      error: (err) => {
        this.isLoading = false;
        this.toaster.error('Failed to update product');
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

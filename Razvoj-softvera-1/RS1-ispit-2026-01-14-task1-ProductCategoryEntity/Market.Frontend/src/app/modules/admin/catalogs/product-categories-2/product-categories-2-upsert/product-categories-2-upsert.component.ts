import { Component, inject, OnInit } from '@angular/core';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { ProductCategories2ApiService } from '../../../../../api-services/product-categories-2/product-categories-2-api.service';
import { ProductCategory2FormService } from '../services/product-category-2-form.service';
import { FormGroup } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import {
  CreateProductCategory2Command,
  UpdateProductCategory2Command,
} from '../../../../../api-services/product-categories-2/product-categories-2-api.model';
// import { MAT_DIALOG_DATA, MatDialogRef } from '@angular/material/dialog';

export interface ProductCategoryDialogData {
  mode: 'create' | 'edit';
  categoryId?: number;
}

@Component({
  selector: 'app-product-categories-2-upsert',
  standalone: false,
  templateUrl: './product-categories-2-upsert.component.html',
  styleUrl: './product-categories-2-upsert.component.scss',
  providers: [ProductCategory2FormService],
})
export class ProductCategories2UpsertComponent implements OnInit {
  // private dialogRef = inject(MatDialogRef<ProductCategories2UpsertComponent>);
  // private data = inject<ProductCategoryDialogData>(MAT_DIALOG_DATA);
  private api = inject(ProductCategories2ApiService);
  private formService = inject(ProductCategory2FormService);
  private toaster = inject(ToasterService);
  private route = inject(ActivatedRoute);
  private router = inject(Router);

  form!: FormGroup;
  isLoading = false;
  isEditMode = false;
  title = '';
  categoryId!: number;

  ngOnInit(): void {
    this.categoryId = this.route.snapshot.params['id'];
    console.log(this.categoryId);
    this.isEditMode = !!this.categoryId;
    this.title = this.isEditMode ? 'Edit the category:' : 'Create new category:';
    if (this.isEditMode) {
      this.loadCategory(this.categoryId);
    } else {
      this.form = this.formService.createCategoryForm();
    }
  }

  loadCategory(categoryId: number): void {
    this.isLoading = true;

    this.api.getById(categoryId).subscribe({
      next: (response) => {
        this.form = this.formService.createCategoryForm(response);
        this.isLoading = false;
      },
      error: (err) => {
        this.toaster.error('There was an error filling the fields in!');
        this.isLoading = false;
      },
    });
  }

  createCategory() {
    const newCategory: CreateProductCategory2Command = {
      name: this.form.value.name.trim(),
      isEnabled: this.form.value.isEnabled,
    };

    this.isLoading = true;

    this.api.create(newCategory).subscribe({
      next: (response) => {
        this.toaster.success('Category created successfully!');
        this.isLoading = false;
        1;
      },
      error: (err) => {
        this.toaster.error('Category was not created!');
        this.isLoading = false;
      },
    });
  }

  updateCategory() {
    const categoryUpdate: UpdateProductCategory2Command = {
      name: this.form.value.name.trim(),
      isEnabled: this.form.value.isEnabled,
    };

    this.isLoading = true;

    this.api.update(this.categoryId, categoryUpdate).subscribe({
      next: (response) => {
        this.toaster.success(`Category ${categoryUpdate.name} updated successfully!`);
        this.isLoading = false;
      },
      error: (err) => {
        this.toaster.error('Category was not updated!');
        this.isLoading = false;
      },
    });
  }

  submitAction() {
    if (this.isEditMode) {
      this.updateCategory();
      this.router.navigate(['/admin/product-categories-2']);
    } else {
      this.createCategory();
      this.router.navigate(['/admin/product-categories-2']);
    }
  }

  cancelAction() {
    this.router.navigate(['/admin/product-categories-2']);
  }

  getErrorMessage(controlName: string) {
    return this.formService.getErrorMessage(this.form, controlName);
  }
}

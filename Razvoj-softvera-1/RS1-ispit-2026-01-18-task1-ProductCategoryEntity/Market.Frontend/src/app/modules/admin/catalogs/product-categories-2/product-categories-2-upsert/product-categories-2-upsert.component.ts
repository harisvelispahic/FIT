import { Component, inject, OnInit } from '@angular/core';
import { ProductCategory2FormService } from '../services/product-category-2-form.service';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { ProductCategories2ApiService } from '../../../../../api-services/product-categories-2/product-categories-2-api.service';
import { FormGroup } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import {
  CreateProductCategory2Command,
  UpdateProductCategory2Command,
} from '../../../../../api-services/product-categories-2/product-categories-2-api.models';

@Component({
  selector: 'app-product-categories-2-upsert',
  standalone: false,
  templateUrl: './product-categories-2-upsert.component.html',
  styleUrl: './product-categories-2-upsert.component.scss',
  providers: [ProductCategory2FormService],
})
export class ProductCategories2UpsertComponent implements OnInit {
  // private dialogRef = inject(MatDialogRef<ProductCategory2UpsertComponent>);
  // private data = inject<ProductCategory2DialogData>(MAT_DIALOG_DATA);
  private api = inject(ProductCategories2ApiService);
  private formService = inject(ProductCategory2FormService);
  private toaster = inject(ToasterService);
  private route = inject(ActivatedRoute);
  private rotuer = inject(Router);

  form!: FormGroup;
  isLoading = false;
  isEditMode = false;
  categoryId!: number;

  ngOnInit(): void {
    this.form = this.formService.createProductCategoryForm();
    this.categoryId = this.route.snapshot.params['id'];

    this.isEditMode = !!this.categoryId;

    if (this.isEditMode && this.categoryId) {
      this.loadCategory(this.categoryId);
    }
  }

  private loadCategory(id: number): void {
    this.isLoading = true;

    this.api.getById(id).subscribe({
      next: (category) => {
        this.form = this.formService.createProductCategoryForm(category);
        this.isLoading = false;
      },
      error: (err) => {
        this.toaster.error('Failed to load category');
        console.error('Load category error:', err);
        this.isLoading = false;
      },
    });
  }

  onSubmit(): void {
    if (this.form.invalid || this.isLoading) {
      this.form.markAllAsTouched();
      return;
    }

    this.isLoading = true;

    if (this.isEditMode && this.categoryId) {
      this.updateCategory();
    } else {
      this.createCategory();
    }

    // console.log(this.form.value);
    // console.log(this.form.get('name')?.invalid);
  }

  private createCategory(): void {
    // const command: CreateProductCategory2Command = {
    //   name: this.form.value.name.trim(),
    //   isEnabled: this.form.value.isEnabled,
    // };

    const command = this.form.getRawValue() as CreateProductCategory2Command;

    this.api.create(command).subscribe({
      next: () => {
        this.toaster.success('Category created successfully');
        this.isLoading = false;
        this.onCancel();
      },
      error: (err) => {
        this.toaster.error('There was an error in creating the category!');
        console.error('Create category error:', err);
        this.isLoading = false;
      },
    });
  }

  private updateCategory(): void {
    // const command: UpdateProductCategory2Command = {
    //   name: this.form.value.name.trim(),
    //   isEnabled: this.form.value.isEnabled,
    // };

    const command = this.form.getRawValue() as UpdateProductCategory2Command;
    console.log(command);

    this.api.update(this.categoryId!, command).subscribe({
      next: () => {
        this.toaster.success('Category updated successfully');
        this.isLoading = false;
        this.onCancel();
      },
      error: (err) => {
        this.toaster.error('There was an error in updating the category!');
        console.error('Update category error:', err);
        this.isLoading = false;
      },
    });
  }

  onCancel(): void {
    this.rotuer.navigate(['/admin/product-categories-2']);
  }

  getErrorMessage(controlName: string): string {
    return this.formService.getErrorMessage(this.form, controlName);
  }
}

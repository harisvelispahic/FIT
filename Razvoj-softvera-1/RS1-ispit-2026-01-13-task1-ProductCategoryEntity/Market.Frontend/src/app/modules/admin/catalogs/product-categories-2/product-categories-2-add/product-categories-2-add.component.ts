import { Component, inject } from '@angular/core';
import { FormBuilder, FormControl, FormGroup, Validators } from '@angular/forms';
import { MAT_DIALOG_DATA, MatDialogRef } from '@angular/material/dialog';
import { ProductCategoryDialogData } from '../../product-categories/product-category-upsert/product-category-upsert.component';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { ProductCategories2ApiService } from '../../../../../api-services/product-categories-2/product-categories-2-api.service';
import { CreateProductCategory2Command } from '../../../../../api-services/product-categories-2/product-categories-2-api.model';
import { Router } from '@angular/router';

@Component({
  selector: 'app-product-categories-2-add',
  standalone: false,
  templateUrl: './product-categories-2-add.component.html',
  styleUrl: './product-categories-2-add.component.scss',
})
export class ProductCategories2AddComponent {
  // private dialogRef = inject(MatDialogRef<ProductCategories2AddComponent>);
  // private data = inject<ProductCategoryDialogData>(MAT_DIALOG_DATA);
  private router = inject(Router);
  private fb = inject(FormBuilder);
  private api = inject(ProductCategories2ApiService);
  private toaster = inject(ToasterService);

  isLoading = false;
  isEditMode = false;
  title = '';

  public form = this.fb.group({
    name: ['', [Validators.required, Validators.minLength(3), Validators.maxLength(100)]],
    isEnabled: [true, [Validators.required]],
  });

  createCategory() {
    const command: CreateProductCategory2Command = {
      name: this.form.value.name!.trim(),
      isEnabled: this.form.value.isEnabled!,
    };
    console.log(command);
    this.api.create(command).subscribe({
      next: (response) => {
        this.toaster.success('Category created successfully');
        this.router.navigate(['/admin/product-categories-2']);
      },
      error: (err) => {
        this.toaster.error('Failed to create category');
        console.error('Create category error:', err);
      },
    });
  }

  cancel() {
    this.router.navigate(['/admin/product-categories-2']);
  }
}

import { Component, inject, OnInit } from '@angular/core';
import { FormBuilder, FormControl, FormGroup, Validators } from '@angular/forms';
import { MAT_DIALOG_DATA, MatDialogRef } from '@angular/material/dialog';
import { ProductCategoryDialogData } from '../../product-categories/product-category-upsert/product-category-upsert.component';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { ProductCategories2ApiService } from '../../../../../api-services/product-categories-2/product-categories-2-api.service';
import {
  CreateProductCategory2Command,
  UpdateProductCategory2Command,
} from '../../../../../api-services/product-categories-2/product-categories-2-api.model';
import { ActivatedRoute, Router } from '@angular/router';
@Component({
  selector: 'app-product-categories-2-edit',
  standalone: false,
  templateUrl: './product-categories-2-edit.component.html',
  styleUrl: './product-categories-2-edit.component.scss',
})
export class ProductCategories2EditComponent implements OnInit {
  private router = inject(Router);
  private route = inject(ActivatedRoute);
  private fb = inject(FormBuilder);
  private api = inject(ProductCategories2ApiService);
  private toaster = inject(ToasterService);

  isLoading = false;
  private id!: number;
  isEditMode = false;
  title = '';

  public form = this.fb.group({
    name: ['', [Validators.required, Validators.minLength(3), Validators.maxLength(100)]],
    isEnabled: [true, [Validators.required]],
  });

  ngOnInit(): void {
    this.id = +this.route.snapshot.params['id'];

    this.isLoading = true;
    this.api.getById(this.id).subscribe({
      next: (category) => {
        this.form.patchValue({
          name: category.name,
          isEnabled: category.isEnabled,
        });

        this.isLoading = false;
      },
      error: (err) => {
        this.isLoading = false;
        this.toaster.error('Failed to load category');
        console.error(err);
      },
    });
  }

  editCategory() {
    const command: UpdateProductCategory2Command = {
      name: this.form.value.name!.trim(),
      isEnabled: this.form.value.isEnabled!,
    };
    this.api.update(this.id, command).subscribe({
      next: (response) => {
        this.toaster.success('Category updated successfully');
        this.router.navigate(['/admin/product-categories-2']);
      },
      error: (err) => {
        this.toaster.error('Failed to update category');
        console.error('Update category error:', err);
      },
    });
  }

  cancel() {
    this.router.navigate(['/admin/product-categories-2']);
  }
}

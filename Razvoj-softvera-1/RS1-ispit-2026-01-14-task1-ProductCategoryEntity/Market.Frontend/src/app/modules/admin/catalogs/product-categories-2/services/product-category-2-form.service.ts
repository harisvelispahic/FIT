import { Injectable, inject } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { GetProductCategory2ByIdQueryDto } from '../../../../../api-services/product-categories-2/product-categories-2-api.model';

/**
 * Service for creating and managing product category forms.
 * Used in modal dialog for both create and edit operations.
 */
@Injectable()
export class ProductCategory2FormService {
  private fb = inject(FormBuilder);

  /**
   * Create a product category form with validation.
   * If category data is provided, form is pre-filled (edit mode).
   */
  createCategoryForm(category?: GetProductCategory2ByIdQueryDto): FormGroup {
    return this.fb.group({
      name: [
        category?.name ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],
      isEnabled: [category?.isEnabled ?? true, [Validators.required]],
    });
  }

  /**
   * Get validation error message for a form control.
   */
  getErrorMessage(form: FormGroup, controlName: string): string {
    const control = form.get(controlName);
    if (!control || !control.errors || !control.touched) {
      return '';
    }

    const errors = control.errors;

    if (errors['required']) {
      return 'This field is required';
    }
    if (errors['minlength']) {
      return `Minimum ${errors['minlength'].requiredLength} characters required`;
    }
    if (errors['maxlength']) {
      return `Maximum ${errors['maxlength'].requiredLength} characters allowed`;
    }

    return 'Invalid value';
  }
}

import { Injectable, inject } from '@angular/core';
import { FormBuilder, Validators, FormGroup } from '@angular/forms';
import { GetProductCategory2ByIdQueryDto } from '../../../../../api-services/product-categories-2/product-categories-2-api.models';

/**
 * Service for creating and managing product forms.
 * Provides reusable form creation with validation for Add and Edit components.
 */
@Injectable()
export class ProductCategory2FormService {
  private fb = inject(FormBuilder);

  /**
   * Create a product form with validation.
   * If product data is provided, form is pre-filled (edit mode).
   */
  createProductCategoryForm(category2?: GetProductCategory2ByIdQueryDto): FormGroup {
    return this.fb.group({
      name: [
        category2?.name ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],
      isEnabled: [category2?.isEnabled ?? false, [Validators.required]],
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
    if (errors['min']) {
      return `Minimum value is ${errors['min'].min}`;
    }
    if (errors['max']) {
      return `Maximum value is ${errors['max'].max}`;
    }
    if (errors['email']) {
      return 'Invalid email format';
    }

    return 'Invalid value';
  }
}

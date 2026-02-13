import { Injectable, inject } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { GetProduct2ByIdQueryDto } from '../../../../../api-services/products-2/products-2-api.model';

/**
 * Service for creating and managing product category forms.
 * Used in modal dialog for both create and edit operations.
 */
@Injectable()
export class Product2FormService {
  private fb = inject(FormBuilder);

  /**
   * Create a product category form with validation.
   * If category data is provided, form is pre-filled (edit mode).
   */
  createProductForm(product?: GetProduct2ByIdQueryDto): FormGroup {
    return this.fb.group({
      name: [
        product?.name ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],
      description: [
        product?.description ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],
      price: [
        product?.price ?? 0,
        [Validators.required, Validators.min(0.01), Validators.max(1000000)],
      ],
      categoryId: [product?.categoryId ? +product.categoryId : null, [Validators.required]],
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
      return `Minimum ${errors['min'].requiredLength} value`;
    }
    if (errors['max']) {
      return `Maximum ${errors['max'].requiredLength} value`;
    }

    return 'Invalid value';
  }
}

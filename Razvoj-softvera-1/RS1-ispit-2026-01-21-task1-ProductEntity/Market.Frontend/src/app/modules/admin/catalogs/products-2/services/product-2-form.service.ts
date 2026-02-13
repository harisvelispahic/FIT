import { Injectable, inject } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { GetProductCategoryByIdQueryDto } from '../../../../../api-services/product-categories/product-categories-api.model';
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
  createProduct2Form(product2?: GetProduct2ByIdQueryDto): FormGroup {
    return this.fb.group({
      name: [
        product2?.name ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],
      description: [
        product2?.description ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],
      price: [
        product2?.price ?? 0,
        [Validators.required, Validators.min(0.00001), Validators.max(999999999)],
      ],
      stockQuantity: [
        product2?.stockQuantity ?? 0,
        [Validators.required, Validators.min(1), Validators.max(999999999)],
      ],
      categoryId: [product2?.categoryId ?? 0, [Validators.required, Validators.min(0)]],
      isEnabled: [product2?.isEnabled ?? true, [Validators.required]],
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
      return `Minimum ${errors['minlength'].requiredLength} characters required`;
    }
    if (errors['max']) {
      return `Maximum ${errors['maxlength'].requiredLength} characters allowed`;
    }

    return 'Invalid value';
  }
}

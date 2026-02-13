import { Injectable, inject } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { GetPromotionByIdQueryDto } from '../../../../../api-services/promotions/promotions-api.model';
import { Title } from '@angular/platform-browser';

/**
 * Service for creating and managing product Promotion forms.
 * Used in modal dialog for both create and edit operations.
 */
@Injectable()
export class PromotionFormService {
  private fb = inject(FormBuilder);

  /**
   * Create a product Promotion form with validation.
   * If Promotion data is provided, form is pre-filled (edit mode).
   */
  createPromotionForm(Promotion?: GetPromotionByIdQueryDto): FormGroup {
    return this.fb.group({
      title: [
        Promotion?.title ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],
      imageUrl: [
        Promotion?.title ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],
      targetUrl: [
        Promotion?.title ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],

      isActive: [Promotion?.isActive ?? true, [Validators.required]],
      startsAtUtc: [Promotion?.startsAtUtc ?? true, [Validators.required]],
      endsAtUtc: [Promotion?.endsAtUtc ?? true, [Validators.required]],
      sortOrder: [Promotion?.sortOrder ?? true, [Validators.required]],
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

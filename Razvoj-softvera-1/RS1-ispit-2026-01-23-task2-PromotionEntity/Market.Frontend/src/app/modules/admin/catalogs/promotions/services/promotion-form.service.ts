import { Injectable, inject } from '@angular/core';
import { FormArray, FormBuilder, FormGroup, Validators } from '@angular/forms';
import {
  GetPromotionByIdQueryDtoItem,
  GetPromotionByIdQueryDto,
} from '../../../../../api-services/promotions/promotions-api.models';

/**
 * Service for creating and managing product promotion forms.
 * Used in modal dialog for both create and edit operations.
 */
@Injectable()
export class PromotionFormService {
  private fb = inject(FormBuilder);

  /**
   * Create a product promotion form with validation.
   * If promotion data is provided, form is pre-filled (edit mode).
   */
  createPromotionForm(promotion?: GetPromotionByIdQueryDto): FormGroup {
    return this.fb.group({
      title: [
        promotion?.title ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],
      imageUrl: [
        promotion?.imageUrl ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],
      targetUrl: [
        promotion?.targetUrl ?? '',
        [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
      ],
      isActive: [promotion?.isActive ?? false, [Validators.required]],
      startsAtUtc: [promotion?.startsAtUtc ?? '', [Validators.required]],
      endsAtUtc: [promotion?.endsAtUtc ?? '', [Validators.required]],
      sortOrder: [promotion?.sortOrder ?? '', [Validators.required]],

      promotionItems: this.fb.array(
        (promotion?.promotionItems ?? []).map((item) => this.createPromotionItemForm(item)),
      ),
    });
  }

  createPromotionItemForm(promotionItem: GetPromotionByIdQueryDtoItem): FormGroup {
    return this.fb.group({
      productId: [promotionItem?.productId ?? '', [Validators.required]],
      discountPercent: [promotionItem?.discountPercent ?? '', [Validators.required]],
    });
  }

  // ✅ helper accessor - doesn't store form
  getPromotionItems(form: FormGroup): FormArray {
    return form.get('promotionItems') as FormArray;
  }

  // addPromotionItem(form: FormGroup): void {
  //   this.getPromotionItems(form).push(this.createPromotionItemForm());
  // }

  removePromotionItem(form: FormGroup, index: number): void {
    this.getPromotionItems(form).removeAt(index);
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

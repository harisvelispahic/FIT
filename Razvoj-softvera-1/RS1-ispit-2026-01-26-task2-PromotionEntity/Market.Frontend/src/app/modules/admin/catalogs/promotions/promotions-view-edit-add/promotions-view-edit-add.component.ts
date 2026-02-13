import { Component, inject, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { PromotionsApiService } from '../../../../../api-services/promotions/promotions-api.service';
import { FormArray, FormBuilder, FormGroup, Validators } from '@angular/forms';
import {
  CreatePromotionCommand,
  GetByIdPromotionQueryDtoPromotionItem,
  GetPromotionByIdQueryDto,
  UpdatePromotionCommand,
} from '../../../../../api-services/promotions/promotions-api.models';
import { ListProductsQueryDto } from '../../../../../api-services/products/products-api.models';
import { ProductsApiService } from '../../../../../api-services/products/products-api.service';
import { BaseComponent } from '../../../../../core/components/base-classes/base-component';
import { forkJoin } from 'rxjs';

@Component({
  selector: 'app-promotions-view-edit-add',
  standalone: false,
  templateUrl: './promotions-view-edit-add.component.html',
  styleUrl: './promotions-view-edit-add.component.scss',
})
export class PromotionsViewEditAddComponent extends BaseComponent implements OnInit {
  // private dialogRef = inject(MatDialogRef<ProductCategoryUpsertComponent>);
  // private data = inject<ProductCategoryDialogData>(MAT_DIALOG_DATA);
  // private formService = inject(ProductCategoryFormService);
  private api = inject(PromotionsApiService);
  private apiProducts = inject(ProductsApiService);
  private toaster = inject(ToasterService);
  private router = inject(Router);
  private route = inject(ActivatedRoute);
  private fb = inject(FormBuilder);

  form!: FormGroup;
  mode: 'view' | 'edit' | 'add' = 'view';
  promotionId!: number;
  products!: ListProductsQueryDto[];

  ngOnInit(): void {
    this.form = this.createPromotionForm();

    this.promotionId = +this.route.snapshot.params['id'];
    this.mode = this.route.snapshot.data['mode'];

    this.startLoading();

    if (this.mode === 'add') {
      this.apiProducts.list().subscribe({
        next: (products) => {
          this.products = products.items;
          this.stopLoading();
        },
        error: () => {
          this.toaster.error('Failed to load products!');
          this.stopLoading();
        },
      });
    } else {
      forkJoin({
        products: this.apiProducts.list(),
        promotion: this.api.getById(this.promotionId),
      }).subscribe({
        next: ({ products, promotion }) => {
          this.products = products.items;
          this.form = this.createPromotionForm(promotion);
          if (this.mode === 'view') {
            this.form.disable();
          }
          this.stopLoading();
        },
        error: () => {
          this.toaster.error('Failed to load!');
          this.stopLoading();
        },
      });
    }
    console.log(this.form.value);
  }

  onSubmit(): void {
    if (this.form.invalid || this.isLoading) {
      this.form.markAllAsTouched();
      return;
    }

    this.isLoading = true;

    if (this.mode === 'add') {
      let command: CreatePromotionCommand = this.form.getRawValue();

      this.api.create(command).subscribe({
        next: () => {
          this.toaster.success('Successfully added promotion!');
          this.stopLoading();
        },
        error: () => {
          this.toaster.error('Error adding promotion!');
          this.stopLoading();
        },
      });
    } else if (this.mode === 'edit') {
      let command: UpdatePromotionCommand = this.form.getRawValue();

      this.api.update(this.promotionId, command).subscribe({
        next: () => {
          this.toaster.success('Successfully updated promotion!');
          this.stopLoading();
        },
        error: () => {
          this.toaster.error('Error updating promotion!');
          this.stopLoading();
        },
      });
    }
    this.router.navigate(['/admin/promotions']);
  }

  onCancel() {
    console.log(this.form.value);
    this.router.navigate(['/admin/promotions']);
  }

  /**
   * Create a product category form with validation.
   * If category data is provided, form is pre-filled (edit mode).
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
      isActive: [promotion?.isActive ?? true, [Validators.required]],
      startsAtUtc: [promotion?.startsAtUtc ?? null, [Validators.required]],
      endsAtUtc: [promotion?.endsAtUtc ?? null, [Validators.required]],
      sortOrder: [promotion?.sortOrder ?? 0, [Validators.required]],

      promotionItems: this.fb.array(
        (promotion?.promotionItems ?? []).map((item) => this.createPromotionItemForm(item)),
      ),
    });
  }

  createPromotionItemForm(item?: GetByIdPromotionQueryDtoPromotionItem): FormGroup {
    return this.fb.group({
      productId: [item?.productId ?? null, [Validators.required]],
      discountPercent: [item?.discountPercent ?? 0, [Validators.required]],
    });
  }

  get promotionItems(): FormArray {
    return this.form.get('promotionItems') as FormArray;
  }

  addItem() {
    this.promotionItems.push(this.createPromotionItemForm());
  }

  removeItem(index: number) {
    this.promotionItems.removeAt(index);
  }

  /**
   * Get validation error message for a form control.
   */
  getErrorMessage(controlName: string): string {
    const control = this.form.get(controlName);
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

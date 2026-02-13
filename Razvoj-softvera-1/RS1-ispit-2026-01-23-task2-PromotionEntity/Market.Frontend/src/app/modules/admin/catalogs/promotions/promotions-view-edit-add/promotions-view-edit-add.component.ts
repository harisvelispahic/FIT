import { Component, inject, OnInit } from '@angular/core';
import { BaseComponent } from '../../../../../core/components/base-classes/base-component';
import { PromotionsApiService } from '../../../../../api-services/promotions/promotions-api.service';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { FormArray, FormBuilder, FormGroup, Validators } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import {
  CreatePromotionCommand,
  GetPromotionByIdQueryDtoItem,
  GetPromotionByIdQueryDto,
  UpdatePromotionCommand,
} from '../../../../../api-services/promotions/promotions-api.models';
import {
  ListProductsQueryDto,
  ListProductsResponse,
} from '../../../../../api-services/products/products-api.models';
import { ProductsApiService } from '../../../../../api-services/products/products-api.service';
import { forkJoin } from 'rxjs';

@Component({
  selector: 'app-promotions-view-edit-add',
  standalone: false,
  templateUrl: './promotions-view-edit-add.component.html',
  styleUrl: './promotions-view-edit-add.component.scss',
})
export class PromotionsViewEditAddComponent extends BaseComponent implements OnInit {
  private api = inject(PromotionsApiService);
  private apiProducts = inject(ProductsApiService);
  private toaster = inject(ToasterService);
  private router = inject(Router);
  private route = inject(ActivatedRoute);
  private fb = inject(FormBuilder);

  form!: FormGroup;
  mode!: 'view' | 'edit' | 'add';
  promotionId!: number;
  products!: ListProductsQueryDto[];

  ngOnInit(): void {
    this.form = this.createPromotionForm();

    this.promotionId = +this.route.snapshot.params['id'];
    this.mode = this.route.snapshot.data['mode'] ?? 'view';

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
        },
        error: () => {
          this.toaster.error('Failed to load!');
          this.stopLoading();
        },
      });
    }
  }

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

  createPromotionItemForm(promotionItem?: GetPromotionByIdQueryDtoItem) {
    return this.fb.group({
      productId: [
        promotionItem?.productId ? +promotionItem.productId : null,
        [Validators.required],
      ],
      discountPercent: [promotionItem?.discountPercent ?? '', [Validators.required]],
    });
  }

  get promotionItems(): FormArray {
    return this.form.get('promotionItems') as FormArray;
  }

  addPromotionItem(): void {
    this.promotionItems.push(this.createPromotionItemForm());
  }

  removePromotionItem(index: number) {
    this.promotionItems.removeAt(index);
  }

  onSubmit(): void {
    if (this.form.invalid) {
      this.form.markAllAsTouched();
      return;
    }
    console.log(this.form.value);

    this.startLoading();

    if (this.mode === 'add') {
      let command: CreatePromotionCommand = this.form.getRawValue();
      this.api.create(command).subscribe({
        next: () => {
          this.toaster.success('Successfully created promotion!');
          this.stopLoading();
        },
        error: () => {
          this.toaster.error('Error creating promotion!');
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

  // private loadPromotion(id: number): void {
  //   this.startLoading();

  //   this.api.getById(id).subscribe({
  //     next: (result) => {
  //       // this.promotion = result;
  //       // console.log(this.promotion);
  //       this.form = this.createPromotionForm(result);
  //       if (this.mode === 'view') {
  //         this.form.disable();
  //       }
  //       this.stopLoading();
  //     },
  //     error: (err) => {
  //       this.toaster.error('Failed to load promotion');
  //       this.stopLoading();
  //     },
  //   });
  // }

  // private createPromotion(): void {
  //   const command: CreatePromotionCommand = this.form.getRawValue();

  //   this.startLoading();
  //   this.api.create(command).subscribe({
  //     next: () => {
  //       this.toaster.success('Category created successfully');
  //       this.stopLoading();
  //     },
  //     error: (err) => {
  //       this.toaster.error('Create category error:', err);
  //       this.stopLoading();
  //     },
  //   });
  // }

  // private updatePromotion(): void {
  //   const command: UpdatePromotionCommand = this.form.getRawValue();

  //   this.startLoading();

  //   this.api.update(this.promotionId, command).subscribe({
  //     next: () => {
  //       this.toaster.success('Category updated successfully');
  //       this.stopLoading();
  //     },
  //     error: (err) => {
  //       this.toaster.error('Update category error:', err);
  //       this.stopLoading();
  //     },
  //   });
  // }

  onCancel(): void {
    this.router.navigate(['/admin/promotions']);
  }

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

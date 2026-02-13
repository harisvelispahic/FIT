import { Component, inject, OnInit } from '@angular/core';
import { PromotionsApiService } from '../../../../../api-services/promotions/promotions-api.service';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { FormArray, FormBuilder, FormGroup, Validators } from '@angular/forms';
import { BaseComponent } from '../../../../../core/components/base-classes/base-component';
import { ActivatedRoute, Router } from '@angular/router';
import {
  GetPromotionByIdQueryDtoItem,
  GetPromotionByIdQueryDto,
  CreatePromotionCommand,
  UpdatePromotionCommand,
} from '../../../../../api-services/promotions/promotions-api.models';
import { ListProductsQueryDto } from '../../../../../api-services/products/products-api.models';
import { forkJoin } from 'rxjs';
import { ProductsApiService } from '../../../../../api-services/products/products-api.service';

@Component({
  selector: 'app-promotions-view-edit-add-details',
  standalone: false,
  templateUrl: './promotions-view-edit-add-details.component.html',
  styleUrl: './promotions-view-edit-add-details.component.scss',
})
export class PromotionsViewEditAddComponent extends BaseComponent implements OnInit {
  private api = inject(PromotionsApiService);
  private apiProducts = inject(ProductsApiService);
  private toaster = inject(ToasterService);
  private route = inject(ActivatedRoute);
  private fb = inject(FormBuilder);
  private router = inject(Router);

  form!: FormGroup;
  promotionId!: number;
  products!: ListProductsQueryDto[];

  mode: 'view' | 'edit' | 'add' = 'view';

  ngOnInit(): void {
    this.form = this.createPromotionForm();

    this.promotionId = +this.route.snapshot.params['id'];
    this.mode = this.route.snapshot.data['mode'] ?? 'view';

    this.startLoading();

    if (this.mode === 'add') {
      this.apiProducts.list().subscribe({
        next: (response) => {
          this.products = response.items;
          this.stopLoading();
        },
        error: () => {
          this.toaster.error('Error loading products');
          this.stopLoading();
        },
      });
    } else {
      forkJoin({
        promotion: this.api.getById(this.promotionId),
        products: this.apiProducts.list(),
      }).subscribe({
        next: ({ promotion, products }) => {
          this.form = this.createPromotionForm(promotion);
          this.products = products.items;
          if (this.mode === 'view') {
            this.form.disable();
          }
          this.stopLoading();
        },
        error: () => {
          this.toaster.error('Failed to load promotion');
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
      imageUrl: [promotion?.imageUrl ?? '', [Validators.required]],
      targetUrl: [promotion?.imageUrl ?? '', [Validators.required]],
      isActive: [promotion?.isActive ?? false, [Validators.required]],
      startsAtUtc: [promotion?.startsAtUtc ?? null, [Validators.required]],
      endsAtUtc: [promotion?.endsAtUtc ?? null, [Validators.required]],
      sortOrder: [promotion?.sortOrder ?? 0, [Validators.required]],
      promotionItems: this.fb.array(
        (promotion?.promotionItems ?? []).map((item) => this.createPromotionItemForm(item)),
      ),
    });
  }

  createPromotionItemForm(item?: GetPromotionByIdQueryDtoItem): FormGroup {
    return this.fb.group({
      productId: [item?.productId ?? null, [Validators.required]],
      // productName: [item?.productName ?? null, [Validators.required]],
      discountPercent: [item?.discountPercent ?? 0, [Validators.required]],
    });
  }

  get promotionItems(): FormArray {
    return this.form.get('promotionItems') as FormArray;
  }

  onSubmit() {
    if (this.form.invalid) {
      this.toaster.error('Please fill all required fields.');
      return;
    }

    if (this.mode === 'add') {
      let command: CreatePromotionCommand = this.form.getRawValue();
      console.log(command);
      this.startLoading();
      this.api.create(command).subscribe({
        next: (response) => {
          this.toaster.success('Successfully added promotion!');
          this.stopLoading();
        },
        error: (err) => {
          this.toaster.error('Error while adding promotion!');
          this.stopLoading();
        },
      });
    } else if (this.mode === 'edit') {
      let command: UpdatePromotionCommand = this.form.getRawValue();
      this.startLoading();
      this.api.update(this.promotionId, command).subscribe({
        next: (response) => {
          this.toaster.success('Successfully updated promotion!');
          this.stopLoading();
        },
        error: (err) => {
          this.toaster.error('Error while updating promotion!');
          this.stopLoading();
        },
      });
    }
    this.router.navigate(['/admin/promotions']);
  }

  addPromotionItem(): void {
    this.promotionItems.push(
      this.fb.group({
        productId: [null, [Validators.required]],
        discountPercent: [0, [Validators.required]],
      }),
    );
  }

  removePromotionItem(index: number): void {
    this.promotionItems.removeAt(index);
  }

  // createPromotionForm(promotion?: GetPromotionByIdQueryDto): FormGroup {
  //   return this.fb.group({
  //     title: [
  //       promotion?.title ?? '',
  //       [Validators.required, Validators.minLength(3), Validators.maxLength(100)],
  //     ],
  //     imageUrl: [promotion?.imageUrl ?? '', [Validators.required]],
  //     targetUrl: [promotion?.imageUrl ?? '', [Validators.required]],
  //     isActive: [promotion?.isActive ?? false, [Validators.required]],
  //     startsAtUtc: [promotion?.startsAtUtc ?? null, [Validators.required]],
  //     endsAtUtc: [promotion?.endsAtUtc ?? null, [Validators.required]],
  //     sortOrder: [promotion?.sortOrder ?? 0, [Validators.required]],
  //   });
  // }
}

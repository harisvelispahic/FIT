import { Component, inject, OnInit } from '@angular/core';
import { PromotionFormService } from '../services/promotion-form.service';
import { PromotionsApiService } from '../../../../../api-services/promotions/promotions-api.service';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { FormGroup } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import {
  CreatePromotionCommand,
  UpdatePromotionCommand,
} from '../../../../../api-services/promotions/promotions-api.model';
import { MatSort } from '@angular/material/sort';

@Component({
  selector: 'app-promotions-upsert',
  standalone: false,
  templateUrl: './promotions-upsert.component.html',
  styleUrl: './promotions-upsert.component.scss',
  providers: [PromotionFormService],
})
export class PromotionsUpsertComponent implements OnInit {
  // private dialogRef = inject(MatDialogRef<ProductCategoryUpsertComponent>);
  // private data = inject<ProductCategoryDialogData>(MAT_DIALOG_DATA);
  private api = inject(PromotionsApiService);
  private formService = inject(PromotionFormService);
  private toaster = inject(ToasterService);
  private route = inject(ActivatedRoute);
  private router = inject(Router);

  form!: FormGroup;
  isLoading = false;
  isEditMode = false;

  promotionId!: number;

  ngOnInit(): void {
    this.form = this.formService.createPromotionForm();
    this.promotionId = this.route.snapshot.params['id'];
    this.isEditMode = !!this.promotionId;

    if (this.isEditMode && this.promotionId) {
      this.loadPromotion(this.promotionId);
    }
  }

  private loadPromotion(id: number): void {
    this.isLoading = true;

    this.api.getById(id).subscribe({
      next: (category) => {
        this.form = this.formService.createPromotionForm(category);
        this.isLoading = false;
      },
      error: (err) => {
        this.toaster.error('Failed to load category');
        console.error('Load category error:', err);
        this.isLoading = false;
      },
    });
  }

  onSubmit(): void {
    if (this.form.invalid || this.isLoading) {
      this.form.markAllAsTouched();
      return;
    }

    this.isLoading = true;

    if (this.isEditMode && this.promotionId) {
      this.updatePromotion();
    } else {
      this.createPromotion();
    }
    this.onCancel();
  }

  private createPromotion(): void {
    const command: CreatePromotionCommand = {
      title: this.form.value.title.trim(),
      imageUrl: this.form.value.imageUrl.trim(),
      targetUrl: this.form.value.targetUrl.trim(),
      isActive: this.form.value.isActive,
      startsAtUtc: this.form.value.startsAtUtc,
      endsAtUtc: this.form.value.endsAtUtc,
      sortOrder: this.form.value.sortOrder,
    };

    this.api.create(command).subscribe({
      next: () => {
        this.toaster.success('Promotion created successfully');
        this.isLoading = false;
      },
      error: (err) => {
        console.error('Create promotion error:', err);
        this.isLoading = false;
      },
    });
  }

  private updatePromotion(): void {
    const command: UpdatePromotionCommand = {
      id: this.promotionId,
      title: this.form.value.title.trim(),
      imageUrl: this.form.value.imageUrl.trim(),
      targetUrl: this.form.value.targetUrl.trim(),
      isActive: this.form.value.isActive,
      startsAtUtc: this.form.value.startsAtUtc,
      endsAtUtc: this.form.value.endsAtUtc,
      sortOrder: this.form.value.sortOrder,
    };

    this.api.update(this.promotionId!, command).subscribe({
      next: () => {
        this.toaster.success('Promotion updated successfully');
        this.isLoading = false;
      },
      error: (err) => {
        console.error('Update promotion error:', err);
        this.isLoading = false;
      },
    });
  }

  onCancel(): void {
    this.router.navigate(['/admin/promotions']);
  }

  getErrorMessage(controlName: string): string {
    return this.formService.getErrorMessage(this.form, controlName);
  }
}

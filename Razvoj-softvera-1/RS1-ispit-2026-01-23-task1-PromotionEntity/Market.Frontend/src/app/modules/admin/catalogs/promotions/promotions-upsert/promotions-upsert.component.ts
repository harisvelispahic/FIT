import { Component, inject, OnInit } from '@angular/core';
import { PromotionFormService } from '../services/promotion-form.service';
import { BaseComponent } from '../../../../../core/components/base-classes/base-component';
import { PromotionsApiService } from '../../../../../api-services/promotions/promotions-api.service';
import { ToasterService } from '../../../../../core/services/toaster.service';
import { FormGroup } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import {
  CreatePromotionCommand,
  UpdatePromotionCommand,
} from '../../../../../api-services/promotions/promotions-api.model';

@Component({
  selector: 'app-promotions-upsert',
  standalone: false,
  templateUrl: './promotions-upsert.component.html',
  styleUrl: './promotions-upsert.component.scss',
  providers: [PromotionFormService],
})
export class PromotionsUpsertComponent extends BaseComponent implements OnInit {
  // private dialogRef = inject(MatDialogRef<PromotionUpsertComponent>);
  private api = inject(PromotionsApiService);
  private formService = inject(PromotionFormService);
  private toaster = inject(ToasterService);
  private router = inject(Router);
  private route = inject(ActivatedRoute);

  form!: FormGroup;
  isEditMode = false;
  promotionId!: number;

  ngOnInit(): void {
    this.form = this.formService.createPromotionForm();

    this.promotionId = +this.route.snapshot.params['id'];
    this.isEditMode = !!this.promotionId;

    if (this.isEditMode && this.promotionId) {
      this.loadPromotion(this.promotionId);
    }
  }

  private loadPromotion(id: number): void {
    this.isLoading = true;

    this.api.getById(id).subscribe({
      next: (promotion) => {
        this.form = this.formService.createPromotionForm(promotion);
        this.isLoading = false;
      },
      error: (err) => {
        this.toaster.error('Failed to load category');
        console.error('Load category error:', err);
        this.stopLoading();
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
    const command: CreatePromotionCommand = this.form.getRawValue();

    this.api.create(command).subscribe({
      next: () => {
        this.toaster.success('Category created successfully');
        this.stopLoading();
      },
      error: (err) => {
        this.toaster.error('Create category error:', err);
        this.stopLoading();
      },
    });
  }

  private updatePromotion(): void {
    const command: UpdatePromotionCommand = this.form.getRawValue();

    this.api.update(this.promotionId, command).subscribe({
      next: () => {
        this.toaster.success('Category updated successfully');
      },
      error: (err) => {
        this.isLoading = false;
        console.error('Update category error:', err);
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

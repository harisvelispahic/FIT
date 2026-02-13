import { Component, inject, OnInit } from '@angular/core';
import {
  ListPromotionsQueryDto,
  ListPromotionsRequest,
} from '../../../../api-services/promotions/promotions-api.models';
import { BaseListPagedComponent } from '../../../../core/components/base-classes/base-list-paged-component';
import { PromotionsApiService } from '../../../../api-services/promotions/promotions-api.service';
import { Router } from '@angular/router';
import { ToasterService } from '../../../../core/services/toaster.service';
import { DialogHelperService } from '../../../shared/services/dialog-helper.service';
import { DialogButton } from '../../../shared/models/dialog-config.model';
import { debounceTime, distinctUntilChanged, Subject, takeUntil } from 'rxjs';
import { FormControl } from '@angular/forms';

@Component({
  selector: 'app-promotions',
  standalone: false,
  templateUrl: './promotions.component.html',
  styleUrl: './promotions.component.scss',
})
export class PromotionsComponent
  extends BaseListPagedComponent<ListPromotionsQueryDto, ListPromotionsRequest>
  implements OnInit
{
  private api = inject(PromotionsApiService);
  private router = inject(Router);
  private toaster = inject(ToasterService);
  private dialogHelper = inject(DialogHelperService);
  private destroy$ = new Subject<void>();

  searchControl = new FormControl('');

  /**
   *
   */
  constructor() {
    super();
    this.request = new ListPromotionsRequest();
    this.request.isActive = true;
  }

  ngOnInit(): void {
    // this.initList();
    this.loadPagedData();
    this.setupSearchDebounce();
  }

  ngOnDestroy(): void {
    this.destroy$.next();
    this.destroy$.complete();
  }

  protected override loadPagedData(): void {
    this.startLoading();

    this.api.list(this.request).subscribe({
      next: (response) => {
        this.handlePageResult(response);
        this.stopLoading();
      },
      error: (err) => {
        console.error('Load promotions error:', err);
        this.stopLoading('Failed to load promotions');
      },
    });
  }

  private setupSearchDebounce(): void {
    this.searchControl.valueChanges
      .pipe(
        debounceTime(400), // Wait 400ms after user stops typing
        distinctUntilChanged(), // Only if value actually changed
        takeUntil(this.destroy$),
      )
      .subscribe((searchTerm) => {
        this.onSearchChange(searchTerm || '');
      });
  }

  onSearchChange(searchTerm: string): void {
    this.request.search = searchTerm;
    this.request.paging.page = 1; // Reset to first page
    this.loadPagedData();
  }

  onAdd(): void {
    this.router.navigate(['/admin/promotions/add']);
  }

  onEdit(promotion: ListPromotionsQueryDto): void {
    this.router.navigate(['/admin/promotions/edit', promotion.id]);
  }

  onViewDetails(promotion: ListPromotionsQueryDto, event?: MouseEvent) {
    event?.stopPropagation();
    this.router.navigate(['/admin/promotions/view-details', promotion.id]);
  }

  onDelete(promotion: ListPromotionsQueryDto): void {
    this.dialogHelper.product.confirmDelete(promotion.title).subscribe((result) => {
      if (result && result.button === DialogButton.DELETE) {
        this.performDelete(promotion);
      }
    });
  }

  private performDelete(promotion: ListPromotionsQueryDto): void {
    this.startLoading();

    this.api.delete(promotion.id).subscribe({
      next: () => {
        this.dialogHelper.product.showDeleteSuccess().subscribe();
        this.loadPagedData();
      },
      error: (err) => {
        this.stopLoading();

        this.dialogHelper
          .showError('DIALOGS.TITLES.ERROR', 'PRODUCTS.DIALOGS.ERROR_DELETE')
          .subscribe();

        console.error('Delete promotion error:', err);
      },
    });
  }
}

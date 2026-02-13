import { Component, inject, OnInit } from '@angular/core';
import { FormArray, FormBuilder, FormGroup, Validators } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import { OrdersApiService } from '../../../../api-services/orders/orders-api.service';
import { ProductsApiService } from '../../../../api-services/products/products-api.service';
import { ToasterService } from '../../../../core/services/toaster.service';
import { DialogHelperService } from '../../../shared/services/dialog-helper.service';
import { DialogButton } from '../../../shared/models/dialog-config.model';
import {
  GetOrderByIdQueryDto,
  UpdateOrderCommand,
  UpdateOrderCommandItem,
  OrderStatusType
} from '../../../../api-services/orders/orders-api.models';
import { ListProductsQueryDto } from '../../../../api-services/products/products-api.models';

@Component({
  selector: 'app-order-edit',
  standalone: false,
  templateUrl: './order-edit.component.html',
  styleUrl: './order-edit.component.scss'
})
export class OrderEditComponent implements OnInit {
  private route = inject(ActivatedRoute);
  private router = inject(Router);
  private fb = inject(FormBuilder);
  private ordersApi = inject(OrdersApiService);
  private productsApi = inject(ProductsApiService);
  private toaster = inject(ToasterService);
  private dialogHelper = inject(DialogHelperService);

  form!: FormGroup;
  isLoading = false;
  isSaving = false;
  orderId!: number;
  order?: GetOrderByIdQueryDto;

  // Products list for dropdown
  availableProducts: ListProductsQueryDto[] = [];
  isLoadingProducts = false;

  ngOnInit(): void {
    this.orderId = Number(this.route.snapshot.paramMap.get('id'));

    if (!this.orderId || isNaN(this.orderId)) {
      this.toaster.error('Invalid order ID');
      this.router.navigate(['/admin/orders']);
      return;
    }

    this.initForm();
    this.loadProducts();
    this.loadOrder();
  }

  private initForm(): void {
    this.form = this.fb.group({
      note: [''],
      items: this.fb.array([])
    });
  }

  get items(): FormArray {
    return this.form.get('items') as FormArray;
  }

  private loadOrder(): void {
    this.isLoading = true;

    this.ordersApi.getById(this.orderId).subscribe({
      next: (order) => {
        this.order = order;

        // Check if order is Draft
        if (order.status !== OrderStatusType.Draft) {
          this.toaster.error('Only draft orders can be edited');
          this.router.navigate(['/admin/orders']);
          return;
        }

        // Populate form
        this.form.patchValue({
          note: order.note || ''
        });

        // Populate items
        this.items.clear();
        order.items.forEach(item => {
          this.items.push(this.createItemFormGroup(item));
        });

        this.isLoading = false;
      },
      error: (err) => {
        this.isLoading = false;
        this.toaster.error('Failed to load order');
        console.error('Load order error:', err);
        this.router.navigate(['/admin/orders']);
      }
    });
  }

  private loadProducts(): void {
    this.isLoadingProducts = true;

    this.productsApi.list({ paging: { page: 1, pageSize: 1000 } }).subscribe({
      next: (response) => {
        this.availableProducts = response.items;
        this.isLoadingProducts = false;
      },
      error: (err) => {
        this.isLoadingProducts = false;
        this.toaster.error('Failed to load products');
        console.error('Load products error:', err);
      }
    });
  }

  private createItemFormGroup(item?: any): FormGroup {
    const group = this.fb.group({
      id: [item?.id || 0],
      productId: [item?.product?.productId || null, Validators.required],
      quantity: [item?.quantity || 1, [Validators.required, Validators.min(1)]],
      unitPrice: [{ value: item?.unitPrice || 0, disabled: true }],
      subtotal: [{ value: item?.subtotal || 0, disabled: true }],
      total: [{ value: item?.total || 0, disabled: true }]
    });

    // Subscribe to changes for real-time calculations
    group.get('productId')?.valueChanges.subscribe(() => this.calculateItemTotals(group));
    group.get('quantity')?.valueChanges.subscribe(() => this.calculateItemTotals(group));

    return group;
  }

  addItem(): void {
    this.items.push(this.createItemFormGroup());
  }

  removeItem(index: number): void {
    // Show warning if trying to remove all items
    if (this.items.length === 1) {
      this.dialogHelper.showWarning(
        'DIALOGS.TITLES.WARNING',
        'Da li ste sigurni da želite obrisati sve stavke? Narudžba će biti automatski otkazana.'
      ).subscribe(result => {
        if (result && result.button === DialogButton.YES) {
          this.items.removeAt(index);
        }
      });
    } else {
      this.items.removeAt(index);
    }
  }

  private calculateItemTotals(itemGroup: FormGroup): void {
    const productId = itemGroup.get('productId')?.value;
    const quantity = itemGroup.get('quantity')?.value || 0;

    if (!productId || quantity <= 0) {
      itemGroup.patchValue({
        unitPrice: 0,
        subtotal: 0,
        total: 0
      }, { emitEvent: false });
      this.calculateOrderTotal();
      return;
    }

    // Find product
    const product = this.availableProducts.find(p => p.id === productId);
    if (!product) {
      return;
    }

    const unitPrice = product.price;
    const subtotal = unitPrice * quantity;
    const discountPercent = 0.05; // 5% discount
    const discountAmount = subtotal * discountPercent;
    const total = subtotal - discountAmount;

    itemGroup.patchValue({
      unitPrice: this.roundMoney(unitPrice),
      subtotal: this.roundMoney(subtotal),
      total: this.roundMoney(total)
    }, { emitEvent: false });

    this.calculateOrderTotal();
  }

  private calculateOrderTotal(): number {
    let total = 0;
    this.items.controls.forEach(item => {
      total += item.get('total')?.value || 0;
    });
    return this.roundMoney(total);
  }

  getOrderTotal(): number {
    return this.calculateOrderTotal();
  }

  private roundMoney(value: number): number {
    return Math.round(value * 100) / 100;
  }

  getProductName(productId: number): string {
    const product = this.availableProducts.find(p => p.id === productId);
    return product?.name || '';
  }

  onSubmit(): void {
    if (this.form.invalid || this.isSaving) {
      this.form.markAllAsTouched();
      return;
    }

    // Check if items array is empty
    if (this.items.length === 0) {
      this.dialogHelper.showWarning(
        'DIALOGS.TITLES.WARNING',
        'Narudžba nema stavki i biće automatski otkazana. Da li želite nastaviti?'
      ).subscribe(result => {
        if (result && result.button === DialogButton.YES) {
          this.performUpdate();
        }
      });
      return;
    }

    this.performUpdate();
  }

  private performUpdate(): void {
    this.isSaving = true;

    const payload = this.form.getRawValue();

    this.ordersApi.update(this.orderId, payload).subscribe({
      next: () => {
        this.isSaving = false;
        this.toaster.success('Narudžba uspješno ažurirana');
        this.router.navigate(['/admin/orders']);
      },
      error: (err) => {
        this.isSaving = false;
        this.toaster.error('Failed to update order');
        console.error('Update order error:', err);
      }
    });
  }

  onCancel(): void {
    this.router.navigate(['/admin/orders']);
  }
}

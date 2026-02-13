import { Component, OnInit, inject } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { OrdersApiService } from '../../../api-services/orders/orders-api.service';
import { GetOrderByIdQueryDto, OrderStatusType } from '../../../api-services/orders/orders-api.models';

@Component({
  selector: 'app-client-order-details',
  standalone: false,
  templateUrl: './client-order-details.component.html',
  styleUrl: './client-order-details.component.scss'
})
export class ClientOrderDetailsComponent implements OnInit {
  private ordersApi = inject(OrdersApiService);
  private route = inject(ActivatedRoute);
  private router = inject(Router);

  order: GetOrderByIdQueryDto | null = null;
  loading = true;
  error = false;

  ngOnInit(): void {
    const id = Number(this.route.snapshot.paramMap.get('id'));
    if (id) {
      this.loadOrder(id);
    } else {
      this.router.navigate(['/client/orders']);
    }
  }

  loadOrder(id: number): void {
    this.loading = true;
    this.error = false;

    this.ordersApi.getById(id).subscribe({
      next: (order) => {
        this.order = order;
        this.loading = false;
      },
      error: (err) => {
        console.error('Failed to load order', err);
        this.error = true;
        this.loading = false;
      }
    });
  }

  getStatusLabel(status: OrderStatusType): string {
    switch (status) {
      case OrderStatusType.Draft: return 'Nacrt';
      case OrderStatusType.Confirmed: return 'Potvrđeno';
      case OrderStatusType.Paid: return 'Plaćeno';
      case OrderStatusType.Completed: return 'Završeno';
      case OrderStatusType.Cancelled: return 'Otkazano';
      default: return 'Nepoznato';
    }
  }

  getStatusClass(status: OrderStatusType): string {
    switch (status) {
      case OrderStatusType.Draft: return 'status-draft';
      case OrderStatusType.Confirmed: return 'status-confirmed';
      case OrderStatusType.Paid: return 'status-paid';
      case OrderStatusType.Completed: return 'status-completed';
      case OrderStatusType.Cancelled: return 'status-cancelled';
      default: return 'status-unknown';
    }
  }

  formatDate(dateString: string): string {
    return new Date(dateString).toLocaleDateString('bs-BA', {
      day: '2-digit',
      month: '2-digit',
      year: 'numeric',
      hour: '2-digit',
      minute: '2-digit'
    });
  }

  goBack(): void {
    this.router.navigate(['/client/orders']);
  }
}

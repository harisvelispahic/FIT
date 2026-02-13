import { Component, OnInit, inject } from '@angular/core';
import { Router } from '@angular/router';
import { OrdersApiService } from '../../../api-services/orders/orders-api.service';
import { ListOrdersQueryDto, OrderStatusType } from '../../../api-services/orders/orders-api.models';

@Component({
  selector: 'app-client-orders',
  standalone: false,
  templateUrl: './client-orders.component.html',
  styleUrl: './client-orders.component.scss'
})
export class ClientOrdersComponent implements OnInit {
  private ordersApi = inject(OrdersApiService);
  private router = inject(Router);

  orders: ListOrdersQueryDto[] = [];
  loading = true;
  error = false;

  ngOnInit(): void {
    this.loadOrders();
  }

  loadOrders(): void {
    this.loading = true;
    this.error = false;

    this.ordersApi.list().subscribe({
      next: (response) => {
        this.orders = response.items;
        this.loading = false;
      },
      error: (err) => {
        console.error('Failed to load orders', err);
        this.error = true;
        this.loading = false;
      }
    });
  }

  viewDetails(orderId: number): void {
    this.router.navigate(['/client/orders', orderId]);
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
}

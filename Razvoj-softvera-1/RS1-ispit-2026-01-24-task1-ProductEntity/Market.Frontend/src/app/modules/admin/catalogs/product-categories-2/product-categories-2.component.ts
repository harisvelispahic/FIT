import {Component, inject, OnInit} from '@angular/core';
import {ProductCategoriesApiService} from '../../../../api-services/product-categories/product-categories-api.service';
import {
  ListProductCategoriesQueryDto,
  ListProductCategoriesRequest
} from '../../../../api-services/product-categories/product-categories-api.model';
import {DialogHelperService} from '../../../shared/services/dialog-helper.service';
import {DialogButton} from '../../../shared/models/dialog-config.model';
import {ToasterService} from '../../../../core/services/toaster.service';
import {ActivatedRoute, Router} from '@angular/router';
import {BaseComponent} from '../../../../core/components/base-classes/base-component';
import {BaseListPagedComponent} from '../../../../core/components/base-classes/base-list-paged-component';

@Component({
  selector: 'app-product-categories-2',
  standalone: false,
  templateUrl: './product-categories-2.component.html',
  styleUrl: './product-categories-2.component.scss',
})
export class ProductCategories2Component extends BaseListPagedComponent<ListProductCategoriesQueryDto, ListProductCategoriesRequest> implements OnInit {

  private api = inject(ProductCategoriesApiService);
  private dialogHelper = inject(DialogHelperService);
  private toaster = inject(ToasterService);
  private router = inject(Router);
  private route = inject(ActivatedRoute);

  searchValue="";

constructor() {
  super();
  this.request = new ListProductCategoriesRequest();
  this.request.onlyEnabled = true;
  this.request.paging.pageSize = 100;
}


  ngOnInit(): void {

    this.initList();
  }

  protected override loadPagedData(): void {
    this.startLoading();
    this.api.list(this.request).subscribe({
      next: (response) => {
        this.handlePageResult(response);
        this.toaster.success("ok su podaci: " + this.totalItems);
        this.stopLoading();
      },
      error: (error) => {
        this.toaster.error(error.message);
        this.stopLoading();
      }
    });
  }

  changeStatus(x: ListProductCategoriesQueryDto, $event: Event) {
    this.startLoading();
    if (x.isEnabled){
      this.api.disable(x.id).subscribe({
        next: response =>{
          this.toaster.success("update je uspješan: ");
          this.ngOnInit();
        },
        error: (error) => {
          this.toaster.error(error);
          this.ngOnInit();
        }
      })
    }
    else{
      this.api.enable(x.id).subscribe(
        {
          next: response =>{
            this.toaster.success("update je uspješan: ");
            this.ngOnInit();
          },
          error: (error) => {
            this.toaster.error(error);
            this.ngOnInit();
          }
        }
      )
    }
  }

  deleteAction(x: ListProductCategoriesQueryDto) {
    this.dialogHelper.productCategory.confirmDelete(x.name).subscribe((result) => {
      if (result && result.button === DialogButton.DELETE) {

        this.startLoading();
        this.api.delete(x.id).subscribe({
          next: response =>{
            this.ngOnInit();
            this.toaster.success(`Brisanje ${x.name} uspješno`)
            this.stopLoading();
          },
          error: (error) => {
            this.toaster.error(error.message);
            this.ngOnInit();

          }
        })
      }
      }

    );
  }

  searchAction() {

    this.api.list({
      paging:{
        page:1,
        pageSize: 1000
      },
      search: this.searchValue
    }).subscribe({
      next: (response) => {
        this.handlePageResult(response);
        //this.toaster.success("ok su podaci: " + this.productCategoriesList.length);
      },
      error: (error) => {
        this.toaster.error(error.message);
      }
    });

  }

  inputKeyDown($event: KeyboardEvent) {
    if($event.keyCode == 13){
      this.searchAction();
    }
  }

  editAction(x: ListProductCategoriesQueryDto) {
    this.router.navigate(['edit', x.id], {relativeTo: this.route});
  }
}

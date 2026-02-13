import {Component, inject, OnInit} from '@angular/core';
import {ActivatedRoute} from '@angular/router';
import {
  ProductCategoriesApiService
} from '../../../../../api-services/product-categories/product-categories-api.service';
import {
  GetProductCategoryByIdQueryDto
} from '../../../../../api-services/product-categories/product-categories-api.model';
import {BaseComponent} from '../../../../../core/components/base-classes/base-component';
import {FormBuilder, FormControl, FormGroup, Validators} from '@angular/forms';

@Component({
  selector: 'app-product-categories-edit',
  standalone: false,
  templateUrl: './product-categories-edit.component.html',
  styleUrl: './product-categories-edit.component.scss',
})
export class ProductCategoriesEditComponent extends BaseComponent implements OnInit {

  private route= inject(ActivatedRoute);
  private productCategoryId: number=0;
  private apiService = inject(ProductCategoriesApiService);
  public productCategoryDto: GetProductCategoryByIdQueryDto| null = null;
  private formBuilder =  inject(FormBuilder);
  public form: FormGroup = this.formBuilder.group({
    id: [0, [Validators.required]],
    name: ["", [Validators.required]],
    isEnabled : [true, [Validators.required]],
  })


    ngOnInit(): void {

      this.startLoading();
        this.productCategoryId = +this.route.snapshot.params['abc'];

        console.log("this.productCategoryId: " + this.productCategoryId);

        this.apiService.getById(this.productCategoryId).subscribe({
            next: (response) => {
              this.productCategoryDto = response;
              this.form.patchValue(response);
              this.stopLoading();
            },
            error: (err) => {
              console.error('Load categories error:', err);
              this.stopLoading();
            }
          }
        );
    }

  save() {
    if (this.form.invalid) {
      this.form.markAllAsTouched();
      return;
    }

    const payload = this.form.getRawValue();

    this.apiService.create(payload).subscribe({

    })
  }
}

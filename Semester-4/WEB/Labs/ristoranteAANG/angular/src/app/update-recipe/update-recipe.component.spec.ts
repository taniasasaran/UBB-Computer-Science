import { ComponentFixture, TestBed } from '@angular/core/testing';

import { UpdateRecipeComponent } from './update-recipe.component';

describe('UpdateRecipeComponent', () => {
  let component: UpdateRecipeComponent;
  let fixture: ComponentFixture<UpdateRecipeComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [UpdateRecipeComponent]
    });
    fixture = TestBed.createComponent(UpdateRecipeComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

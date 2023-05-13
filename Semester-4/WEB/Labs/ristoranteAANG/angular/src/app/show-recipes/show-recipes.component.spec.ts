import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ShowRecipesComponent } from './show-recipes.component';

describe('ShowRecipesComponent', () => {
  let component: ShowRecipesComponent;
  let fixture: ComponentFixture<ShowRecipesComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [ShowRecipesComponent]
    });
    fixture = TestBed.createComponent(ShowRecipesComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

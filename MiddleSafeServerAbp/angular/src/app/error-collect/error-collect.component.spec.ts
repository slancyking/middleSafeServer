import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ErrorCollectComponent } from './error-collect.component';

describe('ErrorCollectComponent', () => {
  let component: ErrorCollectComponent;
  let fixture: ComponentFixture<ErrorCollectComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ErrorCollectComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ErrorCollectComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

import { ComponentFixture, TestBed } from '@angular/core/testing';

import { NameCollectComponent } from './name-collect.component';

describe('NameCollectComponent', () => {
  let component: NameCollectComponent;
  let fixture: ComponentFixture<NameCollectComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ NameCollectComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(NameCollectComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

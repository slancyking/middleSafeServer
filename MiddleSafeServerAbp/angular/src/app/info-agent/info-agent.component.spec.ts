import { ComponentFixture, TestBed } from '@angular/core/testing';

import { InfoAgentComponent } from './info-agent.component';

describe('InfoAgentComponent', () => {
  let component: InfoAgentComponent;
  let fixture: ComponentFixture<InfoAgentComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ InfoAgentComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(InfoAgentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

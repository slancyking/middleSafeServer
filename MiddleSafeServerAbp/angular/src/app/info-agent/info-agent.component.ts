import { Component, OnInit } from '@angular/core';
import { ListService, PagedResultDto } from '@abp/ng.core';
import { query } from '@angular/animations';
import { UntypedFormBuilder, UntypedFormGroup, Validators } from '@angular/forms';
import { InfoAgentService, InfoAgentDto } from '@proxy/sk/info-agents';
import { ConfirmationService, Confirmation } from '@abp/ng.theme.shared';
import { LocalizationService } from '@abp/ng.core';
import {NavigationExtras,Router} from "@angular/router";



@Component({
  selector: 'app-info-agent',
  templateUrl: './info-agent.component.html',
  styleUrls: ['./info-agent.component.scss'],
  providers: [ListService],
})
export class InfoAgentComponent implements OnInit {

  infoAgentList = { items:[],totalCount:0} as PagedResultDto<InfoAgentDto>;
  isCreateModalOpen = false; //�½���Ŀ����Ĭ�ϲ���
  form: UntypedFormGroup; // add this line
  selectInfoAgent = {} as InfoAgentDto;

  constructor(public readonly list: ListService, 
    private infoAgentService : InfoAgentService,
    private fb: UntypedFormBuilder, // inject FormBuilder, 
    private confirmation: ConfirmationService, // inject the ConfirmationService
    private localizationService: LocalizationService,
    private router:Router ) { }

  ngOnInit(): void {
    const infoAgentStreamCreator = (query) => this.infoAgentService.getList(query);
    this.list.hookToQuery(infoAgentStreamCreator).subscribe((response)=>{
      this.infoAgentList = response;
      console.log(response);
    }); 
  }

  //查看分支
  seeNameCollect(id: string){

    let navigationExtras:NavigationExtras = {
      queryParams:{'infoAgentId': id}
    }
    this.router.navigate(['/name-collects'],navigationExtras).then((r: any) => console.log(r))
    
  }

  buildForm() {
    this.form = this.fb.group({
      Name: [this.selectInfoAgent.name || '', Validators.required],
      IsOpen:[this.selectInfoAgent.isOpen],
      Description: [this.selectInfoAgent.description]
    });
  }

  createInfoAgent() {
    this.selectInfoAgent = {} as InfoAgentDto;
    this.buildForm();
    this.isCreateModalOpen = true;
  }

  editInfoAgent(id: string) {
    this.infoAgentService.get(id).subscribe((infoAgent) => {
      this.selectInfoAgent = infoAgent;
      this.buildForm();
      this.isCreateModalOpen = true;
    });
  }

  delete(id: string,name: string) {

    let deleteWarn = this.localizationService.instant(
      { key: '::InfoAgentDeletionConfirmationMessage', defaultValue: 'Default Value' },
      name
    );
     
    this.confirmation.warn( deleteWarn, '::AreYouSure').subscribe((status) => {
      if (status === Confirmation.Status.confirm) {
        this.infoAgentService.delete(id).subscribe(() => this.list.get());
      }
    });
  }

  save() {
    if (this.form.invalid) { return; }

    const Therequest = this.selectInfoAgent.id
      ? this.infoAgentService.update(this.selectInfoAgent.id, this.form.value)
      : this.infoAgentService.create(this.form.value);
 
      Therequest.subscribe(null,null,() => {  
      this.isCreateModalOpen = false;
      this.form.reset();
      this.list.get();
      });
  }

}

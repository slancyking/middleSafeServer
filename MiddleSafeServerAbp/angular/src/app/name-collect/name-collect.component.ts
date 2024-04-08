import { ListService, LocalizationService, PagedResultDto } from '@abp/ng.core';
import { ConfirmationService } from '@abp/ng.theme.shared';
import { Component, OnInit } from '@angular/core';
import { UntypedFormBuilder, UntypedFormGroup, Validators } from '@angular/forms';
import { ActivatedRoute } from '@angular/router';
import { GetInfoAgentListDto, InfoAgentDto, InfoAgentService } from '@proxy/sk/info-agents';
import { NameCollectDto, NameCollectService } from '@proxy/sk/info-collects/name-collects';

@Component({
  selector: 'app-name-collect',
  templateUrl: './name-collect.component.html',
  styleUrls: ['./name-collect.component.scss'],
  providers: [ ListService ]
})
export class NameCollectComponent implements OnInit {

  nameCollectList = { items:[],totalCount:0} as PagedResultDto<NameCollectDto>;
  infoAgentId:string | undefined;;
  infoAgent = {} as InfoAgentDto;
  infoAgentList = { items:[],totalCount:0}  as  PagedResultDto<InfoAgentDto>;
  singlePage_infoAgent:number = 20;

  searchForm:UntypedFormGroup;
  formInfoAgentId: any;
  formFilter: any;


  isEditModalOpen:boolean = false; //编辑窗口是否打开 
  isDetailModalOpen:boolean = false; //详情页


  isShowSearch = false;

  constructor(public readonly list: ListService, 
    private infoAgentService : InfoAgentService,
    private route: ActivatedRoute,
    private nameCollectService : NameCollectService,
    private fb: UntypedFormBuilder, // inject FormBuilder, 
    private confirmation: ConfirmationService, // inject the ConfirmationService
    private localizationService: LocalizationService) { 
      this.route.queryParams.subscribe((r: any) => {  //根据参数获取当前分支信息
        this.infoAgentId = r.valueOf().branchId;
        if(this.infoAgentId != null){
          this.infoAgentService.get(this.infoAgentId).subscribe((infoAgent) => { 
            this.infoAgent = infoAgent;  
            console.log(infoAgent);
          });
        } 
      }) 
    } 

  ngOnInit(): void {
    const cardStreamCreator = (query) => {  //查询卡密列表时.branchId作为参数
      query["infoAgentId"] = this.infoAgentId;
      return this.nameCollectService.getList(query);
    };

    if(this.infoAgentList.totalCount == 0){
      this.getInfoAgentList(0);
    }

    
    this.list.hookToQuery(cardStreamCreator).subscribe((response)=>{
      this.nameCollectList = response;
        
      console.log(this.nameCollectList);
    });

  }

  getInfoAgentList(tmpSkip:number = 0):void{
    let query:GetInfoAgentListDto = {
      maxResultCount: this.singlePage_infoAgent,
      skipCount : tmpSkip
    };
    this.infoAgentService.getList(query).subscribe((response)=>{
      this.infoAgentList.totalCount = response.totalCount;
      this.infoAgentList.items = this.infoAgentList.items.concat(response.items);
      console.log(this.infoAgentList);
      if(tmpSkip + this.singlePage_infoAgent <this.infoAgentList.totalCount){
        this.getInfoAgentList(tmpSkip + this.singlePage_infoAgent); 
      } 
    });
  }

  search():void{

    this.formInfoAgentId = this.searchForm.value['infoAgentId'];
    this.formFilter = this.searchForm.value['filter']; 

    const cardStreamCreator = (query) => {  //查询卡密列表时.branchId作为参数
      query["infoAgentId"] = this.formInfoAgentId;
      query["filter"] = this.formFilter; 
      return this.nameCollectService.getList(query);
    };
 
    this.list.hookToQuery(cardStreamCreator).subscribe((response)=>{
      this.nameCollectList = response;
      console.log(this.nameCollectList);
    }); 
  }

  edit(id: string) {
    // this.cardService.get(id).subscribe((card) => {
    //   this.selectCard = card;
    //   this.buildEditForm();
    //   this.isEditModalOpen = true;
    // });
  }

  showDetail(id:string){
    // this.cardService.get(id).subscribe((card) => {
    //   this.selectCard = card;  
 
    //   console.log(this.cardChargingModeExp);
    //   this.isDetailModalOpen = true;
    // });
  }
  delete(id: string,password: string) {

    // let deleteWarn = this.localizationService.instant(
    //   { key: '::CardDeletionConfirmationMessage', defaultValue: 'Default Value' },
    //   password
    // );
     
    // this.confirmation.warn( deleteWarn, '::AreYouSure').subscribe((status) => {
    //   if (status === Confirmation.Status.confirm) {
    //     this.cardService.delete(id).subscribe(() => this.list.get());
    //   }
    // });
  }
  //导入表单
  buildSearchForm() : void{
    this.searchForm = this.fb.group({
      infoAgentId: [this.infoAgentId, Validators.required], 
      filter:[""] , 
    }); 
}
  showSearch(){
    if(!this.isShowSearch){
      this.buildSearchForm();
      this.isShowSearch = true;
    }else{
      this.isShowSearch = false;
    }
  }


}

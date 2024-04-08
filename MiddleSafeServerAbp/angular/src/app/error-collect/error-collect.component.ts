import { ListService, LocalizationService, PagedResultDto } from '@abp/ng.core';
import { Confirmation, ConfirmationService } from '@abp/ng.theme.shared';
import { Component, OnInit } from '@angular/core';
import { UntypedFormBuilder, UntypedFormGroup, Validators } from '@angular/forms';
import { BranchDto, BranchService, GetBranchListDto } from '@proxy/sk/branchs';
import { ErrorCollectDto, ErrorCollectService } from '@proxy/sk/error-collects';
import { NgbDateNativeAdapter, NgbDateAdapter ,NgbModal,NgbCollapse  } from '@ng-bootstrap/ng-bootstrap';

@Component({
  selector: 'app-error-collect',
  templateUrl: './error-collect.component.html',
  styleUrls: ['./error-collect.component.scss'],
  providers: [ListService]
})
export class ErrorCollectComponent implements OnInit { 

  objectKeys = Object.keys;

  errorList = { items:[],totalCount:0} as PagedResultDto<ErrorCollectDto>;
  
  branchId:string | undefined;
  branchList = { items:[],totalCount:0}  as  PagedResultDto<BranchDto>;
  singlePage_Branch:number = 20;

  isDetailModalOpen:boolean = false; //详情页 


  form: UntypedFormGroup; // add this line
  selectErrorCollect = {} as ErrorCollectDto; 
 
    

  search_errTitle:string =  "";
  search_errMessage:string = "";

  isShowSearch = false;
 
  searchForm:UntypedFormGroup;


  constructor(public readonly list: ListService, 
    private branchService : BranchService, 
    private errorCollectService : ErrorCollectService,
    private fb: UntypedFormBuilder, // inject FormBuilder, 
    private confirmation: ConfirmationService, // inject the ConfirmationService
    private localizationService: LocalizationService,  
    private modalService: NgbModal) { }

  ngOnInit(): void {


    const errStreamCreator = (query) => {  //查询卡密列表时.branchId作为参数 
      return this.errorCollectService.getList(query);
    };
 
    this.list.hookToQuery(errStreamCreator).subscribe((response)=>{
      this.errorList = response;
      console.log(this.errorList);
    });

  }


  getBranchList(tmpSkip:number):void{ 
    let query:GetBranchListDto = {
      maxResultCount: this.singlePage_Branch,
      skipCount : tmpSkip
    };
    this.branchService.getList(query).subscribe((response)=>{
      this.branchList.totalCount = response.totalCount;
      this.branchList.items = this.branchList.items.concat(response.items);
      console.log(this.branchList);
      if(tmpSkip + this.singlePage_Branch <this.branchList.totalCount){
        this.getBranchList(tmpSkip + this.singlePage_Branch); 
      } 
    });
  }
  //导入表单
  buildSearchForm() : void{
    this.searchForm = this.fb.group({
      branchId: [this.branchId], 
      errorTitle:[this.search_errTitle] ,
      errorMessage:[this.search_errMessage]  
    }); 
}
  showDetail(id:string){
    this.errorCollectService.get(id).subscribe((err) => {
      console.log("显示详情", err);
      this.selectErrorCollect = err;   
      this.isDetailModalOpen = true;
    });
  }
  showSearch(){

    if(this.branchList.totalCount == 0){
      this.getBranchList(0);
    }

    if(!this.isShowSearch){
      this.buildSearchForm();
      this.isShowSearch = true;
    }else{
      this.isShowSearch = false;
    }
  }


  delete(id: string, errorTitle: string) {

    let deleteWarn = this.localizationService.instant(
      { key: '::ErrorCollectDeletionConfirmationMessage', defaultValue: 'Default Value' },
      errorTitle
    );
     
    this.confirmation.warn( deleteWarn, '::AreYouSure').subscribe((status) => {
      if (status === Confirmation.Status.confirm) {
        this.errorCollectService.delete(id).subscribe(() => this.list.get());
      }
    });
  }
 
deleteSame(id: string, errorTitle: string) {

  let deleteWarn = this.localizationService.instant(
    { key: '::ErrorCollectDeletionSameConfirmationMessage', defaultValue: 'Default Value' },
    errorTitle
  );
   
  this.confirmation.warn( deleteWarn, '::AreYouSure').subscribe((status) => {
    if (status === Confirmation.Status.confirm) {
      this.errorCollectService.deleteSameErrorMessageById(id).subscribe(() => this.list.get());
    }
  });
}

 
getFileDescription(f:string,v:any):string{
   
  return v;
}

  search():void{

    this.branchId = this.searchForm.value['branchId'];
    this.search_errTitle = this.searchForm.value['errorTitle'];
    this.search_errMessage = this.searchForm.value['errorMessage']; 

    const cardStreamCreator = (query) => {  //查询卡密列表时.branchId作为参数
      query["branchId"] = this.branchId;
      query["errorTitle"] = this.search_errTitle;
      query["errorMessage"] = this.search_errMessage; 
      return this.errorCollectService.getList(query);
    };
 
    this.list.hookToQuery(cardStreamCreator).subscribe((response)=>{
      this.errorList = response;
      console.log(this.errorList);
    });

    
  }


}

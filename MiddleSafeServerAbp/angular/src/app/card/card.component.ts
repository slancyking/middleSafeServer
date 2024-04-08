import { Component,  Input,  OnInit } from '@angular/core';
import { ListService, LocalizationService, PagedResultDto, validateRange } from '@abp/ng.core';
import { query } from '@angular/animations'; 
import { BranchDto, BranchService, GetBranchListDto } from '@proxy/sk/branchs';
import { ActivatedRoute, NavigationExtras, Router } from "@angular/router";
import { CardService, CardDto, cardStatusOptions, CardStatus, cardChargingModeOptions ,CardChargingMode, ImportCardInputDto, cardTypeOptions} from '@proxy/sk/cards';
import { AbstractControl, UntypedFormBuilder, UntypedFormGroup, ValidationErrors, ValidatorFn, Validators } from '@angular/forms';
import { Confirmation, ConfirmationService } from '@abp/ng.theme.shared';
import { NgbDateNativeAdapter, NgbDateAdapter ,NgbModal,NgbCollapse  } from '@ng-bootstrap/ng-bootstrap';
import * as moment from 'moment';
import { Observable } from 'rxjs';
import { ClientCardDto } from '../common/clientDto';
import { Clipboard } from '@angular/cdk/clipboard';
@Component({
  selector: 'app-card',
  templateUrl: './card.component.html',
  styleUrls: ['./card.component.scss'],
  providers: [ListService,{ provide: NgbDateAdapter, useClass: NgbDateNativeAdapter }]
})
export class CardComponent implements OnInit {
  cardStatusExp = cardStatusOptions; //卡密状态
  cardChargingModeExp = cardChargingModeOptions; //计费模式
  cardTypeExp = cardTypeOptions;
  objectKeys = Object.keys;


  cardList = { items:[],totalCount:0} as PagedResultDto<ClientCardDto>;
 
  branch = {} as BranchDto;

  branchId:string | undefined;
  branchList = { items:[],totalCount:0}  as  PagedResultDto<BranchDto>;
  singlePage_Branch:number = 20;

  isCreateModalOpen:boolean = false; //新建项目窗口默认不打开
  isEditModalOpen:boolean = false; //编辑窗口是否打开
  isImportModalOpen:boolean = false;
  isDetailModalOpen:boolean = false; //详情页
  isExportModalOpen:boolean = false; //导出页


  form: UntypedFormGroup; // add this line
  selectCard = {} as ClientCardDto;
  selectCardArr = [];
  importErrorInfo:string = "当前无异常";
  importBusy:boolean = false;
    
  isShowSearch = false;
  _exportString:string = ""; //导出字符串
  searchForm:UntypedFormGroup;

  constructor(public readonly list: ListService, 
    private branchService : BranchService,
    private route: ActivatedRoute,
    private cardService : CardService,
    private fb: UntypedFormBuilder, // inject FormBuilder, 
    private confirmation: ConfirmationService, // inject the ConfirmationService
    private localizationService: LocalizationService,
    private router:Router,
    private modalService: NgbModal,
    private clipboard: Clipboard
    ) { 
      
        this.route.queryParams.subscribe((r: any) => {  //根据参数获取当前分支信息
          this.branchId = r.valueOf().branchId;
          if(this.branchId != null){
            this.branchService.get(this.branchId).subscribe((branch) => { 
              this.branch = branch;  
              console.log(branch);
            });
          } 
      }) 

    }
 

  ngOnInit(): void {

      const cardStreamCreator = (query) => {  //查询卡密列表时.branchId作为参数
        query["branchId"] = this.branchId;
        return this.cardService.getList(query);
      };

      if(this.branchList.totalCount == 0){
        this.getBranchList(0);
      }

      
      this.list.hookToQuery(cardStreamCreator).subscribe((response)=>{
        this.cardList = response;
        this.cardList.items.forEach(element => {
          element.check = true;
        });
 
        console.log(this.cardList);
      });

      //this.buildSearchForm();
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


  ImportCard() : void {
    this.buildImportForm();
    this.isImportModalOpen = true;
  }
  //展示导出表单
  showExportForm():void{
    this._exportString = "";
    this.cardList.items.forEach(e => {
      this._exportString += e.password.padEnd(40," ") + " , " + e.days.toString().padEnd(10," ") + " , " + e.mail.padEnd(50," ") + " , " + moment(e.expiredTime).format("YYYY年MM月DD日hh:mm") + "\r\n";
    });


    //console.log(this._exportString);
    this.buildExportForm();
    this.isExportModalOpen = true;
  }
  //拷贝导出表单内容
  copyByExportForm():void{
    this.clipboard.copy(this._exportString);
  }
  //关闭导出表单
  closeExportForm():void{
    this.isExportModalOpen = false;
  }


  createCard(): void { 
    this.buildCreateForm();
    this.isCreateModalOpen = true;
  }

  // Add editBook method
  editCard(id: string) {
    this.cardService.get(id).subscribe((card) => {
      this.selectCard = card;
      this.buildEditForm();
      this.isEditModalOpen = true;
    });
  }

  showDetail(id:string){
    this.cardService.get(id).subscribe((card) => {
      this.selectCard = card;  
 
      console.log(this.cardChargingModeExp);
      this.isDetailModalOpen = true;
    });
  }


  getFileDescription(f:string,v:any):string{
    if(f == "status" ){ 
      for (let index = 0; index < this.cardStatusExp.length; index++) {
        const element = this.cardStatusExp[index];
        if(element.value == v){
          console.log(f,element.key);
          return this.localizationService.instant("::"+element.key);
        } 
      }  
    }
    if(f == "chargingMode" ){

      for (let index = 0; index < this.cardChargingModeExp.length; index++) {
        const element = this.cardChargingModeExp[index];
        if(element.value == v){
          console.log(f,element.key);
          return this.localizationService.instant("::"+element.key);
        } 
      }   
   }
   if(f == "type" ){
    for (let index = 0; index < this.cardTypeExp.length; index++) {
      const element = this.cardTypeExp[index];
      if(element.value == v){
        console.log(f,element.key);
        return this.localizationService.instant("::"+element.key);
      } 
    }   
 }


    return v;
  }

  // Add a delete method
  delete(id: string,password: string) {

    let deleteWarn = this.localizationService.instant(
      { key: '::CardDeletionConfirmationMessage', defaultValue: 'Default Value' },
      password
    );
     
    this.confirmation.warn( deleteWarn, '::AreYouSure').subscribe((status) => {
      if (status === Confirmation.Status.confirm) {
        this.cardService.delete(id).subscribe(() => this.list.get());
      }
    });
  }

  // 创建表单
  buildCreateForm(): void { 
    this.form = this.fb.group({
      branchId: [this.branchId, Validators.required], 
      Remark: [""],
      Days: [30, Validators.required],
      Mail: [""],
      Phone: [""],
      Count:  [10, Validators.required],
      enableMail:[true,Validators.required],
      enablePhoneMsg:[true,Validators.required], 
      expiredTime: [moment().add(1, 'year').toDate(),Validators.required],
      chargingMode: [CardChargingMode.realTime,Validators.required]
    });
  }
  // 编辑表单
  buildEditForm(): void {
    this.form = this.fb.group({
      Remark: [this.selectCard.remark],
      Days: [this.selectCard.days, Validators.required],
      Mail: [this.selectCard.mail],
      Phone: [this.selectCard.phone],
      Password:[this.selectCard.password],
      Status:[this.selectCard.status, Validators.required],
      enableMail:[this.selectCard.enableMail,Validators.required],
      enablePhoneMsg:[this.selectCard.enablePhoneMsg,Validators.required], 
      expiredTime: [new Date(this.selectCard.expiredTime),Validators.required],
      chargingMode: [ this.selectCard.chargingMode ,Validators.required]
    });
  }

  //导入表单
  buildSearchForm() : void{
      this.searchForm = this.fb.group({
        branchId: [this.branchId, Validators.required], 
        filter:[""] ,
        mail:[""] ,
        phone:[""]
      }); 
  }
  
  //导入表单
  buildImportForm() : void{
      this.form = this.fb.group({
        branchId: [this.branchId, Validators.required], 
        importString:["",this.checkImport()] 
      }); 
  }

  //构建导出表单
  buildExportForm():void{ 
    this.form = this.fb.group({
      exportString:this._exportString
    });
  }


  save() : void { 
    if (this.form.invalid) { return; }
  
      this.cardService.create(this.form.value).subscribe(null,null,() => {  
      this.isCreateModalOpen = false;
      this.form.reset();
      this.list.get();
      }); 
  }

  saveEdit() : void{
    if (this.form.invalid) { return; }
  
    this.cardService.update(this.selectCard.id,this.form.value).subscribe(null,null,() => {  
    this.isEditModalOpen = false;
    this.form.reset();
    this.list.get();
    }); 
  }

  saveImport() : void{
    if (this.form.invalid) { return; }
    let importItems : ImportCardInputDto[] = [];
    let imString =  this.form.value["importString"];
    let imBranchId = this.form.value["branchId"];
    let imLine = imString.split(/\n/); 
    imLine.forEach(element => {
      let lineInfo = element.split("|"); 
      console.log(lineInfo.length );
      if (lineInfo.length != 5){
        let deleteWarn = this.localizationService.instant(
          { key: '::ImportFormatErrorInfo', defaultValue: 'Default Value' },
          element
        );
        this.confirmation.error( deleteWarn, '::ImportFormatError').subscribe((status) => {
          return;
        });
      }
 
       
      let newIm : ImportCardInputDto = {
        password : lineInfo[0].trim(),
        expiredTime : new Date((new Date(lineInfo[1].trim())).getTime() + (60*60*8*1000)).toISOString(),
        mail : lineInfo[2].trim(),
        phone : lineInfo[3].trim(),
        remark : lineInfo[4].trim(),
        branchId : imBranchId
      }; 
      
      importItems.push(newIm); 
    });
    this.importBusy = true;
    if(importItems.length > 0){
      console.log(importItems);
      this.cardService.importCard(importItems).subscribe((value) => {
        if(value.failseList.length !=0 ){
            console.log(value.failseList);
            let errCard = value.failseList.join("<br/>");

            let deleteWarn = this.localizationService.instant(
              { key: '::ImportServerExsitErrorInfo', defaultValue: 'Default Value' },
              errCard
            );
            this.confirmation.error( deleteWarn, '::Error').subscribe((status) => {
              return;
            });
        }
        this.importBusy = false;
        this.isImportModalOpen = false;
      });
      
    }  
    
  }

  checkImport()  : ValidatorFn {  
    return (control: AbstractControl): ValidationErrors | null => { 
      let imString =  control.value;
      let imLine = imString.split(/\n/);  
      let isErr:boolean = false;

      for (let index = 0; index < imLine.length; index++) {
        const element = imLine[index];
        let lineInfo = element.split("|"); 
        console.log(lineInfo.length );
        if (lineInfo.length != 5){
          let errWarn = this.localizationService.instant(
            '::ImportFormatErrorInfo',
            (index + 1).toString()
          );
          this.importErrorInfo = errWarn;
          isErr = true;
          break;
        }  
      }
      if (!isErr){ this.importErrorInfo = "当前无异常";}
      return isErr ? {forbiddenName: {value: control.value}} : null;
    };
  }

  showSearch(){
    if(!this.isShowSearch){
      this.buildSearchForm();
      this.isShowSearch = true;
    }else{
      this.isShowSearch = false;
    }
  }

  search():void{

    let formBranchId = this.searchForm.value['branchId'];
    let formFilter = this.searchForm.value['filter'];
    let formMail = this.searchForm.value['mail'];
    let formPhone = this.searchForm.value['phone'];

    const cardStreamCreator = (query) => {  //查询卡密列表时.branchId作为参数
      query["branchId"] = formBranchId;
      query["filter"] = formFilter;
      query["mail"] = formMail;
      query["phone"] = formPhone;
      return this.cardService.getList(query);
    };
 
    this.list.hookToQuery(cardStreamCreator).subscribe((response)=>{
      this.cardList = response;
      console.log(this.cardList);
    }); 
  }


  clearLoginStatus(id: string,password: string){ 
    let ClearWarn = this.localizationService.instant(
      { key: '::CardLogoutConfirmationMessage', defaultValue: 'Default Value' },
      password
    );
     
    this.confirmation.warn( ClearWarn, '::AreYouSure').subscribe((status) => {
      if (status === Confirmation.Status.confirm) {
        this.cardService.clearLoginStatusById(id).subscribe(() => this.list.get());
      }
    });
  }

}


 
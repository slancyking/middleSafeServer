import { ListService, LocalizationService, PagedResultDto } from '@abp/ng.core';
import { query } from '@angular/animations';
import { Component, OnInit } from '@angular/core';
import { BranchDto, BranchService } from '@proxy/sk/branchs';
import { ClientBranchDto } from '../common/clientDto';
import { ActivatedRoute, NavigationExtras, Router } from "@angular/router";
import { ProjectService, ProjectDto, GetProjectListDto } from '@proxy/sk/projects';
import { UntypedFormBuilder, UntypedFormGroup, Validators } from '@angular/forms';
import { Confirmation, ConfirmationService } from '@abp/ng.theme.shared';
import { Observable } from 'rxjs';


@Component({
  selector: 'app-branch',
  templateUrl: './branch.component.html',
  styleUrls: ['./branch.component.scss'],
  providers: [ListService], //,ClientBranchService
})
export class BranchComponent implements OnInit {

  branch = { items:[],totalCount:0} as PagedResultDto<ClientBranchDto>;
  _projectId:string | undefined;
  project = [] as unknown as ProjectDto;


  projectList = { items:[],totalCount:0}  as  PagedResultDto<ProjectDto>;
  singlePage_Project:number = 20;
  isCreateModalOpen = false; //新建项目窗口默�?�不打开
  form: UntypedFormGroup; // add this line
  selectBranch = {} as ClientBranchDto;

  constructor(
    public readonly list: ListService, 
    private branchService : BranchService,
    private route: ActivatedRoute,
    private projectService : ProjectService,
    private fb: UntypedFormBuilder, // inject FormBuilder, 
    private confirmation: ConfirmationService, // inject the ConfirmationService
    private localizationService: LocalizationService,
    private router:Router
    ) { 
          this.route.queryParams.subscribe((r: any) => {
              this._projectId = r.valueOf()._projectId;
              if(this._projectId != null){
                this.projectService.get(this._projectId).subscribe((project) => { 
                  this.project = project; 
                });
              }
          }) 
    }

  ngOnInit(): void {
    
    const branchStreamCreator = (query) => { 
      query["_projectId"] = this._projectId;
      return this.branchService.getList(query);
    };

    if(this.projectList.totalCount == 0){
      this.getProjectList(0);
    }

    
    this.list.hookToQuery(branchStreamCreator).subscribe((response)=>{
      this.branch = response; 
      this.branch.items.forEach(_tmpBranch => { 
        
        for(let i in this.projectList.items){
          if (this.projectList.items[i].id == _tmpBranch.projectId){
            _tmpBranch.projectName = this.projectList.items[i].name;
             break;
          } 
        } 
      }); 
      console.log(this.branch);
    });

    

  }

  createBranch(): void {
    this.selectBranch = {} as ClientBranchDto;
    this.buildForm();
    this.isCreateModalOpen = true;
  }

  // Add editBook method
  editBranch(id: string) {
    this.branchService.get(id).subscribe((branch) => {
      this.selectBranch = branch;
      this.buildForm();
      this.isCreateModalOpen = true;
    });
  }
  // Add a delete method
  delete(id: string,name: string) {

    let deleteWarn = this.localizationService.instant(
      { key: '::BranchDeletionConfirmationMessage', defaultValue: 'Default Value' },
      name
    );
     
    this.confirmation.warn( deleteWarn, '::AreYouSure').subscribe((status) => {
      if (status === Confirmation.Status.confirm) {
        this.branchService.delete(id).subscribe(() => this.list.get());
      }
    });
  }

  seeCardList(id: string){ 
    let navigationExtras:NavigationExtras = {
      queryParams:{'branchId': id}
    }
    this.router.navigate(['cards'],navigationExtras).then((r: any) => console.log(r))
    
  }

  getProjectList(tmpSkip:number = 0):void{
    let query:GetProjectListDto = {
      maxResultCount: this.singlePage_Project,
      skipCount : tmpSkip
    };
    this.projectService.getList(query).subscribe((response)=>{
      this.projectList.totalCount = response.totalCount;
      this.projectList.items = this.projectList.items.concat(response.items);
      console.log(this.projectList);
      if(tmpSkip + this.singlePage_Project <this.projectList.totalCount){
        this.getProjectList(tmpSkip + this.singlePage_Project); 
      } 
    });
 
  }

  // add buildForm method
  buildForm(): void {
    this.form = this.fb.group({
      Name: [this.selectBranch.name || '', Validators.required],
      Remark: [this.selectBranch.remark],
      isOpen: [this.selectBranch.isOpen || true, Validators.required],
      projectId: [this.selectBranch.projectId, Validators.required]
    });
  }

  save() : void { 
    if (this.form.invalid) { return; }

    const Therequest = this.selectBranch.id
      ? this.branchService.update(this.selectBranch.id, this.form.value )
      : this.branchService.create(this.form.value);
 
      Therequest.subscribe(null,null,() => {  
      this.isCreateModalOpen = false;
      this.form.reset();
      this.list.get();
      });


  }


}

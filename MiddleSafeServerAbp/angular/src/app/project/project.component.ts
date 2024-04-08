import { ListService, PagedResultDto } from '@abp/ng.core';
import { query } from '@angular/animations';
import { Component, OnInit } from '@angular/core';
import { UntypedFormBuilder, UntypedFormGroup, Validators } from '@angular/forms';
import { ProjectService, ProjectDto } from '@proxy/sk/projects';
import { ConfirmationService, Confirmation } from '@abp/ng.theme.shared';
import { LocalizationService } from '@abp/ng.core';
import {NavigationExtras,Router} from "@angular/router";


@Component({
  selector: 'app-project',
  templateUrl: './project.component.html',
  styleUrls: ['./project.component.scss'],
  providers: [ListService],
})
export class ProjectComponent implements OnInit {

  project = { items:[],totalCount:0} as PagedResultDto<ProjectDto>;

  isCreateModalOpen = false; //新建项目窗口默认不打开
  form: UntypedFormGroup; // add this line
  selectProject = {} as ProjectDto;

  constructor(public readonly list: ListService, 
    private projectService : ProjectService,
    private fb: UntypedFormBuilder, // inject FormBuilder, 
    private confirmation: ConfirmationService, // inject the ConfirmationService
    private localizationService: LocalizationService,
    private router:Router
    ) { 

    }

  ngOnInit(): void {
    const projectStreamCreator = (query) => this.projectService.getList(query);
    this.list.hookToQuery(projectStreamCreator).subscribe((response)=>{
      this.project = response;
    }); 
  }


  // add new method
  createProject() {
    this.selectProject = {} as ProjectDto;
    this.buildForm();
    this.isCreateModalOpen = true;
  }
  // Add editBook method
  editProject(id: string) {
    this.projectService.get(id).subscribe((project) => {
      this.selectProject = project;
      this.buildForm();
      this.isCreateModalOpen = true;
    });
  }
  // Add a delete method
  delete(id: string,name: string) {

    let deleteWarn = this.localizationService.instant(
      { key: '::ProjectDeletionConfirmationMessage', defaultValue: 'Default Value' },
      name
    );
     
    this.confirmation.warn( deleteWarn, '::AreYouSure').subscribe((status) => {
      if (status === Confirmation.Status.confirm) {
        this.projectService.delete(id).subscribe(() => this.list.get());
      }
    });
  }
  //查看分支
  seeBranch(id: string){

    let navigationExtras:NavigationExtras = {
      queryParams:{'_projectId': id}
    }
    this.router.navigate(['branchs'],navigationExtras).then((r: any) => console.log(r))
    
  }

  // add buildForm method
  buildForm() {
    this.form = this.fb.group({
      Name: [this.selectProject.name || '', Validators.required],
      IpMaxUserCount:[this.selectProject.ipMaxUserCount],
      Remark: [this.selectProject.remark]
    });
  }


  // add save method
  save() {
    if (this.form.invalid) { return; }

    const Therequest = this.selectProject.id
      ? this.projectService.update(this.selectProject.id, this.form.value)
      : this.projectService.create(this.form.value);
 
      Therequest.subscribe(null,null,() => {  
      this.isCreateModalOpen = false;
      this.form.reset();
      this.list.get();
      });
  }



}

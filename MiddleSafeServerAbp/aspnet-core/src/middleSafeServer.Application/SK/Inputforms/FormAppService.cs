
using middleSafeServer.SK.Inputforms.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories;
using Volo.Abp.Users;

namespace middleSafeServer.SK.Inputforms
{
    /// <summary>
    /// 后台表单查询 记录
    /// </summary>
    public class FormAppService : middleSafeServerAppService, IFormAppService
    {
        private readonly IRepository<SK.InputForms.InputForm> _formRepository;
        private readonly ICurrentUser _currentUser;


        /// <summary>
        /// 
        /// </summary>
        /// <param name="formRepository"></param>
        public FormAppService(IRepository<SK.InputForms.InputForm> formRepository, ICurrentUser currentUser)
        {
            _formRepository = formRepository;
            _currentUser = currentUser;
        }



        /// <summary>
        /// 获取表单列表
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public async Task<List<GetFormOutputDto>> GetFormInfoList(GetFormsInputDto input)
        {
            Guid? UserId = _currentUser.GetId();
            if (UserId == null ) { return null; }

            var result = await _formRepository.GetQueryableAsync();
            result = result.Where(i => i.UserId == UserId && i.Name == input.Name).OrderByDescending(i => i.CreationTime).Take(input.MaxResult);

            return ObjectMapper.Map<IQueryable<InputForms.InputForm>, List<GetFormOutputDto>>(result);
        }

        /// <summary>
        /// 获取最后表单内容
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public async Task<GetFormOutputDto> GetLastFormInfo(GetFormInputDto input)
        {
            Guid? UserId = _currentUser.GetId();
            if (UserId == null) { return null; }

            var result = await _formRepository.GetQueryableAsync();
            var lastInput = result.Where(i => i.UserId == UserId && i.Name == input.Name).OrderByDescending(i => i.CreationTime).FirstOrDefault();
            return ObjectMapper.Map<InputForms.InputForm,GetFormOutputDto>(lastInput);
        }


    }
}

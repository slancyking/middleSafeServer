using middleSafeServer.IRepository;
using middleSafeServer.SK.InputForms;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.EntityFrameworkCore;
using Volo.Abp.Timing;

namespace middleSafeServer.EntityFrameworkCore.Repositories
{
    public class InputformRepository : middleSafeServerRepositoryBase<InputForm>, IInputformRepository
    {
        public InputformRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }

        public void CreateFromObject<T>(Guid UserId, string name, T value)
        {

            Newtonsoft.Json.JsonSerializerSettings setting = new Newtonsoft.Json.JsonSerializerSettings();
            setting.ContractResolver = new CamelCasePropertyNamesContractResolver();
            setting.NullValueHandling = NullValueHandling.Ignore;
            string formpra = JsonConvert.SerializeObject(value, setting);



            var NewForm = new InputForm();
            NewForm.Name = name;
            NewForm.Value = formpra;
            NewForm.CreationTime = DateTime.Now;
            NewForm.UserId = UserId;

            InsertAsync(NewForm);


        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.IRepository
{
    public interface IInputformRepository : IRepository<SK.InputForms.InputForm, Guid>
    {
        void CreateFromObject<T>(Guid UserId, string name, T value);
    }
}

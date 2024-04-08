using middleSafeServer.SK.InfoCollects.NameCollects;
using ShardingCore.Core.EntityMetadatas;
using ShardingCore.Core.VirtualDatabase.VirtualDataSources;
using ShardingCore.Core.VirtualRoutes;
using ShardingCore.Core.VirtualRoutes.TableRoutes.Abstractions;
using ShardingCore.Helpers;
using ShardingCore.TableCreator;
using ShardingCore.VirtualRoutes.Mods;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySqlConnector;
using Microsoft.Data.SqlClient;
using ShardingCore.Core.VirtualRoutes.DataSourceRoutes.RouteRuleEngine;
using Microsoft.EntityFrameworkCore.SqlServer.Storage.Internal;
using middleSafeServer.SK.InfoCollects.ImageCollects;

namespace middleSafeServer.Routes
{
    public class ImageCollectHashRangeVirtualTableRoute : AbstractShardingOperatorVirtualTableRoute<ImageCollect, Guid>
    {

        private const string Tables = "Tables";
        private const string TABLE_NAME = "TABLE_NAME";

        private const string CurrentTableName = middleSafeServerConsts.DbTablePrefix + "ImageCollects";
        private readonly IVirtualDataSource _virtualDataSource; 
        private readonly IShardingTableCreator _shardingTableCreator;
        private readonly ConcurrentDictionary<string, object?> _tails = new ConcurrentDictionary<string, object?>(StringComparer.OrdinalIgnoreCase); 
        private readonly object _lock = new object();

        public ImageCollectHashRangeVirtualTableRoute(IVirtualDataSource virtualDataSource, IShardingTableCreator shardingTableCreator)
        {
            _virtualDataSource = virtualDataSource;
            _shardingTableCreator = shardingTableCreator;
            InitTails();
        }

        private void InitTails()
        {

            //启动寻找有哪些表后缀 
            var con = _virtualDataSource.DefaultConnectionString;
            using (var connection = new SqlConnection(con))
            {
                connection.Open();
                var database = connection.Database;

                using (var dataTable = connection.GetSchema(Tables))
                {
                    for (int i = 0; i < dataTable.Rows.Count; i++)
                    {
                            var tableName = dataTable.Rows[i][TABLE_NAME].ToString() ?? string.Empty;
                            if (tableName.StartsWith(CurrentTableName + "_", StringComparison.OrdinalIgnoreCase))
                            {
                                //如果没有下划线那么需要CurrentTableName.Length有下划线就要CurrentTableName.Length+1
                                _tails.TryAdd(tableName.Substring(CurrentTableName.Length + 1), null);
                            }
                        
                    }
                }
            }
        }

        public override void Configure(EntityMetadataTableBuilder<ImageCollect> builder)
        {
            builder.ShardingProperty(o => o.InfoAgentId);
        }

        public override Func<string, bool> GetRouteToFilter(Guid shardingKey, ShardingOperatorEnum shardingOperator)
        {
            var t = ShardingKeyFormat(shardingKey);
            switch (shardingOperator)
            { 
                case ShardingOperatorEnum.Equal: return tail => tail == t;
                default:
                    {
#if DEBUG
                        Console.WriteLine($"shardingOperator is not equal scan all table tail");
#endif
                        return tail => true;
                    }
            }
        }

        public override List<string> GetTails()
        {
            return _tails.Keys.ToList();
        }

        public override string ShardingKeyToTail(object shardingKey)
        {
            return shardingKey.ToString().Replace("-", "");
        }
        private string ShardingKeyFormat(Guid key)
        { 
            return ShardingKeyToTail(key);
        }
        public override TableRouteUnit RouteWithValue(DataSourceRouteResult dataSourceRouteResult, object shardingKey)
        {
            var shardingKeyToTail = ShardingKeyToTail(shardingKey);

            if (!_tails.TryGetValue(shardingKeyToTail, out var _))
            {
                lock (_lock)
                {
                    if (!_tails.TryGetValue(shardingKeyToTail, out var _))
                    {
                        try
                        {
                            _shardingTableCreator.CreateTable<ImageCollect>(_virtualDataSource.DefaultDataSourceName,
                                shardingKeyToTail);
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine("尝试添加表失败" + ex);
                        }

                        _tails.TryAdd(shardingKeyToTail, null);
                    }
                }
            }

            return base.RouteWithValue(dataSourceRouteResult, shardingKey);
        }



    }
}

using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace middleSafeServer.Migrations
{
    public partial class update_card_title : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "Title",
                table: "Cards",
                type: "nvarchar(max)",
                nullable: true);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Title",
                table: "Cards");
        }
    }
}

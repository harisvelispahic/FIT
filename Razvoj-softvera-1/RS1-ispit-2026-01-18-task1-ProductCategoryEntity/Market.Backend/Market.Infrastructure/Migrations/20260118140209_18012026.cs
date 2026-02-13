using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Market.Infrastructure.Migrations
{
    /// <inheritdoc />
    public partial class _18012026 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<int>(
                name: "ProductCategory2EntityId",
                table: "Products",
                type: "int",
                nullable: true);

            migrationBuilder.CreateTable(
                name: "ProductCategories2",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Name = table.Column<string>(type: "nvarchar(100)", maxLength: 100, nullable: false),
                    IsEnabled = table.Column<bool>(type: "bit", nullable: false),
                    IsDeleted = table.Column<bool>(type: "bit", nullable: false),
                    CreatedAtUtc = table.Column<DateTime>(type: "datetime2", nullable: false),
                    ModifiedAtUtc = table.Column<DateTime>(type: "datetime2", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_ProductCategories2", x => x.Id);
                });

            migrationBuilder.CreateIndex(
                name: "IX_Products_ProductCategory2EntityId",
                table: "Products",
                column: "ProductCategory2EntityId");

            migrationBuilder.AddForeignKey(
                name: "FK_Products_ProductCategories2_ProductCategory2EntityId",
                table: "Products",
                column: "ProductCategory2EntityId",
                principalTable: "ProductCategories2",
                principalColumn: "Id");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Products_ProductCategories2_ProductCategory2EntityId",
                table: "Products");

            migrationBuilder.DropTable(
                name: "ProductCategories2");

            migrationBuilder.DropIndex(
                name: "IX_Products_ProductCategory2EntityId",
                table: "Products");

            migrationBuilder.DropColumn(
                name: "ProductCategory2EntityId",
                table: "Products");
        }
    }
}

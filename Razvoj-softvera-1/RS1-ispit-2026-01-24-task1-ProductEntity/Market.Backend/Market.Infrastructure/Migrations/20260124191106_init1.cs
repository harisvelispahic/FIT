using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Market.Infrastructure.Migrations
{
    /// <inheritdoc />
    public partial class init1 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<int>(
                name: "Product2EntityId",
                table: "UserProductFavorites",
                type: "int",
                nullable: true);

            migrationBuilder.CreateTable(
                name: "Products22",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Name = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Description = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    Price = table.Column<decimal>(type: "decimal(18,2)", precision: 18, scale: 2, nullable: false),
                    StockQuantity = table.Column<int>(type: "int", nullable: false),
                    CategoryId = table.Column<int>(type: "int", nullable: false),
                    IsEnabled = table.Column<bool>(type: "bit", nullable: false),
                    IsDeleted = table.Column<bool>(type: "bit", nullable: false),
                    CreatedAtUtc = table.Column<DateTime>(type: "datetime2", nullable: false),
                    ModifiedAtUtc = table.Column<DateTime>(type: "datetime2", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Products22", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Products22_ProductCategories_CategoryId",
                        column: x => x.CategoryId,
                        principalTable: "ProductCategories",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_UserProductFavorites_Product2EntityId",
                table: "UserProductFavorites",
                column: "Product2EntityId");

            migrationBuilder.CreateIndex(
                name: "IX_Products22_CategoryId",
                table: "Products22",
                column: "CategoryId");

            migrationBuilder.AddForeignKey(
                name: "FK_UserProductFavorites_Products22_Product2EntityId",
                table: "UserProductFavorites",
                column: "Product2EntityId",
                principalTable: "Products22",
                principalColumn: "Id");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_UserProductFavorites_Products22_Product2EntityId",
                table: "UserProductFavorites");

            migrationBuilder.DropTable(
                name: "Products22");

            migrationBuilder.DropIndex(
                name: "IX_UserProductFavorites_Product2EntityId",
                table: "UserProductFavorites");

            migrationBuilder.DropColumn(
                name: "Product2EntityId",
                table: "UserProductFavorites");
        }
    }
}

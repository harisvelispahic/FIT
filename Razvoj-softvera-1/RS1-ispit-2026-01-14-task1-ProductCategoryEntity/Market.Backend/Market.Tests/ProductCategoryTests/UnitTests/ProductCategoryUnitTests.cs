using Market.Application.Modules.Catalog.ProductCategories.Commands.Create;
using Market.Application.Abstractions.Caching;
using Moq;

namespace Market.Tests.ProductCategoryTests.UnitTests;

public class ProductCategoryUnitTests
{
    private DatabaseContext GetInMemoryDbContext()
    {
        var options = new DbContextOptionsBuilder<DatabaseContext>()
            .UseInMemoryDatabase(Guid.NewGuid().ToString())// Each test gets a new database
            .Options;
        var fakeClock = new Microsoft.Extensions.Time.Testing.FakeTimeProvider();
        return new DatabaseContext(options, fakeClock);
    }

    [Fact]
    public async Task Handle_ShouldAddNewCategory()
    {
        // Arrange
        using var context = GetInMemoryDbContext(); // dispose

        // Mock ICatalogCacheVersionService
        var mockCacheVersionService = new Mock<ICatalogCacheVersionService>();
        mockCacheVersionService
            .Setup(x => x.BumpVersionAsync(It.IsAny<CancellationToken>()))
            .ReturnsAsync(2); // Returns new version number

        var handler = new CreateProductCategoryCommandHandler(context, mockCacheVersionService.Object);
        var command = new CreateProductCategoryCommand { Name = "Test Category", IsEnabled = true };

        // Act
        var resultId = await handler.Handle(command, CancellationToken.None);

        // Assert
        var category = await context.ProductCategories.FindAsync(resultId);
        Assert.NotNull(category);
        Assert.Equal("Test Category", category!.Name);

        // Verify cache version was bumped
        mockCacheVersionService.Verify(
            x => x.BumpVersionAsync(It.IsAny<CancellationToken>()),
            Times.Once);

        // (Optional) if using UTC:
        // Assert.True(category.CreatedAt > DateTime.MinValue);
    }
}
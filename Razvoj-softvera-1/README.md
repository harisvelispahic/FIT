# ⚙️ Setup & Running Instructions

This project requires a local database configuration and a running Redis instance.

---

## 1️⃣ Database Configuration

Update the connection string inside:

`appsettings.Development.json`

Example:

```json
"ConnectionStrings": {
  "DefaultConnection": "Server=localhost;Database=YourDb;Trusted_Connection=True;TrustServerCertificate=True;"
}
```

Adjust the values according to your local SQL Server setup.

---

## 2️⃣ Redis Requirement

The application uses Redis for caching / state management.

Redis must be available at:

```
localhost:6379
```

---

## 3️⃣ Running Redis via Docker (Recommended)

If Docker is installed, start Redis with:

```bash
docker run -d --name redis -p 6379:6379 redis:7-alpine
```

Verify Redis is running:

```bash
docker ps
```

---

## 4️⃣ Restore & Run Backend

From the backend project directory:

```bash
dotnet restore
dotnet run
```

---

## 5️⃣ Run Frontend (Angular)

From the Angular project directory:

```bash
npm install
ng serve
```

---

## ✅ Requirements

- .NET SDK  
- Node.js / npm  
- SQL Server (local)  
- Redis (localhost:6379)  
- Docker (optional but recommended)

---

# 🚨 Common Issues & Fixes

## EF Core Migrations

If the database is not created automatically:

```bash
dotnet ef database update
```

---

## Redis Not Running

Ensure Redis is available at:

```
localhost:6379
```

---

## Environment Configuration

Windows:

```bash
set ASPNETCORE_ENVIRONMENT=Development
```

Linux / macOS:

```bash
export ASPNETCORE_ENVIRONMENT=Development
```

---

## Angular API Endpoint

Verify backend URL inside:

`environment.ts`

Ensure the API base URL matches the running backend instance.

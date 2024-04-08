#See https://aka.ms/containerfastmode to understand how Visual Studio uses this Dockerfile to build your images for faster debugging.

FROM mcr.microsoft.com/dotnet/aspnet:6.0 AS base
WORKDIR /app
EXPOSE 80

FROM mcr.microsoft.com/dotnet/sdk:6.0 AS build
WORKDIR /src
COPY ["NuGet.Config", "."]
COPY ["src/middleSafeServer.HttpApi.Host/middleSafeServer.HttpApi.Host.csproj", "src/middleSafeServer.HttpApi.Host/"]
COPY ["src/middleSafeServer.Application/middleSafeServer.Application.csproj", "src/middleSafeServer.Application/"]
COPY ["src/middleSafeServer.Application.Contracts/middleSafeServer.Application.Contracts.csproj", "src/middleSafeServer.Application.Contracts/"]
COPY ["src/middleSafeServer.Domain.Shared/middleSafeServer.Domain.Shared.csproj", "src/middleSafeServer.Domain.Shared/"]
COPY ["src/crypto/crypto.Net45.csproj", "src/crypto/"]
COPY ["src/middleSafeServer.Domain/middleSafeServer.Domain.csproj", "src/middleSafeServer.Domain/"]
COPY ["src/middleSafeServer.EntityFrameworkCore/middleSafeServer.EntityFrameworkCore.csproj", "src/middleSafeServer.EntityFrameworkCore/"]
COPY ["src/middleSafeServer.HttpApi/middleSafeServer.HttpApi.csproj", "src/middleSafeServer.HttpApi/"]
RUN dotnet restore "src/middleSafeServer.HttpApi.Host/middleSafeServer.HttpApi.Host.csproj"
COPY . .
WORKDIR "/src/src/middleSafeServer.HttpApi.Host"
RUN dotnet build "middleSafeServer.HttpApi.Host.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "middleSafeServer.HttpApi.Host.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "middleSafeServer.HttpApi.Host.dll"]
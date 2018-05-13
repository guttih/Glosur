# DotNet

## Before you start
- Install [.NET Core.](https://microsoft.com/net/core)
- Install the [C# extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.csharp) from the VS Code Marketplace.

## Create a web application in Visual Studio Code (vscode)
```shell
mkdir appname
cd appname
dotnet new mvc
code .
```
#### Accept the question by clicking "Yes" (lower right corner)
Required assets to build and debug are missing from 'appname'. Add them?
Click 'Yes'

#### Start debugging
Ctrl+Shift+D and click play to start the debugging

Navigate to http://localhost:5000/api/values

----------------------------------------------------------------------

## Create a api application in Visual Studio Code (vscode)
```shell
dotnet new webapi -o Appname
code Appname
```
#### Accept the question by clicking "Yes" (lower right corner)
Required assets to build and debug are missing from 'appname'. Add them?
Click 'Yes'
#### Start debugging
Ctrl+Shift+D and click play to start the debugging

Navigate to http://localhost:5000/api/values
## Create a api application in Visual Studio Code (vscode)
```shell
dotnet new webapi -o Appname
code Appname
```
#### Accept the question by clicking "Yes" (lower right corner)
Required assets to build and debug are missing from 'appname'. Add them?
Click 'Yes'

Navigate to http://localhost:5000/api/values


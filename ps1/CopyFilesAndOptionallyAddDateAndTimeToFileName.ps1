# Copy files and optionally add date and time to file name
#gudjonh@valitor.is
<#
    This script allows Copy files from one directory to another 
    Additionally you can ask the script to append date and time at then end of a file name.

param(
   [string]  $FromDirectory, 
   [string]  $ToDirectory,
   [boolean] $AppendTime,
   [boolean] $ShowDestName,
   [boolean] $FilterExe,
   [boolean] $FilterDll,
   [boolean] $FilterTxt,
   [boolean] $FilterXml,
   [boolean] $FilterConfig,
   [boolean] $Force,
   [string]  $Filter0,
   [string]  $Filter1,
   [string]  $Filter2,
   [string]  $Filter3,
   [string]  $Filter4,
   [string]  $Filter5,
   [string]  $Filter6,
   [string]  $Filter7,
   [string]  $Filter8,
   [string]  $Filter9
)
#>
Write-Output "Directories from: ""$FromDirectory""   to:""$ToDirectory"""

if (  [string]::IsNullOrEmpty($FromDirectory))                { throw "Parameter FromDirectory is missing!"  }
if (  [string]::IsNullOrEmpty($ToDirectory))                  { throw "Parameter ToDirectory is missing!"    }
if ( !(Test-Path -Path $FromDirectory -PathType Container) )  { throw "FromDirectory invalid!"               }


###############################   Functions START   ###############################

function CheckParameterBool {
    Param ( [string]$ParamName, [string]$ParamValue)
    #Write-Output "$ParamName : $ParamValue"
    #if (  [string]::IsNullOrEmpty($ParamValue))                   { throw "XParameter $ParamName is missing!" }
    #if (  ($ParamValue -ne $true) -and ($ParamValue -ne $false) ) { throw "XParameter $ParamName is not true or false!" }
    [bool]$temp = $false;
    if ([bool]::TryParse($ParamValue, [ref]$temp)) {
       if ($true -eq $temp) {
       return $true;
       } else {
        return $false;
       }
    } else {
        return $false;
    }
}

function CopyFilesToDestinationFolder {
    Param ( [string]$FromDir, 
            [string]$ToDir, 
            [string]$Filter, 
            [boolean]$AppendTime, 
            [boolean]$ShowDestName,
            [boolean]$Force)

    #Write-Output "From $FromDir To $ToDir Filter $Filter  AppendTime $AppendTime  ShowDestName $ShowDestName"
    Get-ChildItem $FromDir -Filter $Filter | 
    Foreach-Object {
        
        if ( ($Force -eq $true) -and (!(Test-Path -path $ToDir) ) ){ 
            try     { New-Item $ToDir -Type Directory | Out-Null
            } catch { throw "Unable to create destination directory " 
                      Write-Error 'Can not continue' -ErrorAction Stop                                         }
        } 
        $DateString = ""
        if ($AppendTime -eq $true) { 
            $DateString = Get-Date -Format "_yyyyMMdd-HHmmss"
        } 
        
        $ToName = $_.BaseName+$DateString+$_.Extension
        if ($ShowDestName -eq $true) { Write-Output $ToName }
        $ToName = $ToDir+"\"+$ToName
        
        Copy-Item $_.FullName "$ToName"
    }
}

###############################    Functions END    ###############################



$AppendTime   = CheckParameterBool AppendTime    $AppendTime
$ShowDestName = CheckParameterBool ShowDestName  $ShowDestName

$FilterExe    = CheckParameterBool FilterExe    $FilterExe
$FilterDll    = CheckParameterBool FilterDll    $FilterDll
$FilterExe    = CheckParameterBool FilterExe    $FilterExe
$FilterTxt    = CheckParameterBool FilterTxt    $FilterTxt
$FilterXml    = CheckParameterBool FilterXml    $FilterXml
$FilterConfig = CheckParameterBool FilterConfig $FilterConfig
$Force        = CheckParameterBool Force        $Force

if ( ($Force -eq $false) -and (!(Test-Path -Path $ToDirectory -PathType Container)) )    { throw "ToDirectory invalid, dir doesn't exist or force is not strong enough!" }

if (  $FilterExe -eq $true   ) { $Filter9 = "*.exe"    }
if (  $FilterDll -eq $true   ) { $Filter8 = "*.dll"    }
if (  $FilterTxt -eq $true   ) { $Filter7 = "*.txt"    }
if (  $FilterXml -eq $true   ) { $Filter6 = "*.xml"    }
if (  $FilterConfig -eq $true) { $Filter5 = "*.config" }

if ( ([string]::IsNullOrEmpty($Filter0)) -and ([string]::IsNullOrEmpty($Filter1)) -and
     ([string]::IsNullOrEmpty($Filter2)) -and ([string]::IsNullOrEmpty($Filter3)) -and
     ([string]::IsNullOrEmpty($Filter4)) -and ([string]::IsNullOrEmpty($Filter5)) -and
     ([string]::IsNullOrEmpty($Filter6)) -and ([string]::IsNullOrEmpty($Filter7)) -and
     ([string]::IsNullOrEmpty($Filter8)) -and ([string]::IsNullOrEmpty($Filter9)) )
   { 
        throw "Parameter Filter is missing!"
   }



#extracting filters
$FilterArray = $Filter0,$Filter1,$Filter2,$Filter3,$Filter4,$Filter5,$Filter6,$Filter7,$Filter8,$Filter9
$FilterArray = $FilterArray.Where{![string]::IsNullOrEmpty($_)}

ForEach ($Filter in $FilterArray){
    try {
        CopyFilesToDestinationFolder -FromDir $FromDirectory -ToDir $ToDirectory -Filter $Filter -AppendTime $AppendTime -ShowDestName $ShowDestName -Force $Force
    } catch {
        throw $_.Exception
        
    }
}

